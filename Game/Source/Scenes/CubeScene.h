#pragma once

class Game;
class RemoveFromGameEvent;
class VirtualGamepad;

class CubeScene : public fw::Scene
{
public:
    CubeScene(Game* pGame);
    virtual ~CubeScene();

    virtual void startFrame(float deltaTime) override;
    void onRemoveFromGameEvent(fw::Event* pEvent);
    virtual void update(float deltaTime) override;
    virtual void draw() override;

    void editor_displayObjectList();

protected:
    fw::EventManager::ListenerFunction onRemoveFromGameEventHandler;

    // GameObjects and Helpers.
    std::vector<fw::GameObject*> m_objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    fw::GameObject* m_pPlayer = nullptr;

    float m_totalTimePassed = 0;
};
