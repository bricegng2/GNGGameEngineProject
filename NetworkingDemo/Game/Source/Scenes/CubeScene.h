#pragma once

class Game;
class Player;
class RemoveFromGameEvent;
class VirtualGamepad;

class CubeScene : public fw::Scene, public fw::EventListener
{
public:
    CubeScene(Game* pGame);
    virtual ~CubeScene();

    virtual void startFrame(float deltaTime) override;
    virtual void onEvent(fw::Event* pEvent) override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;

    void editor_displayObjectList();

protected:
    // GameObjects and Helpers.
    std::vector<fw::GameObject*> m_objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    Player* m_pPlayer = nullptr;

    float m_totalTimePassed = 0;
};
