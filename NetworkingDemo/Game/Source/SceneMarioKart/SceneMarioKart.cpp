#include "Framework.h"

#include "SceneMarioKart.h"
#include "MKCameraObject.h"
#include "MKPlayerObject.h"
#include "NetworkManager.h"
#include "Game.h"
#include "Physics2D/Box2DManager.h"
#include "Objects/VirtualGamepad.h"

static const float c_CameraZ = -5.0f;

SceneMarioKart::SceneMarioKart(Game* pGame, fw::ResourceManager* pResources)
    : fw::Scene( pGame )
{
    m_pNetworkManager = new NetworkManager;
    m_pController = new VirtualGamepad( pGame->getEventManager() );
    m_pResources = pResources;

    loadContent();
}

SceneMarioKart::~SceneMarioKart()
{
    delete m_pNetworkManager;
}

void SceneMarioKart::loadContent()
{
    // Load our textures.
    {
        m_pResources->add<fw::Texture>( "Track", new fw::Texture("Data/SceneMarioKart/SNES_Mario_Circuit_3_map.png") );
        m_pResources->add<fw::Texture>( "KartMario", new fw::Texture("Data/SceneMarioKart/KartMario.png") );
        m_pResources->add<fw::Texture>( "KartLuigi", new fw::Texture("Data/SceneMarioKart/KartLuigi.png") );
        m_pResources->add<fw::Texture>( "KartToad", new fw::Texture("Data/SceneMarioKart/KartToad.png") );
        m_pResources->add<fw::Texture>( "KartBowser", new fw::Texture("Data/SceneMarioKart/KartBowser.png") );
        m_pResources->add<fw::Texture>( "KartMarioFront", new fw::Texture("Data/SceneMarioKart/KartMarioFront.png") );
        m_pResources->add<fw::Texture>( "KartLuigiFront", new fw::Texture("Data/SceneMarioKart/KartLuigiFront.png") );
        m_pResources->add<fw::Texture>( "KartToadFront", new fw::Texture("Data/SceneMarioKart/KartToadFront.png") );
        m_pResources->add<fw::Texture>( "KartBowserFront", new fw::Texture("Data/SceneMarioKart/KartBowserFront.png") );
    }

    // Load our materials.
    {
        m_pResources->add<fw::Material>( "Track", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("Track"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartMario", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartMario"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartLuigi", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartLuigi"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartToad", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartToad"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartBowser", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartBowser"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartMarioFront", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartMarioFront"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartLuigiFront", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartLuigiFront"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartToadFront", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartToadFront"), fw::color4f::white(), true) );
        m_pResources->add<fw::Material>( "KartBowserFront", new fw::Material(m_pResources->get<fw::ShaderProgram>("Texture"), m_pResources->get<fw::Texture>("KartBowserFront"), fw::color4f::white(), true) );
    }

    // Create some game objects.
    {
        // Camera
        MKCameraObject* pCamera = new MKCameraObject( this, "Camera", vec3(0, 2, -3), vec3(0,0,0), vec3(1,1,1) );
        m_pCamera = pCamera;
        addGameObject( pCamera );
        //m_pBox2DManager->SetViewProjMatrices( pCamera->GetViewMatrix(), GetGameCore()->GetProjectionMatrix() );

        m_pBox2DManager = new Box2DManager( nullptr, pCamera );
        m_pBox2DManager->getWorld()->SetGravity( b2Vec2(0,0) );

        MKGameObject* pTrack = new MKGameObject( this, "Track", vec3(66,-0.5,-7.5), vec3(-90,0,0), vec3(150), m_pResources->get<fw::Mesh>("Sprite"), m_pResources->get<fw::Material>("Track") );
        addGameObject( pTrack );

        MKPlayerObject* pPlayer1 = new MKPlayerObject( this, "Player0", vec3(0.0f,0,0), vec3(0,0,0), vec3(1), m_pResources->get<fw::Mesh>("Sprite"), m_pResources->get<fw::Material>("KartMario"),  m_pResources->get<fw::Material>("KartMarioFront") );
        MKPlayerObject* pPlayer2 = new MKPlayerObject( this, "Player1", vec3(1.5f,0,0), vec3(0,0,0), vec3(1), m_pResources->get<fw::Mesh>("Sprite"), m_pResources->get<fw::Material>("KartLuigi"),  m_pResources->get<fw::Material>("KartLuigiFront") );
        MKPlayerObject* pPlayer3 = new MKPlayerObject( this, "Player2", vec3(3.0f,0,0), vec3(0,0,0), vec3(1), m_pResources->get<fw::Mesh>("Sprite"), m_pResources->get<fw::Material>("KartToad"),   m_pResources->get<fw::Material>("KartToadFront") );
        MKPlayerObject* pPlayer4 = new MKPlayerObject( this, "Player3", vec3(4.5f,0,0), vec3(0,0,0), vec3(1), m_pResources->get<fw::Mesh>("Sprite"), m_pResources->get<fw::Material>("KartBowser"), m_pResources->get<fw::Material>("KartBowserFront") );
        addGameObject( pPlayer1 );
        addGameObject( pPlayer2 );
        addGameObject( pPlayer3 );
        addGameObject( pPlayer4 );

        pPlayer1->createBody( false );
        pPlayer2->createBody( false );
        pPlayer3->createBody( false );
        pPlayer4->createBody( false );

        pPlayer1->addBox( vec2(1), 1 );
        pPlayer2->addBox( vec2(1), 1 );
        pPlayer3->addBox( vec2(1), 1 );
        pPlayer4->addBox( vec2(1), 1 );

        pPlayer1->setController( m_pController );
        pCamera->setObjectToFollow( pPlayer1, c_CameraZ );
    }
}

