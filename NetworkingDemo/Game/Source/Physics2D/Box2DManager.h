#pragma once

class b2World;
class Box2DContactListener;
class Box2DDebugDraw;

class Box2DManager
{
public:
    Box2DManager(fw::Material* pMaterial, fw::Camera* pCamera);
    virtual ~Box2DManager();

    void update(float deltaTime);

    b2World* getWorld() { return m_pWorld; }

    b2Body* getWorldBody() { return m_pWorldBody; }

protected:
    b2World* m_pWorld;
    Box2DContactListener* m_pContactListener;
    Box2DDebugDraw* m_pDebugDraw;

    float m_unusedTime;

    b2Body* m_pWorldBody;
};
