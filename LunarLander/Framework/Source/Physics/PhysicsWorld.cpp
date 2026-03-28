#include "CoreHeaders.h"

#include "Physics/Box2D/PhysicsWorldBox2D.h"
#include "Physics/Jolt/PhysicsWorldJolt.h"
#include "Physics/PhysicsWorld.h"

namespace fw
{
    PhysicsWorld* createPhysicsWorld(PhysicsWorldType type, EventManager* pEventManager)
    {
        switch( type )
        {
        case PhysicsWorldType::Box2D:
            return new PhysicsWorldBox2D( pEventManager );

        case PhysicsWorldType::Jolt:
            return new PhysicsWorldJolt( pEventManager );

        default:
            assert( false );
        };

        return nullptr;
    }
} // namespace fw