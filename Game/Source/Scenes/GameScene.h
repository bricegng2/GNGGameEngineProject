#pragma once

class Game;
class RemoveFromGameEvent;
class GameScene;
class VirtualGamepad;

class GameScene : public fw::Scene
{
public:
    GameScene(Game* pGame);
    virtual ~GameScene();

    virtual void startFrame(float deltaTime);
    void onRemoveFromGameEvent(fw::Event* pEvent);
    virtual void update(float deltaTime);
    virtual void draw();

    void editor_displayObjectList();

    fw::EventManager::ListenerFunction onRemoveFromGameEventHandler;

protected:
    // GameObjects and Helpers.
    std::vector<fw::GameObject*> m_objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    fw::GameObject* m_pPlayer = nullptr;
};
