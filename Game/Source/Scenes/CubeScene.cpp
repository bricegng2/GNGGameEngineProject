#include "Framework.h"

#include "CubeScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Events/GameEvents.h"
#include "Objects/VirtualGamepad.h"

#define getMesh pGame->getResources()->get<fw::Mesh>
#define getMaterial pGame->getResources()->get<fw::Material>

CubeScene::CubeScene(Game* pGame)
    : fw::Scene( pGame )
    , onRemoveFromGameEventHandler( std::bind(&CubeScene::onRemoveFromGameEvent, this, std::placeholders::_1) )
{
    m_pGameCore->getEventManager()->registerListenerFunction<RemoveFromGameEvent>( &onRemoveFromGameEventHandler );

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager(), m_pGameCore->getFramework());

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(0,0,-10), vec3(0,0,0) );

    fw::GameObject* pObject = new fw::GameObject( this, "Object 1" );
    pObject->addComponent( new fw::TransformComponent( pObject, 0, 0, 1 ) );
    pObject->addComponent( new fw::RenderComponent( pObject, getMesh("D6"), getMaterial("MegaMan") ) );
    m_objects.push_back( pObject );
}

CubeScene::~CubeScene()
{
    m_pGameCore->getEventManager()->unregisterListenerFunction<RemoveFromGameEvent>( &onRemoveFromGameEventHandler );

    for( fw::GameObject* pObject : m_objects )
    {
        delete pObject;
    }

    delete m_pCamera;
    delete m_pGamepad;
}

void CubeScene::startFrame(float deltaTime)
{
    // Reset the gamepad.
    m_pGamepad->startFrame();
}

void CubeScene::onRemoveFromGameEvent(fw::Event* pEvent)
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

void CubeScene::update(float deltaTime)
{
    m_totalTimePassed += deltaTime * 50;
    m_objects[0]->getComponent<fw::TransformComponent>()->m_rotation = vec3(m_totalTimePassed,m_totalTimePassed*0.5f,m_totalTimePassed*0.25f);

    editor_displayObjectList();
}

void CubeScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    m_pComponentManager->updateTransforms();
    m_pComponentManager->renderMeshes( 0, nullptr );
}

void CubeScene::editor_displayObjectList()
{
    ImGui::Begin( "Object List" );

    for( fw::GameObject* pObject : m_objects )
    {
        ImGui::Text( "%s", pObject->getName().c_str() );
    }

    ImGui::End(); // "Object List"
}
