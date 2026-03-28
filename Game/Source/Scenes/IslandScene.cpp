#include "Framework.h"

#include "IslandScene.h"
#include "DataTypes.h"
#include "Game.h"
#include "Events/GameEvents.h"
#include "GameComponents/GameSystems.h"
#include "GameComponents/Player3DMovementComponent.h"
#include "Objects/VirtualGamepad.h"
#include <Meshes/Shapes.h>

IslandScene::IslandScene(Game* pGame)
    : fw::Scene(pGame)
    , onRemoveFromGameEventHandler(std::bind(&IslandScene::onRemoveFromGameEvent, this, std::placeholders::_1))
{
    ShowCursor(FALSE);

    m_pGameCore->getEventManager()->registerListenerFunction<RemoveFromGameEvent>(&onRemoveFromGameEventHandler);

    m_pGame = pGame;

    m_pPhysicsWorld = fw::createPhysicsWorld(fw::PhysicsWorldType::Jolt, m_pGameCore->getEventManager());

    // Create a gamepad.
    m_pGamepad = new VirtualGamepad(m_pGameCore->getEventManager(), m_pGameCore->getFramework());

    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(5, 5, -5), vec3(5, 0, 5));

#define getMesh pGame->getResources()->get<fw::Mesh>
#define getMaterial pGame->getResources()->get<fw::Material>

    fw::GameObject* pObject;

    vec3 playerPosition = vec3(26, 0, 27);
    playerPosition.y = getHeightAtXZ(playerPosition.x, playerPosition.z); // add 0.5 to the height so the player is above the ground

    pObject = new fw::GameObject(this, "player");
    pObject->addComponent(new fw::TransformComponent(pObject, playerPosition, vec3(0, 0, 0), 0.3));
    pObject->addComponent(new fw::RenderComponent(pObject, getMesh("Cube"), getMaterial("Bottle")));
    //pObject->addComponent(new fw::PlayerComponent(pObject, getHeightMapPixelPositions()));
    pObject->addComponent(new Player3DMovementComponent(pObject, m_pGamepad));
    pObject->addComponent(new fw::CameraComponent(pObject, new fw::FreeCamera(this, vec3(5, 5, -5))));
    m_objects.push_back(pObject);

    pObject = new fw::GameObject(this, "water");
    pObject->addComponent(new fw::TransformComponent(pObject, vec3(-5, 0.3, -5), vec3(-90, 0, 0), 1));
    pObject->addComponent(new fw::RenderComponent(pObject, getMesh("Plane"), getMaterial("Water")));
    m_objects.push_back(pObject);

    pObject = new fw::GameObject(this, "height map");
    pObject->addComponent(new fw::TransformComponent(pObject, vec3(0, 0, 0), vec3(0, 0, 0), 1));
    pObject->addComponent(new fw::RenderComponent(pObject, getMesh("HeightMap"), getMaterial("IslandLighting")));
    //pObject->addComponent(new fw::PhysicsBodyComponent(pObject, m_pPhysicsWorld, false, fw::ShapeType::HeightMap));
    m_objects.push_back(pObject);

    for (int i = 0; i < fw::Random::randomInt(20, 30); i++)
    {
        pObject = new fw::GameObject(this, "tree" + std::to_string(i + 1));
        pObject->addComponent(new fw::TransformComponent(pObject, vec3(getHeightMapPixelPosition()), vec3(0, fw::Random::randomFloat(0.0f, 360.0f), 0), fw::Random::randomFloat(0.8f, 1.0f))); // the tree model is massive so it has to be below 0.8
        pObject->addComponent(new fw::RenderComponent(pObject, getMesh("Tree"), getMaterial("TreeLighting")));
        m_objects.push_back(pObject);
    }
}

IslandScene::~IslandScene()
{
    m_pGameCore->getEventManager()->unregisterListenerFunction<RemoveFromGameEvent>(&onRemoveFromGameEventHandler);

    for (fw::GameObject* pObject : m_objects)
    {
        delete pObject;
    }

    delete m_pCamera;
    delete m_pGamepad;
}

void IslandScene::startFrame(float deltaTime)
{
    // Reset the gamepad.
    m_pGamepad->startFrame();
}

void IslandScene::onRemoveFromGameEvent(fw::Event* pEvent)
{
    if (pEvent->getType() == RemoveFromGameEvent::getStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->getGameObject();

        auto it = std::find(m_objects.begin(), m_objects.end(), pObject);
        m_objects.erase(it);

        delete pObject;
    }
}

