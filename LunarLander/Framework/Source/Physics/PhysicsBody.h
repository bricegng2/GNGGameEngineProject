#pragma once

#include "Math/Vector.h"

namespace fw
{
    class PhysicsBody
    {
    public:
        virtual ~PhysicsBody() = 0 {}

        // Getters.
        virtual vec3 getPosition() = 0;
        virtual vec3 getRotation() = 0;

        // Setters.
        virtual void setTransform(vec3 pos, vec3 rot) = 0;
        virtual void setAllowSleep(bool allowSleep) = 0;
        virtual void setLinearDamping(float linearDamping) = 0;
        virtual void setAngularDamping(float angularDamping) = 0;
        virtual void limitTo2D() = 0;
        // Forces.
        virtual void applyForceToCenter(vec3 force) = 0;
        virtual void applyForceAtWorldPos(vec3 force, vec3 worldPoint) = 0;

    public:
        virtual void editor_fillInspectorWindow() = 0;
    };
} // namespace fw
