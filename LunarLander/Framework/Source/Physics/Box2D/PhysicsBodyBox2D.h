#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "Physics/PhysicsBody.h"

namespace fw
{
    class PhysicsBodyBox2D : public PhysicsBody
    {
    public:
        PhysicsBodyBox2D(b2Body* pBody);
        virtual ~PhysicsBodyBox2D();

        // Getters.
        virtual vec3 getPosition() override;
        virtual vec3 getRotation() override;

        // Setters.
        virtual void setTransform(vec3 pos, vec3 rot) override;
        virtual void setAllowSleep(bool allowSleep) override;
        virtual void setLinearDamping(float linearDamping) override;
        virtual void setAngularDamping(float angularDamping) override;
        virtual void limitTo2D() override;

        // Forces.
        virtual void applyForceToCenter(vec3 force) override;
        virtual void applyForceAtWorldPos(vec3 force, vec3 worldPoint) override;

        // Custom box2d methods.
        b2Body* getb2Body() { return m_pBody; }

    public:
        virtual void editor_fillInspectorWindow() override;    protected:
        b2Body* m_pBody = nullptr;
    };
} // namespace fw
