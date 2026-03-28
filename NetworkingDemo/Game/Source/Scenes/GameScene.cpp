#include "Framework.h"

#include "GameScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Events/GameEvents.h"
#include "Objects/Player.h"
#include "Objects/VirtualGamepad.h"

GameScene::GameScene( Game* pGame )
    : fw::Scene( pGame )
{
    m_pGameCore->getEventManager()->registerListener<RemoveFromGameEvent>( this );

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad( m_pGameCore->getEventManager() );

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(5,5,0) );

#define getMesh pGame->getResources()->get<fw::Mesh>
#define getMaterial pGame->getResources()->get<fw::Material>

    m_pPlayer = new Player( this, m_pGamepad, "Player", vec3(6,5,0), getMesh("Sprite"), getMaterial("MegaMan") );
    m_objects.push_back( m_pPlayer );

    m_objects.push_back( new fw::GameObject( this, "Object 1", vec3(0,0,0), getMesh("Triangle"), getMaterial("VertexColor") ) );
    m_objects.push_back( new fw::GameObject( this, "Object 2", vec3(10,10,0), getMesh("Triangle"), getMaterial("Blue") ) );
    m_objects.push_back( new fw::GameObject( this, "Object 3", vec3(5,5,0), getMesh("Square"), getMaterial("VertexColor") ) );
    m_objects.push_back( new fw::GameObject( this, "Object 4", vec3(1,1,0), getMesh("Square"), getMaterial("VertexColor") ) );
    m_objects.push_back( new fw::GameObject( this, "Object 5", vec3(1,9,0), getMesh("Square"), getMaterial("Blue") ) );
}

GameScene::~GameScene()
{
    m_pGameCore->getEventManager()->unregisterListener<RemoveFromGameEvent>( this );

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

void GameScene::onEvent(fw::Event* pEvent)
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
    for( fw::GameObject* pObject : m_objects )
    {
        pObject->update( deltaTime );
    }

    m_pCamera->update( deltaTime );

    editor_displayObjectList();
}

void GameScene::draw()
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

void GameScene::editor_displayObjectList()
{
    ImGui::Begin( "Object List" );

    for( fw::GameObject* pObject : m_objects )
    {
        ImGui::Text( "%s", pObject->getName().c_str() );
    }

    ImGui::End(); // "Object List"
}
