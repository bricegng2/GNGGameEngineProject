#pragma once

class Game;
class RemoveFromGameEvent;
class VirtualGamepad;

class IslandScene : public fw::Scene
{
public:
    IslandScene(Game* pGame);
    virtual ~IslandScene();

    virtual void startFrame(float deltaTime);
    void onRemoveFromGameEvent(fw::Event* pEvent);
    virtual void update(float deltaTime);
    virtual void draw();

    void spawnBox();

    void editor_displayObjectList();

    fw::EventManager::ListenerFunction onRemoveFromGameEventHandler;

    void removeObject(fw::GameObject* object);

protected:
    // GameObjects and Helpers.
    std::vector<fw::GameObject*> m_objects;
    std::vector<fw::GameObject*> m_boxes;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    fw::vec3 m_cameraPos;
    fw::GameObject* m_pPlayer = nullptr;

    Game* m_pGame = nullptr;

    fw::PhysicsWorld* m_pPhysicsWorld = nullptr;

    int m_boxCount = 0;

    bool m_keyboardCameraControllerOn = false;
};
