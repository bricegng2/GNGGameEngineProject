#include "Framework.h"
#include "PhysicsScene.h"
#include "Game.h"
#include "Objects/VirtualGamepad.h"

PhysicsScene::PhysicsScene(Game* pGame)
    : fw::Scene( pGame )
{
    fw::ResourceManager* pResources = pGame->getResources();

    m_pPhysicsWorld = fw::createPhysicsWorld( fw::PhysicsWorldType::Box2D, m_pGameCore->getEventManager() );
    //m_pPhysicsWorld->createDebugDraw( pGame->getUniforms(), pResources->get<fw::Material>("VertexColor") );

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(5,5,-10), vec3(5,5,0) );

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager(), m_pGameCore->getFramework());

    m_pPlayer = new fw::GameObject( this, "Player" );
    m_pPlayer->addComponent( new fw::TransformComponent( m_pPlayer, vec3(6,5,0), vec3(0,0,0), vec3(1,1,1) ) );
    m_pPlayer->addComponent( new fw::RenderComponent( m_pPlayer, pResources->get<fw::Mesh>("Sprite"), pResources->get<fw::Material>("MegaMan") ) );
    m_pPlayer->addComponent( new fw::PhysicsBodyComponent( m_pPlayer, m_pPhysicsWorld, true, fw::ShapeType::Box ) );
    m_objects.push_back( m_pPlayer );

    fw::GameObject* pGO;
    pGO = new fw::GameObject( this, "Ground" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(6,0,0), vec3(0,0,0), vec3(10,1,1) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Square"), pResources->get<fw::Material>("Blue") ) );
    pGO->addComponent( new fw::PhysicsBodyComponent( pGO, m_pPhysicsWorld, false, fw::ShapeType::Box ) );
    m_objects.push_back( pGO );

    pGO = new fw::GameObject( this, "Ground" );
    pGO->addComponent( new fw::TransformComponent( pGO, vec3(6.8f,1,0), vec3(0,0,0), vec3(1,1,1) ) );
    pGO->addComponent( new fw::RenderComponent( pGO, pResources->get<fw::Mesh>("Square"), pResources->get<fw::Material>("Blue") ) );
    pGO->addComponent( new fw::PhysicsBodyComponent( pGO, m_pPhysicsWorld, false, fw::ShapeType::Box ) );
    m_objects.push_back( pGO );
}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::startFrame(float deltaTime)
{
    // Reset the gamepad.
    m_pGamepad->startFrame();
}

void PhysicsScene::update(float deltaTime)
{
    //Editor_DisplayObjectList();
    m_pPhysicsWorld->update( deltaTime );
    m_pComponentManager->syncPhysicsObjects();
}

void PhysicsScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    m_pComponentManager->updateTransforms();
    m_pComponentManager->renderMeshes( 0, nullptr );
}
