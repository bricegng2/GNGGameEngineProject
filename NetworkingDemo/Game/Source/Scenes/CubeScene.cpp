#include "Framework.h"

#include "CubeScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Events/GameEvents.h"
#include "Objects/Player.h"
#include "Objects/VirtualGamepad.h"

#define getMesh pGame->getResources()->get<fw::Mesh>
#define getMaterial pGame->getResources()->get<fw::Material>

CubeScene::CubeScene(Game* pGame)
    : fw::Scene( pGame )
{
    m_pGameCore->getEventManager()->registerListener<RemoveFromGameEvent>( this );

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager() );

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(0,0,0) );

    m_objects.push_back( new fw::GameObject( this, "Object 1", vec3(0,0,0), getMesh("Cube"), getMaterial("MegaMan") ) );
}

CubeScene::~CubeScene()
{
    m_pGameCore->getEventManager()->unregisterListener<RemoveFromGameEvent>( this );

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

void CubeScene::onEvent(fw::Event* pEvent)
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
    for( fw::GameObject* pObject : m_objects )
    {
        pObject->update( deltaTime );
    }

    m_pCamera->update( deltaTime );

    m_totalTimePassed += deltaTime * 50;
    m_objects[0]->setRotation( vec3(m_totalTimePassed,m_totalTimePassed*0.5f,m_totalTimePassed*0.25f) );

    editor_displayObjectList();
}

void CubeScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_pCamera->enable( viewID );

    // Draw all objects.
    for( fw::GameObject* pObject : m_objects )
    {
        pObject->draw( viewID );
    }
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
