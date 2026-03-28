#include "Framework.h"

#include "GameScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Events/GameEvents.h"
#include "GameComponents/GameSystems.h"
#include "GameComponents/Player2DMovementComponent.h"
#include "Objects/VirtualGamepad.h"

GameScene::GameScene( Game* pGame )
    : fw::Scene( pGame )
    , onRemoveFromGameEventHandler( std::bind(&GameScene::onRemoveFromGameEvent, this, std::placeholders::_1) )
{
    m_pGameCore->getEventManager()->registerListenerFunction<RemoveFromGameEvent>( &onRemoveFromGameEventHandler );

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager(), m_pGameCore->getFramework());

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(0,0,-10), vec3(0,0,0) );
    //m_pCamera = new fw::Camera(this, vec3(3, 30, -100), vec3(3, 0, 0));
#define getMesh pGame->getResources()->get<fw::Mesh>
#define getMaterial pGame->getResources()->get<fw::Material>

    fw::GameObject* pObject;

    pObject = new fw::GameObject(this, "obj");
    pObject->addComponent(new fw::TransformComponent(pObject, vec3(0, -25, 50), vec3(0, 20, 0), 1));
    pObject->addComponent(new fw::RenderComponent(pObject, getMesh("Obj"), getMaterial("Bottle")));
    m_objects.push_back(pObject);
}

GameScene::~GameScene()
{
    m_pGameCore->getEventManager()->unregisterListenerFunction<RemoveFromGameEvent>( &onRemoveFromGameEventHandler );

    for( fw::GameObject* pObject : m_objects )
    {
        delete pObject;
    }

    delete m_pCamera;
    delete m_pGamepad;
}

void GameScene::startFrame( float deltaTime )
{
    // Reset the gamepad.
    m_pGamepad->startFrame();
}

void GameScene::onRemoveFromGameEvent(fw::Event* pEvent)
{
    if( pEvent->getType() == RemoveFromGameEvent::getStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>( pEvent );
        fw::GameObject* pObject = pRemoveFromGameEvent->getGameObject();

        auto it = std::find( m_objects.begin(), m_objects.end(), pObject );
        m_objects.erase( it );

        delete pObject;
    }
}

void GameScene::update( float deltaTime )
{
    UpdatePlayer2DMovementComponents( m_pComponentManager, deltaTime );

    editor_displayObjectList();

    m_pCamera->moveCamera(m_pGamepad->getDirection(), deltaTime, 50.0f);
    m_pCamera->rotateCamera(m_pGamepad->getRotation(), deltaTime, 100.0f);
}

void GameScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    m_pComponentManager->updateTransforms();
    m_pComponentManager->renderMeshes( 0, nullptr );
}

void GameScene::editor_displayObjectList()
{
    ImGui::Begin( "Object List" );

    for( fw::GameObject* pObject : m_objects )
    {
        ImGui::Text( "%s", pObject->getName().c_str() );
    }

    ImGui::End(); // "Object List"
}
