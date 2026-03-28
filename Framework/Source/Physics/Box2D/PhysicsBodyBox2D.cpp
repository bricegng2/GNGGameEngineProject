#include "PhysicsBodyBox2D.h"
#include "Objects/GameObject.h"
#include "EventSystem/EventManager.h"
#include "EventSystem/Events.h"
#include "../Libraries/imgui/imgui.h"

namespace fw
{
    PhysicsBodyBox2D::PhysicsBodyBox2D(b2Body* pBody)
        : m_pBody( pBody )
    {
    }

    PhysicsBodyBox2D::~PhysicsBodyBox2D()
    {
    }

    vec3 PhysicsBodyBox2D::getPosition()
    {
        b2Vec2 pos = m_pBody->GetPosition();
        return vec3( pos.x, pos.y );
    }

    vec3 PhysicsBodyBox2D::getRotation()
    {
        float angle = m_pBody->GetAngle();
        return vec3( 0, 0, -angle * 180.0f / PI );
    }

    void PhysicsBodyBox2D::setTransform(vec3 pos, vec3 rot)
    {
        m_pBody->SetTransform( b2Vec2(pos.x, pos.y), -rot.z*PI/180.0f );
        m_pBody->SetAwake( true );
    }

    void PhysicsBodyBox2D::setAllowSleep(bool allowSleep)
    {
        m_pBody->SetSleepingAllowed( allowSleep );
    }

    void PhysicsBodyBox2D::applyForceToCenter(vec3 force)
    {
        m_pBody->ApplyForceToCenter( b2Vec2(force.x, force.y), true );
    }
} // namespace fw
