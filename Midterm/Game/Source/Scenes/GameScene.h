#pragma once

class Game;
class Player;
class RemoveFromGameEvent;
class GameScene;
class VirtualGamepad;

class GameScene : public fw::Scene, public fw::EventListener
{
public:
    GameScene(Game* pGame);
    virtual ~GameScene();

    virtual void startFrame(float deltaTime);
    virtual void onEvent(fw::Event* pEvent) override;
    virtual void update(float deltaTime);
    virtual void draw();

    void editor_displayObjectList();

protected:
    // GameObjects and Helpers.
    std::vector<fw::GameObject*> m_objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    Player* m_pPlayer = nullptr;
};
