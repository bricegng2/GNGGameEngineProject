#include "Framework.h"

#include "DataTypes.h"
#include "Events/GameEvents.h"
#include "EweScene.h"
#include "MeatChunkObject.h"
#include "MeteorObject.h"
#include "MidtermBaseObject.h"
#include "Objects/VirtualGamepad.h"
#include "ShakeCameraObject.h"
#include "SheepObject.h"
#include "SheepTitleCard.h"

class MyContactListener : public b2ContactListener
{
public:
    MyContactListener(fw::EventManager* pEventManager)
        : m_pEventManager( pEventManager )
    {
    }
    ~MyContactListener() {}

    virtual void BeginContact(b2Contact* contact)
    {
        b2Fixture* pFixture[2];
        MidtermBaseObject* pObjects[2];

        pFixture[0] = contact->GetFixtureA();
        pFixture[1] = contact->GetFixtureB();

        pObjects[0] = reinterpret_cast<MidtermBaseObject*>( pFixture[0]->GetBody()->GetUserData().pointer );
        pObjects[1] = reinterpret_cast<MidtermBaseObject*>( pFixture[1]->GetBody()->GetUserData().pointer );

        b2WorldManifold worldManifold;
        contact->GetWorldManifold( &worldManifold );
        vec2 position( worldManifold.points[0].x, worldManifold.points[0].y );
        vec2 normal( worldManifold.normal.x, worldManifold.normal.y );

        CollisionEvent* pEvent = new CollisionEvent( pObjects[0], pObjects[1], position, normal );
        m_pEventManager->addEvent( pEvent );
    }

    virtual void EndContact(b2Contact* contact) {}
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}

protected:
    fw::EventManager* m_pEventManager = nullptr;
};

const float EweScene::c_InitialProjectileSpawnDelay = 1.0f;
const float EweScene::c_TimeBetweenProjectileSpawns = 0.3f;
const int EweScene::c_NumProjectilesInPool = 100;
const int EweScene::c_NumMeatChunksInPool = 100;

EweScene::EweScene(fw::GameCore* pGame, fw::ResourceManager* pResources)
    : fw::Scene( pGame )
    , m_pResources( pResources )
    , m_projectilePool()
    , m_meatChunkPool()
{
    m_pBox2DWorld = new b2World( b2Vec2(0,-10) );

    pGame->getEventManager()->registerListener<RemoveFromGameEvent>( this );
    pGame->getEventManager()->registerListener<CollisionEvent>( this );

    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager() );
    loadContent();

    m_projectileSpawnTimer = c_InitialProjectileSpawnDelay;
}

EweScene::~EweScene()
{
    m_pGameCore->getEventManager()->unregisterListener<RemoveFromGameEvent>( this );
    m_pGameCore->getEventManager()->unregisterListener<CollisionEvent>( this );
}

void EweScene::onEvent(fw::Event* pEvent)
{
    if( pEvent->getType() == RemoveFromGameEvent::getStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        MidtermBaseObject* pObject = (MidtermBaseObject*)pRemoveEvent->getGameObject();
        removeFromScene( pObject );
    }
    else if( pEvent->getType() == CollisionEvent::getStaticEventType() )
    {
        CollisionEvent* pCollisionEvent = static_cast<CollisionEvent*>(pEvent);

        MidtermBaseObject* pObjectA = (MidtermBaseObject*)pCollisionEvent->m_pObjectA;
        MidtermBaseObject* pObjectB = (MidtermBaseObject*)pCollisionEvent->m_pObjectB;

        pObjectA->beginContact( pObjectB, pCollisionEvent->m_position.xy(),  pCollisionEvent->m_dirFromAtoB.xy() );
        pObjectB->beginContact( pObjectA, pCollisionEvent->m_position.xy(), -pCollisionEvent->m_dirFromAtoB.xy() );
    }
}

void EweScene::reset()
{
    // Reset all of the Scene objects in the list.
    std::vector<MidtermBaseObject*> objectListCopy = m_objects;
    for( MidtermBaseObject* pObject : objectListCopy )
    {
        pObject->reset();
    }

    m_projectileSpawnTimer = c_InitialProjectileSpawnDelay;
}

