#pragma once

#include "Physics/PhysicsWorld.h"

namespace JPH
{
    class PhysicsSystem;
    class TempAllocatorImpl;
    class JobSystemThreadPool;
    class Body;
}

namespace fw
{
    class EventManager;
    class GameObject;
    class BPLayerInterfaceImpl;
    class ObjectVsBroadPhaseLayerFilterImpl;
    class ObjectLayerPairFilterImpl;

    class JoltWorldBundle
    {
    public:
        JPH::PhysicsSystem* m_pWorld = nullptr;
        JPH::JobSystemThreadPool* m_pJobSystem = nullptr;
        JPH::TempAllocatorImpl* m_pTempAllocator = nullptr;

        BPLayerInterfaceImpl* m_pBroadphaseLayerInterface = nullptr;
        ObjectVsBroadPhaseLayerFilterImpl* m_pObjectVsBroadphaseLayerFilter = nullptr;
        ObjectLayerPairFilterImpl* m_pObjectVsObjectLayerFilter = nullptr;
    };

    JoltWorldBundle* createJoltWorld(EventManager* pEventManager);
    void updateJoltWorld(JoltWorldBundle* pBundle, float deltaTime);
    void destroyJoltWorld(JoltWorldBundle* pBundle);

    JPH::Body* createJoltBody(JPH::PhysicsSystem* pWorld, vec3 pos, vec3 rot, vec3 scale, bool isDynamic, float density, GameObject* pGameObject, ShapeType shapeType);
    void destroyJoltBody(JPH::PhysicsSystem* pWorld, JPH::Body* pBody);
} // namespace fw
