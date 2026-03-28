#include "CoreHeaders.h"

#include "PhysicsBodyJolt.h"
#include "PhysicsWorldJolt.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"

// Disable warning C4291: 'void *JPH::Vec3::operator new(size_t,void *) noexcept': no matching operator delete found; memory will not be freed if initialization throws an exception
#pragma warning(push)
#pragma warning(disable:4291)
#include "Jolt/Jolt.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Body/BodyActivationListener.h"
#pragma warning(pop)

namespace fw
{
    PhysicsBodyJolt::PhysicsBodyJolt(PhysicsWorldJolt* pWorld, JPH::Body* pRigidBody)
    {
        m_pWorld = pWorld;
        m_pBody = pRigidBody;
    }

    PhysicsBodyJolt::~PhysicsBodyJolt()
    {
        JPH::BodyInterface& bodyInterface = m_pWorld->getJoltWorld()->GetBodyInterface();
        bodyInterface.RemoveBody( m_pBody->GetID() );
        bodyInterface.DestroyBody( m_pBody->GetID() );
    }

    vec3 PhysicsBodyJolt::getPosition()
    {
        JPH::RVec3 pos = m_pBody->GetPosition();
        return vec3( pos.GetX(), pos.GetY(), pos.GetZ() );
    }

    vec3 PhysicsBodyJolt::getRotation()
    {
        JPH::Mat44 world = m_pBody->GetWorldTransform().GetRotationSafe();
        mat4 w = mat4( world(0,0), world(1,0), world(2,0), world(3,0),
                       world(0,1), world(1,1), world(2,1), world(3,1),
                       world(0,2), world(1,2), world(2,2), world(3,2),
                       world(0,3), world(1,3), world(2,3), world(3,3) );
        vec3 r = w.getEulerAngles();
        return r;
    }

    void PhysicsBodyJolt::setTransform(vec3 pos, vec3 rot)
    {
    }

    void PhysicsBodyJolt::setAllowSleep(bool allowSleep)
    {
        m_pBody->SetAllowSleeping( allowSleep );
    }

    void PhysicsBodyJolt::setRotation(JPH::PhysicsSystem* pWorld, vec3 rot)
    {
        JPH::Mat44 rotMat = JPH::Mat44::sRotationY(-rot.y/180*PI) * JPH::Mat44::sRotationX(-rot.x/180*PI) * JPH::Mat44::sRotationZ(-rot.z/180*PI);
        JPH::Quat quat = rotMat.GetQuaternion();
        pWorld->GetBodyInterface().SetRotation( m_pBody->GetID(), quat, JPH::EActivation::Activate );
    }

    void PhysicsBodyJolt::applyForceToCenter(vec3 force)
    {
        m_pBody->AddForce( JPH::RVec3(force.x, force.y, force.z) );
    }
} // namespace fw
