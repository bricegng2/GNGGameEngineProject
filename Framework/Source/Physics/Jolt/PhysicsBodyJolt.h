#pragma once

#include "Physics/PhysicsBody.h"

namespace JPH
{
    class PhysicsSystem;
    class Body;
}

namespace fw
{
    class PhysicsWorldJolt;

    class PhysicsBodyJolt : public PhysicsBody
    {
    public:
        PhysicsBodyJolt(PhysicsWorldJolt* pWorld, JPH::Body* pRigidBody);
        virtual ~PhysicsBodyJolt() override;

        // Getters.
        virtual vec3 getPosition() override;
        virtual vec3 getRotation() override;

        // Setters.
        virtual void setTransform(vec3 pos, vec3 rot) override;
        virtual void setAllowSleep(bool allowSleep) override;
        void setRotation(JPH::PhysicsSystem* pWorld, vec3 rot);

        // Forces.
        virtual void applyForceToCenter(vec3 force) override;

        // Custom box2d methods.
        JPH::Body* getJoltBody() { return m_pBody; }

    protected:
        PhysicsWorldJolt* m_pWorld = nullptr;
        JPH::Body* m_pBody = nullptr;
    };
} // namespace fw
