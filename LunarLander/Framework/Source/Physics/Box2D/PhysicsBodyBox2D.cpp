#include "CoreHeaders.h"

#include "PhysicsBodyBox2D.h"
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

    void PhysicsBodyBox2D::setLinearDamping(float linearDamping)
    {
        m_pBody->SetLinearDamping( linearDamping );
    }

    void PhysicsBodyBox2D::setAngularDamping(float angularDamping)
    {
        m_pBody->SetAngularDamping( angularDamping );
    }

    void PhysicsBodyBox2D::limitTo2D()
    {
    }

    void PhysicsBodyBox2D::applyForceToCenter(vec3 force)
    {
        m_pBody->ApplyForceToCenter( b2Vec2(force.x, force.y), true );
    }

    void PhysicsBodyBox2D::applyForceAtWorldPos(vec3 force, vec3 worldPoint)
    {
        m_pBody->ApplyForce( b2Vec2(force.x, force.y), b2Vec2(worldPoint.x, worldPoint.y), true );
    }

    void PhysicsBodyBox2D::editor_fillInspectorWindow()
    {
        bool fixed = m_pBody->IsFixedRotation();
        if( ImGui::Checkbox( "Fixed Rotation", &fixed ) )
        {
            m_pBody->SetFixedRotation( fixed );
        }
    }
} // namespace fw
