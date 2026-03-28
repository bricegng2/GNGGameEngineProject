#include "Framework.h"

#include "DataTypes.h"
#include "Events/GameEvents.h"
#include "MeteorObject.h"

MeteorObject::MeteorObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
    : MidtermBaseObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_destroyed = false;

    //m_pPhysicsBody->SetTransform(b2Vec2(0.0f, 0.0f), 0.0f);
}

MeteorObject::~MeteorObject()
{
}

void MeteorObject::reset()
{
    MidtermBaseObject::reset();
    removeFromScene();
}

void MeteorObject::removeFromScene()
{
    MidtermBaseObject::removeFromScene();

    b2Body* pBody = getPhysicsBody();
    pBody->SetEnabled( false );
    pBody->SetLinearVelocity( b2Vec2(0,0) );
    pBody->SetTransform( b2Vec2(-10000,-10000), 0 );

    if( m_pPool )
    {
        m_pPool->push_back( this );
    }

    m_destroyed = false;
}

void MeteorObject::update(float deltatime)
{
    MidtermBaseObject::update( deltatime );

    if( m_destroyed || m_position.y < -10 )
    {
        removeFromScene();
    }
}

void MeteorObject::setPool(std::vector<MidtermBaseObject*>* pPool)
{
    m_pPool = pPool;
}

void MeteorObject::destroy()
{
    assert( m_pScene != nullptr );

    RemoveFromGameEvent* pEvent = new RemoveFromGameEvent( this );
    m_pScene->getGameCore()->getEventManager()->addEvent( pEvent );
}

void MeteorObject::beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal)
{
    m_pEweScene->getCamera()->shake( 1 );
    m_destroyed = true;
}

void MeteorObject::endContact(MidtermBaseObject* pOtherObject)
{
}
