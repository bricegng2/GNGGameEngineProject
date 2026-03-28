#pragma once

#include "Math/Vector.h"
#include "Physics/PhysicsTypes.h"

namespace fw
{
    class EventManager;
    class GameObject;
    class Material;
    class PhysicsBody;
    class TransformComponent;
    class Uniforms;

    class PhysicsWorld
    {
    public:
        virtual ~PhysicsWorld() = 0 {}

        virtual void update(float deltaTime) = 0;
        virtual void setGravity(vec3 gravity) = 0;

        virtual PhysicsBody* createBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject, fw::ShapeType shapeType) = 0;
        virtual void createJoint(PhysicsBody* pBody, vec3 pos) = 0;

        virtual void destroyBody(PhysicsBody* pBody) = 0;
    };

    enum class PhysicsWorldType
    {
        Box2D,
        Jolt,
    };

    PhysicsWorld* createPhysicsWorld(PhysicsWorldType type, EventManager* pEventManager);
} // namespace fw
