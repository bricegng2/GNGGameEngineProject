#pragma once

class Game;
class Player;
class VirtualGamepad;

class LunarLanderScene : public fw::Scene
{
public:
    LunarLanderScene(Game* pGame);
    ~LunarLanderScene();

    virtual void startFrame(float deltaTime) override;
    //virtual void onEvent(fw::Event* pEvent) override;
    virtual void update(float deltaTime) override;
    void checkForCollectibleCollision();

    virtual void draw() override;

    void editor_displayObjectList();

protected:
    // Physics World.
    fw::PhysicsWorld* m_pPhysicsWorld = nullptr;

    // Objects.
    std::vector<fw::GameObject*> m_objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    fw::GameObject* m_pPlayer = nullptr;

    // Rotation Test.
    fw::GameObject* m_pRotatingPhysicsObject = nullptr;
    fw::GameObject* m_pNonRotatingPhysicsObject = nullptr;

    fw::GameObject* m_pEngineLeft = nullptr;
    fw::GameObject* m_pEngineRight = nullptr;

    std::vector<fw::GameObject*> m_collectiblesActive;
    std::vector<fw::GameObject*> m_collectiblesInactive;
    
    float timer = 0;

    int m_score = 0;
};