void EweScene::loadContent()
{
    // Load our textures.
    {
        m_pResources->add<fw::Texture>( "Ground", new fw::Texture("Data/Midterm/Ground.png") );
        m_pResources->add<fw::Texture>( "Meteor", new fw::Texture("Data/Midterm/Meteor.png") );
        m_pResources->add<fw::Texture>( "Sheep",  new fw::Texture("Data/Midterm/Sheep.png") );
        m_pResources->add<fw::Texture>( "Bone",   new fw::Texture("Data/Midterm/Bone.png") );
        m_pResources->add<fw::Texture>( "Meat",   new fw::Texture("Data/Midterm/ItemFood.png") );
        m_pResources->add<fw::Texture>( "Title",  new fw::Texture("Data/Midterm/Title.png") );
        m_pResources->add<fw::Texture>( "BG",     new fw::Texture("Data/Midterm/BG.png") );
        m_pResources->add<fw::Texture>( "Win",    new fw::Texture("Data/Midterm/Win.png") );
        m_pResources->add<fw::Texture>( "Lose",   new fw::Texture("Data/Midterm/Lose.png") );

        m_pResources->add<fw::Material>( "Ground", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Ground"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Meteor", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Meteor"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Sheep",  new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Sheep"),  fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Bone",   new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Bone"),   fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Meat",   new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Meat"),   fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Title",  new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Title"),  fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "BG",     new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("BG"),     fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Win",    new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Win"),    fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "Lose",   new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Lose"),   fw::color4f::white(), true) );
    }

    // Create some game objects.
    {
#define getMesh m_pResources->get<fw::Mesh>
#define getMaterial m_pResources->get<fw::Material>

        // Camera
        m_pCamera = new ShakeCameraObject( this, vec3(0,0,-15) );

        // BG
        m_objects.push_back( new MidtermBaseObject(this, "BG", vec3(0,0,2), vec3(0,0,0), vec3(15,15,1), getMesh("Sprite"), getMaterial("BG")) );

        // Player
        SheepObject* pSheep = new SheepObject(this, "Player", vec3(1, -1, 1), vec3(0, 0, 0), vec3(1, 1, 1), getMesh("Sprite"), getMaterial("Sheep"));
        pSheep->addPhysicsBox( vec2(1,1), true, true, 1 );
        pSheep->setGamepad( m_pGamepad );
        m_objects.push_back( pSheep );

        // Ground
        MidtermBaseObject* pGround = new MidtermBaseObject(this, "Ground", vec3(0,-5,0), vec3(0,0,0), vec3(10,1,1), getMesh("Sprite"), getMaterial("Ground"));
        pGround->addPhysicsBox( vec2( 10,1 ), false, true, 1 );
        m_objects.push_back( pGround );

        // Title
        m_objects.push_back( new SheepTitleCard(this, "Title", vec3(0,3,0), vec3(0,0,0), vec3(10,1,1), getMesh("Sprite"), getMaterial("Title")) );
        m_objects.push_back( new SheepTitleCard(this, "Win", vec3(0,20,0), vec3(0,0,0), vec3(10,1,1), getMesh("Sprite"), getMaterial("Win")) );
        m_objects.push_back( new SheepTitleCard(this, "Lose", vec3(0,20,0), vec3(0,0,0), vec3(10,1,1), getMesh("Sprite"), getMaterial("Lose")) );
    }

    // Fill the pool with 100 projectiles.
    {
        for( int i=0; i<c_NumProjectilesInPool; i++ )
        {
            float meteorSize = 0.5f;

            char tempstr[50];
            sprintf_s( tempstr, 50, "Meteor%d", i );
            MeteorObject* pMeteor = new MeteorObject( this, tempstr, vec3(-10000,-10000,0), vec3(0,0,0), vec3(meteorSize,meteorSize,1), getMesh("Sprite"), getMaterial("Meteor") );
            pMeteor->addPhysicsCircle( meteorSize/2, true, false, 50 );

            m_projectilePool.push_back( pMeteor );
            assert( pMeteor->getEweScene() == this );
            pMeteor->setPool( &m_projectilePool );
        }
    }

    // Fill the pool with 100 random bits of meat and bone.
    {
        for( int i=0; i<c_NumMeatChunksInPool; i++ )
        {
            float meatChunkSize = 0.5f;

            char tempstr[50];
            sprintf_s( tempstr, 50, "MeatChunk%d", i );

            fw::Material* chunkMaterial = getMaterial( "Meat" );
            if( rand()%2 == 0 )
                chunkMaterial = getMaterial( "Bone" );

            MeatChunkObject* pMeatChunk = new MeatChunkObject( this, tempstr, vec3(-10000,-10000,0), vec3(0,0,0), vec3(meatChunkSize,meatChunkSize,1), getMesh("Sprite"), chunkMaterial );
            pMeatChunk->addPhysicsCircle( meatChunkSize/6, true, false, 50 );

            m_meatChunkPool.push_back( pMeatChunk );
            pMeatChunk->setPool( &m_meatChunkPool );
        }
    }
}

