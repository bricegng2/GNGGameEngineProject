#pragma once

#include "Physics/PhysicsWorld.h"

namespace JPH
{
    class PhysicsSystem;
    class TempAllocatorImpl;
    class JobSystemThreadPool;
}

namespace fw
{
    class EventManager;
    class BPLayerInterfaceImpl;
    class JoltWorldBundle;
    class ObjectVsBroadPhaseLayerFilterImpl;
    class ObjectLayerPairFilterImpl;

    class PhysicsWorldJolt : public PhysicsWorld
    {
    public:
        PhysicsWorldJolt(EventManager* pEventManager);
        virtual ~PhysicsWorldJolt();

        virtual void update(float deltaTime) override;
        virtual void setGravity(vec3 gravity) override;

        virtual PhysicsBody* createBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject, fw::ShapeType shapeType) override;
        virtual void createJoint(PhysicsBody* pBody, vec3 pos) override;

        virtual void destroyBody(PhysicsBody* pBody) override;

        // Getters
        JPH::PhysicsSystem* getJoltWorld();

    protected:
        JoltWorldBundle* m_pWorldBundle;
    };
} // namespace fw