void IslandScene::update(float deltaTime)
{
    update3DPlayerMovementComponents(m_pComponentManager, deltaTime);

    spawnBox();

    editor_displayObjectList();

    fw::CameraComponent* pCamera = m_objects[0]->getComponent<fw::CameraComponent>();

    pCamera->cameraRotation(m_pGamepad->getMouseDirection(), deltaTime, 100.0f);
    //pCamera->cameraRotation(m_pGamepad->getRotation(), deltaTime, 100.0f);

    vec3 playerPosition = m_objects[0]->getComponent<fw::TransformComponent>()->m_position;
    pCamera->setPosition(playerPosition);

    vec3 rot = m_objects[0]->getComponent<fw::TransformComponent>()->m_rotation;
    rot.y = pCamera->getYaw();
    m_objects[0]->getComponent<fw::TransformComponent>()->m_rotation = rot;

    // this isnt being used right now, the light just goes in a circle
    m_pGameCore->getUniforms()->set("u_cameraPos", playerPosition);

    ImGui::Begin("Player Position");
    ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f", playerPosition.x, playerPosition.y, playerPosition.z);
    ImGui::End();

    static bool showCursor = false;
    if (m_pGamepad->wasPressed(VirtualGamepad::Mask::Space))
    {
        showCursor = true;
        ShowCursor(showCursor);
    }
    if (m_pGamepad->wasReleased(VirtualGamepad::Mask::Space))
    {
        showCursor = false;
        ShowCursor(showCursor);
    }

    if (showCursor == false)
    {
        SetCursorPos(1280 / 2, 720 / 2);
    }

    // New ImGui box for some text  
    ImGui::Begin("notes:");
    ImGui::Text("hold space to show mouse cursor");
    ImGui::Text("e - create boxes");
    ImGui::Text("q - destroy boxes");
    ImGui::Text("see method spawnBox in IslandScene.cpp at line 155 to see how box spawning/destroying works");
    ImGui::End();
}

void IslandScene::draw()
{
    int viewID = 0;

    // Program the view and proj uniforms from the camera.
    m_objects[0]->getComponent<fw::CameraComponent>()->m_pCamera->enable(viewID);

    // Draw all objects.
    m_pComponentManager->updateTransforms();
    m_pComponentManager->renderMeshes(0, nullptr);
}

void IslandScene::spawnBox()
{
#define getMesh m_pGame->getResources()->get<fw::Mesh>
#define getMaterial m_pGame->getResources()->get<fw::Material>

    if (m_pGamepad->wasPressed(VirtualGamepad::Mask::CreateBox))
    {
        m_boxCount++;
        vec3 playerPosition = m_objects[0]->getComponent<fw::TransformComponent>()->m_position;
        
        fw::CameraComponent* pCamera = m_objects[0]->getComponent<fw::CameraComponent>();
        vec3 cameraForward = pCamera->getForward();
        vec3 boxPosition = playerPosition + cameraForward;
        boxPosition.y = getHeightAtXZ(boxPosition.x, boxPosition.z);
        boxPosition.y += 0.3f; // add 0.3f to the height so the box is above the ground
        
        fw::GameObject* pObject = new fw::GameObject(this, "box" + std::to_string(m_boxCount));
        pObject->addComponent(new fw::TransformComponent(pObject, boxPosition, vec3(0, 0, 0), 1));
        pObject->addComponent(new fw::RenderComponent(pObject, getMesh("Cube"), getMaterial("Bottle")));
        m_boxes.push_back(pObject);
    }

    else if (m_pGamepad->wasPressed(VirtualGamepad::Mask::DestroyBox))
    {
        float playerRadius = 0.7f;
        float boxRadius = 1.0f;

        vec3 playerPosition = m_objects[0]->getComponent<fw::TransformComponent>()->m_position;
        playerPosition.z += 1.0f; // add 1.0f so the hitbox is in front of the player

        fw::CameraComponent* pCamera = m_objects[0]->getComponent<fw::CameraComponent>();
        vec3 cameraForward = pCamera->getForward();
        playerPosition += cameraForward;

        for (int i = 0; i < m_boxes.size(); i++)
        {
            float distance = (playerPosition - m_boxes[i]->getComponent<fw::TransformComponent>()->m_position).length();

            if (distance < (playerRadius + boxRadius))
            {
                removeObject(m_boxes[i]);
                m_boxCount--;
                break;
            }
        }
    }
}

void IslandScene::editor_displayObjectList()
{
    ImGui::Begin("Object List");

    for (fw::GameObject* pObject : m_objects)
    {
        ImGui::Text("%s", pObject->getName().c_str());
    }

    for (fw::GameObject* pObject : m_boxes)
    {
        if (m_boxes.size() >= 1)
        {
            ImGui::Text("%s", pObject->getName().c_str());
        }
    }

    ImGui::End(); // "Object List"
}

void IslandScene::removeObject(fw::GameObject* object)
{
    auto it = std::find(m_boxes.begin(), m_boxes.end(), object);
    if (it != m_boxes.end())
    {
        delete* it; // Clean up memory.
        m_boxes.erase(it);
    }
}