void EweScene::startFrame(float deltatime)
{
    m_pGamepad->startFrame();
}

void EweScene::update(float deltatime)
{
    if( m_pGameCore->getFramework()->isKeyDown('R') )
    {
        reset();
    }

    m_pCamera->update( deltatime );

    m_projectileSpawnTimer -= deltatime;
    if( m_projectileSpawnTimer < 0.0f )
    {
        MidtermBaseObject* pGameObject = m_projectilePool.back();
        assert( pGameObject->getEweScene() == this );
        m_projectilePool.pop_back();

        if( pGameObject )
        {
            pGameObject->addToScene( this );
            
            vec3 location = vec3(fw::Random::randomFloat(-4.0f, 4.0f), 8, 0);
            pGameObject->setPosition(location);

            b2Body* pBody = pGameObject->getPhysicsBody();
            pBody->SetEnabled( true );
            pBody->ApplyLinearImpulse(b2Vec2(fw::Random::randomFloat(-40.0f, 40.0), -200.0f), pBody->GetWorldCenter(), true);
        }

        m_projectileSpawnTimer = c_TimeBetweenProjectileSpawns;
    }

    for( int i=0; i<m_objects.size(); i++ )
    {
        m_objects[i]->update( deltatime );
    }

    float timeStep = deltatime;
    int velocityIterations = 8;
    int positionIterations = 3;

    m_pBox2DWorld->Step(timeStep, velocityIterations, positionIterations);
}

void EweScene::draw()
{
    int viewID = 0;

    m_pCamera->enable( viewID );

    for( MidtermBaseObject* pObject : m_objects )
    {
        pObject->draw( viewID );
    }
}

void EweScene::addToScene(std::string name, MidtermBaseObject* pObject)
{
    m_objects.push_back( pObject );
}

void EweScene::removeFromScene(MidtermBaseObject* pObject)
{
    auto it = std::find( m_objects.begin(), m_objects.end(), pObject );
    if( it != m_objects.end() )
    {
        m_objects.erase( it );
    }
}

MidtermBaseObject* EweScene::getGameObject(std::string name)
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i]->getName() == name)
        {
            return m_objects[i];
        }
    }
}

void EweScene::spawnMeatChunks(vec3 spawnpos, unsigned int numchunks)
{
    for( unsigned int i=0; i<numchunks; i++ )
    {
        MidtermBaseObject* pGameObject = m_meatChunkPool.back();
        m_meatChunkPool.pop_back();

        if( pGameObject )
        {
            pGameObject->addToScene( this );

            pGameObject->setPosition( spawnpos );

            b2Body* pBody = pGameObject->getPhysicsBody();

            float mass = pBody->GetMass();

            float randvelx = mass * (-2.5f + rand()%50/10.0f);
            float randvely = mass * (6.5f + rand()%30/10.0f);
            float randtorque = mass * (-4.5f + rand()%90/10.0f);

            pBody->SetEnabled( true );
            pBody->ApplyLinearImpulse( b2Vec2( randvelx, randvely ), pBody->GetWorldCenter(), true );
            pBody->ApplyTorque( randtorque, false );
        }
    }
}
