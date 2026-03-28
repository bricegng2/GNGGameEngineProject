#pragma once

#include "GameScene.h"

class Physics3DScene : public fw::Scene
{
public:
    Physics3DScene(Game* pGame);
    ~Physics3DScene();

    virtual void startFrame(float deltaTime) override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;

protected:
    // Objects.
    fw::PhysicsWorld* m_pPhysicsWorld = nullptr;
    std::vector<fw::GameObject*> m_Objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    fw::GameObject* m_pPlayer = nullptr;

    // Rotation Test.
    fw::GameObject* m_pRotatingPhysicsObject = nullptr;
    fw::GameObject* m_pNonRotatingPhysicsObject = nullptr;
};
