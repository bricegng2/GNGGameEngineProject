#include "CoreHeaders.h"

#include "PhysicsWorldJolt.h"
#include "PhysicsBodyJolt.h"
#include "EventSystem/Events.h"
#include "EventSystem/EventManager.h"
#include "Components/Component.h"

#include "JoltHelpers.h"

// Disable warning C4291: 'void *JPH::Vec3::operator new(size_t,void *) noexcept': no matching operator delete found; memory will not be freed if initialization throws an exception
#pragma warning(push)
#pragma warning(disable:4291)
#include "Jolt/Jolt.h"
#include "JoltPhysics/Jolt/Physics/PhysicsSystem.h"
#pragma warning(pop)

namespace fw
{
    PhysicsWorldJolt::PhysicsWorldJolt(EventManager* pEventManager)
    {
        m_pWorldBundle = createJoltWorld( pEventManager );
    }

    PhysicsWorldJolt::~PhysicsWorldJolt()
    {
        destroyJoltWorld( m_pWorldBundle );
    }

    void PhysicsWorldJolt::update(float deltaTime)
    {
        updateJoltWorld( m_pWorldBundle, deltaTime );
    }

    void PhysicsWorldJolt::setGravity(vec3 gravity)
    {
        m_pWorldBundle->m_pWorld->SetGravity( JPH::Vec3Arg(gravity.x, gravity.y, gravity.z) );
    }

    PhysicsBody* PhysicsWorldJolt::createBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject, fw::ShapeType shapeType)
    {
        JPH::Body* pRigidBody = createJoltBody( m_pWorldBundle->m_pWorld, pTransform->m_position, pTransform->m_rotation, pTransform->m_scale, isDynamic, density, pGameObject, shapeType );

        // Create a wrapper instance.
        PhysicsBodyJolt* pBody = new PhysicsBodyJolt( this, pRigidBody );
        return pBody;
    }

    void PhysicsWorldJolt::createJoint(PhysicsBody* pBody, vec3 pos)
    {
        assert( false ); // implement this.
    }

    void PhysicsWorldJolt::destroyBody(PhysicsBody* pBody)
    {
        destroyJoltBody( m_pWorldBundle->m_pWorld, static_cast<PhysicsBodyJolt*>(pBody)->getJoltBody() );
    }

    JPH::PhysicsSystem* PhysicsWorldJolt::getJoltWorld()
    {
        return m_pWorldBundle->m_pWorld;
    }
} // namespace fw
