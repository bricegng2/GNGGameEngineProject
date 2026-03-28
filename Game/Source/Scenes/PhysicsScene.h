#pragma once

#include "GameScene.h"

class PhysicsScene : public fw::Scene
{
public:
    PhysicsScene(Game* pGame);
    ~PhysicsScene();

    virtual void startFrame(float deltaTime) override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;

protected:
    // Objects.
    fw::PhysicsWorld* m_pPhysicsWorld = nullptr;
    std::vector<fw::GameObject*> m_objects;

    VirtualGamepad* m_pGamepad = nullptr;

    fw::Camera* m_pCamera = nullptr;
    fw::GameObject* m_pPlayer = nullptr;
};