void SceneMarioKart::startFrame(float deltaTime)
{
}

void SceneMarioKart::update(float deltaTime)
{
    //fw::Scene::update( deltaTime );

    m_pBox2DManager->update( deltaTime );

    for( fw::GameObject* pObject : m_objects )
    {
        pObject->update( deltaTime );
    }

    m_pCamera->update( 0 );

    m_pNetworkManager->update( deltaTime, this );

    if( m_pGameCore->getFramework()->isKeyDown('S') && m_pGameCore->getFramework()->isKeyDown(17) ) //VK_LCONTROL] )
    {
        m_pNetworkManager->initAsServer( 12345 );
        return;
    }
    if( m_pGameCore->getFramework()->isKeyDown('C') && m_pGameCore->getFramework()->isKeyDown(17) ) //VK_LCONTROL] )
    {
        m_pNetworkManager->initAsClient( 3333/* + rand()%1000*/, "10.50.42.144", 12345 );
        return;
    }
    if( m_pGameCore->getFramework()->isKeyDown('W') && m_pGameCore->getFramework()->isKeyDown(17) ) //VK_LCONTROL] )
    {
        m_pNetworkManager->webRequest();
        return;
    }

    if( m_pGameCore->getFramework()->isKeyDown('Z') )
    {
        ( (MKCameraObject*)getGameObjectByName( "Camera"  ) )->setObjectToFollow( getGameObjectByName( "Player0" ), c_CameraZ );
        ( (MKPlayerObject*)getGameObjectByName( "Player0" ) )->setController( m_pController );
        ( (MKPlayerObject*)getGameObjectByName( "Player1" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player2" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player3" ) )->setController( nullptr );
    }
    if( m_pGameCore->getFramework()->isKeyDown('X') )
    {
        ( (MKCameraObject*)getGameObjectByName( "Camera"  ) )->setObjectToFollow( getGameObjectByName( "Player1" ), c_CameraZ );
        ( (MKPlayerObject*)getGameObjectByName( "Player0" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player1" ) )->setController( m_pController );
        ( (MKPlayerObject*)getGameObjectByName( "Player2" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player3" ) )->setController( nullptr );
    }
    if( m_pGameCore->getFramework()->isKeyDown('C') )
    {
        ( (MKCameraObject*)getGameObjectByName( "Camera"  ) )->setObjectToFollow( getGameObjectByName( "Player2" ), c_CameraZ );
        ( (MKPlayerObject*)getGameObjectByName( "Player0" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player1" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player2" ) )->setController( m_pController );
        ( (MKPlayerObject*)getGameObjectByName( "Player3" ) )->setController( nullptr );
    }
    if( m_pGameCore->getFramework()->isKeyDown('V') )
    {
        ( (MKCameraObject*)getGameObjectByName( "Camera"  ) )->setObjectToFollow( getGameObjectByName( "Player3" ), c_CameraZ );
        ( (MKPlayerObject*)getGameObjectByName( "Player0" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player1" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player2" ) )->setController( nullptr );
        ( (MKPlayerObject*)getGameObjectByName( "Player3" ) )->setController( m_pController );
    }
}

void SceneMarioKart::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    for( fw::GameObject* pObject : m_objects )
    {
        pObject->draw( viewID );
    }

    //fw::Scene::draw();
    ////m_pBox2DManager->getWorld()->DrawDebugData();
}

void SceneMarioKart::addGameObject(fw::GameObject* pObject)
{
    m_objects.push_back( pObject );
}

bool SceneMarioKart::removeGameObject(fw::GameObject* pObject)
{
    auto iteratorForObject = std::find( m_objects.begin(), m_objects.end(), pObject );

    if( iteratorForObject != m_objects.end() )
    {
        m_objects.erase( iteratorForObject );
        return true;
    }

    return false;
}

bool SceneMarioKart::isGameObjectInScene(fw::GameObject* pObject)
{
    auto iteratorForObject = std::find( m_objects.begin(), m_objects.end(), pObject );

    if( iteratorForObject != m_objects.end() )
    {
        return true;
    }

    return false;
}

fw::GameObject* SceneMarioKart::getGameObjectByName(std::string name)
{
    for( auto pObject: m_objects )
    {
        if( pObject->getName() == name )
        {
            return pObject;
        }
    }

    return nullptr;
}
