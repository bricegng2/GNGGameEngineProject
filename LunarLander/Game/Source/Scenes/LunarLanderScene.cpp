#include "Framework.h"
#include "LunarLanderScene.h"
#include "Game.h"
#include "Objects/VirtualGamepad.h"

static const int c_MaxCollectibles = 5;
static const float c_CollectibleSpawnTime = 2.5f;
static const float c_CollectibleRadius = 0.15f;
static const float c_PlayerRadius = 0.5f;

LunarLanderScene::LunarLanderScene(Game* pGame)
    : fw::Scene( pGame )
{
    fw::ResourceManager* pResources = pGame->getResources();

    m_pPhysicsWorld = createPhysicsWorld( fw::PhysicsWorldType::Jolt, m_pGameCore->getEventManager() );
    m_pPhysicsWorld->setGravity( vec3(0,-2,0) );

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(3,5.0f,-10), vec3(3,0,0) );

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager() );

    m_pPlayer = new fw::GameObject( this, "Player" );
    float playerScale = c_PlayerRadius * 2.0f;
    m_pPlayer->addComponent( new fw::TransformComponent( m_pPlayer, vec3(7,5,0), vec3(0,0,0), playerScale ) );
    m_pPlayer->addComponent( new fw::RenderComponent( m_pPlayer, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Green") ) );
    m_pPlayer->addComponent( new fw::PhysicsBodyComponent( m_pPlayer, m_pPhysicsWorld, true, fw::ShapeType::Box ) );
    m_objects.push_back( m_pPlayer );

    fw::PhysicsBody* pPlayerBody = m_pPlayer->getComponent<fw::PhysicsBodyComponent>()->m_pBody;
    pPlayerBody->setAllowSleep( false );
    pPlayerBody->setLinearDamping( 0.2f );
    pPlayerBody->setAngularDamping( 5.0f );
    pPlayerBody->limitTo2D();

    fw::GameObject* pGO;
    pGO = new fw::GameObject( this, "Ground Left" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(0,-0.1f,0), vec3(0,0,0), vec3(6,0.2f,3) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Blue") ) );
    pGO->addComponent( new fw::PhysicsBodyComponent( pGO, m_pPhysicsWorld, false, fw::ShapeType::Box ) );
    m_objects.push_back( pGO );
    m_pRotatingPhysicsObject = pGO;

    pGO = new fw::GameObject( this, "Ground Right" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(8.0f,-0.1f,0.0f), vec3(0,0,0), vec3(6,0.2f,3) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Blue") ) );
    pGO->addComponent( new fw::PhysicsBodyComponent( pGO, m_pPhysicsWorld, false, fw::ShapeType::Box ) );
    m_objects.push_back( pGO );
    m_pNonRotatingPhysicsObject = pGO;

    pGO = new fw::GameObject( this, "EngineLeft" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(0,0,0), vec3(0,0,0), vec3(0.1f, 0.1f, 0.1f) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Red") ) );
    m_objects.push_back( pGO );
    m_pEngineLeft = pGO;

    pGO = new fw::GameObject( this, "EngineRight" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(0,0,0), vec3(0,0,0), vec3(0.1f, 0.1f, 0.1f) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Red") ) );
    m_objects.push_back( pGO );
    m_pEngineRight = pGO;

    // Create a pool of collectible objects.
    for( int i=0; i<c_MaxCollectibles; i++ )
    {
        vec3 pos = vec3( i*2.0f, 1, 0 );
        float scale = c_CollectibleRadius * 2.0f;

        pGO = new fw::GameObject( this, std::string("Collectible") + std::to_string(i) );
        pGO->addComponent( new fw::TransformComponent( pGO, pos, vec3(0,0,0), scale ) );
        pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Red") ) );
        pGO->setActive( false );

        m_collectiblesInactive.push_back( pGO );
    }
}

LunarLanderScene::~LunarLanderScene()
{
    for( fw::GameObject* pObject : m_objects )
    {
        delete pObject;
    }

    delete m_pCamera;
    delete m_pGamepad;
}

void LunarLanderScene::startFrame(float deltaTime)
{
    // Reset the gamepad.
    m_pGamepad->startFrame();
}

//void LunarLanderScene::onEvent(fw::Event* pEvent)
//{
//    GameScene::onEvent( pEvent );
//}

void LunarLanderScene::update(float deltaTime)
{
    m_pComponentManager->syncPhysicsBodiesToGameObjectTransforms();

    editor_displayObjectList();

    vec3 playerPosition = m_pPlayer->getComponent<fw::TransformComponent>()->m_position;

    // Draw game stats.
    ImGui::Begin( "Game Stats" );
    ImGui::Text( "Score: %d", m_score );
    ImGui::Text( "Collectibles: %d", m_collectiblesActive.size() );
    ImGui::Text( "Inactive Collectibles: %d", m_collectiblesInactive.size() );
    ImGui::Text("player position: %.2f, %.2f, %.2f", playerPosition.x, playerPosition.y, playerPosition.z);
    ImGui::End();

    m_pPhysicsWorld->update(deltaTime); // jimmy why did you put 0.0f here... wtf
    m_pComponentManager->syncPhysicsObjects();

    fw::PhysicsBodyComponent* pPlayerBody = m_pPlayer->getComponent<fw::PhysicsBodyComponent>();
    fw::TransformComponent* pPlayerTransform = m_pPlayer->getComponent<fw::TransformComponent>();
    fw::TransformComponent* pLeftEngineTransform = m_pEngineLeft->getComponent<fw::TransformComponent>();
    fw::TransformComponent* pRightEngineTransform = m_pEngineRight->getComponent<fw::TransformComponent>();

    // Calculate world position of the left and right sides of the player taking into account the rotation.
    mat4 rot;
    rot.createRotation( pPlayerTransform->m_rotation );
    vec3 worldPointLeft = pPlayerTransform->m_position + rot * vec3(-0.5f,-0.5f,0);
    vec3 worldPointRight = pPlayerTransform->m_position + rot * vec3(0.5f,-0.5f,0);

    // Place engines at the left and right sides of the player.
    pLeftEngineTransform->m_position = worldPointLeft;
    pLeftEngineTransform->m_position.z = -0.5f;
    pLeftEngineTransform->m_rotation = pPlayerTransform->m_rotation;
    pLeftEngineTransform->m_scale.y = 0.1f;

    pRightEngineTransform->m_position = worldPointRight;
    pRightEngineTransform->m_position.z = -0.5f;
    pRightEngineTransform->m_rotation = pPlayerTransform->m_rotation;
    pRightEngineTransform->m_scale.y = 0.1f;

    float force = 2;

    // Rotate the force.
    vec3 rotatedForce = rot * vec3(0,force,0);

    // Apply forces and scale the engines based on input.
    if( m_pGamepad->isHeld( VirtualGamepad::Left ) )
    {
        pLeftEngineTransform->m_scale.y = force;
        pPlayerBody->m_pBody->applyForceAtWorldPos( rotatedForce, worldPointLeft );
    }
    if( m_pGamepad->isHeld( VirtualGamepad::Right ) )
    {
        pRightEngineTransform->m_scale.y = force;
        pPlayerBody->m_pBody->applyForceAtWorldPos( rotatedForce, worldPointRight);
    }

    // Spawn collectibles.
    for( fw::GameObject* pCollectible : m_collectiblesInactive )
    {
        timer += deltaTime;
        if (timer >= c_CollectibleSpawnTime)
        {
            pCollectible->setActive(true);
            vec3 pos = vec3(fw::Random::randomFloat(0, 8), fw::Random::randomFloat(2, 5), 0);
            pCollectible->getComponent<fw::TransformComponent>()->m_position = pos;

            m_objects.push_back(pCollectible);
            m_collectiblesActive.push_back(pCollectible);
            m_collectiblesInactive.erase(std::remove(m_collectiblesInactive.begin(), m_collectiblesInactive.end(), pCollectible), m_collectiblesInactive.end());
            
            timer = 0.0f;
        }

        // Shift the Collectible between the 3 vectors and activate it.

        break;
    }

    checkForCollectibleCollision();
}

void LunarLanderScene::checkForCollectibleCollision()
{
    float playerRadius = c_PlayerRadius;
    float collectibleRadius = c_CollectibleRadius;
    vec3 playerPos = m_pPlayer->getComponent<fw::TransformComponent>()->m_position;

    // Check for collisions with active collectibles.
    for( fw::GameObject* pCollectible : m_collectiblesActive )
    {
        // Increase score.
        // Shift the Collectible between the 3 vectors and disable it.
        vec3 collectiblePos = pCollectible->getComponent<fw::TransformComponent>()->m_position;

        float distance = (playerPos - collectiblePos).length();

        if( distance < (playerRadius + collectibleRadius) )
        {
            m_score++;
            pCollectible->setActive(false);
            m_collectiblesInactive.push_back(pCollectible);
            m_collectiblesActive.erase(std::remove(m_collectiblesActive.begin(), m_collectiblesActive.end(), pCollectible), m_collectiblesActive.end());
            m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), pCollectible), m_objects.end());
        }
    }
}

void LunarLanderScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    m_pComponentManager->updateTransforms();
    m_pComponentManager->renderMeshes( 0, nullptr );
}

void LunarLanderScene::editor_displayObjectList()
{
    ImGui::Begin( "Object List" );
    for( fw::GameObject* pObject : m_objects )
    {
        ImGui::Text( "%s", pObject->getName().c_str() );
    }
    ImGui::End();

    ImGui::Begin( "Active Collectibles List" );
    for( fw::GameObject* pObject : m_collectiblesActive )
    {
        ImGui::Text( "%s", pObject->getName().c_str() );
    }
    ImGui::End();

    ImGui::Begin( "Inactive Collectibles List" );
    for( fw::GameObject* pObject : m_collectiblesInactive )
    {
        ImGui::Text( "%s", pObject->getName().c_str() );
    }
    ImGui::End();
}
