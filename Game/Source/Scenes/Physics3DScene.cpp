#include "Framework.h"
#include "Physics3DScene.h"
#include "Game.h"
#include "Objects/VirtualGamepad.h"

Physics3DScene::Physics3DScene(Game* pGame)
    : fw::Scene( pGame )
{
    fw::ResourceManager* pResources = pGame->getResources();

    m_pPhysicsWorld = fw::createPhysicsWorld( fw::PhysicsWorldType::Jolt, m_pGameCore->getEventManager() );

    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(3, 30, -100), vec3(3, 0, 0));

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager(), m_pGameCore->getFramework());

    m_pPlayer = new fw::GameObject( this, "Player" );
    m_pPlayer->addComponent( new fw::TransformComponent( m_pPlayer, vec3(0,5,0), vec3(0,0,0), vec3(2,2,2) ) );
    m_pPlayer->addComponent( new fw::RenderComponent( m_pPlayer, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("MegaMan") ) );
    m_pPlayer->addComponent( new fw::PhysicsBodyComponent( m_pPlayer, m_pPhysicsWorld, true, fw::ShapeType::Box ) );
    m_pPlayer->getComponent<fw::PhysicsBodyComponent>()->m_pBody->setAllowSleep( false );
    m_Objects.push_back( m_pPlayer );

    fw::GameObject* pGO;
    pGO = new fw::GameObject( this, "Ground" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(0,-0.1f,0), vec3(0,0,0), vec3(200,0.2f,200) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Blue") ) );
    pGO->addComponent( new fw::PhysicsBodyComponent( pGO, m_pPhysicsWorld, false, fw::ShapeType::Box ) );
    m_Objects.push_back( pGO );
    m_pRotatingPhysicsObject = pGO;

    for (int i = 0; i < 20; i++)
    {
        pGO = new fw::GameObject(this, "Obstacle");
        pGO->addComponent(new fw::TransformComponent(pGO, vec3(0.6f, 1.0f, -60.6f), vec3(0, 0, 0), vec3(1, 1, 1)));
        pGO->addComponent(new fw::RenderComponent(pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Red")));
        pGO->addComponent(new fw::PhysicsBodyComponent(pGO, m_pPhysicsWorld, true, fw::ShapeType::Box));
        m_Objects.push_back(pGO);
    }

    for (int i = 0; i < 20; i++)
    {
        pGO = new fw::GameObject(this, "Obstacle");
        pGO->addComponent(new fw::TransformComponent(pGO, vec3(0.6f, 1.0f*i, -60.6f), vec3(0, 0, 0), vec3(1, 1, 1)));
        pGO->addComponent(new fw::RenderComponent(pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Red")));
        pGO->addComponent(new fw::PhysicsBodyComponent(pGO, m_pPhysicsWorld, true, fw::ShapeType::Box));
        m_Objects.push_back(pGO);
    }

    pGO = new fw::GameObject( this, "NoPhysics" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(8.0f,-0.1f,0.0f), vec3(0,0,0), vec3(6,0.2f,3) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Cube"), pResources->get<fw::Material>("Red") ) );
    m_Objects.push_back( pGO );
    m_pNonRotatingPhysicsObject = pGO;
}

Physics3DScene::~Physics3DScene()
{
}

void Physics3DScene::startFrame(float deltaTime)
{
    // Reset the gamepad.
    m_pGamepad->startFrame();
}

void Physics3DScene::update(float deltaTime)
{
    //Editor_DisplayObjectList();
    m_pPhysicsWorld->update( deltaTime );
    m_pComponentManager->syncPhysicsObjects();

    float force = 100;

    if( m_pGamepad->isHeld( VirtualGamepad::Up ) )
        m_pPlayer->getComponent<fw::PhysicsBodyComponent>()->m_pBody->applyForceToCenter( vec3(0,0,force) );
    if( m_pGamepad->isHeld( VirtualGamepad::Down ) )
        m_pPlayer->getComponent<fw::PhysicsBodyComponent>()->m_pBody->applyForceToCenter( vec3(0,0,-force) );
    if( m_pGamepad->isHeld( VirtualGamepad::Left ) )
        m_pPlayer->getComponent<fw::PhysicsBodyComponent>()->m_pBody->applyForceToCenter( vec3(-force,0,0) );
    if( m_pGamepad->isHeld( VirtualGamepad::Right ) )
        m_pPlayer->getComponent<fw::PhysicsBodyComponent>()->m_pBody->applyForceToCenter( vec3(force,0,0) );
}

void Physics3DScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    m_pComponentManager->updateTransforms();
    m_pComponentManager->renderMeshes( 0, nullptr );
}
