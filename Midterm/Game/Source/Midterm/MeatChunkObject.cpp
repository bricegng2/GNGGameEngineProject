#include "Framework.h"

#include "DataTypes.h"
#include "Events/GameEvents.h"
#include "EweScene.h"
#include "MeatChunkObject.h"

MeatChunkObject::MeatChunkObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
    : MidtermBaseObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
}

MeatChunkObject::~MeatChunkObject()
{
}

void MeatChunkObject::reset()
{
    MidtermBaseObject::reset();
    removeFromScene();
}

void MeatChunkObject::removeFromScene()
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
}

void MeatChunkObject::update(float deltatime)
{
    MidtermBaseObject::update( deltatime );
}

void MeatChunkObject::setPool(std::vector<MidtermBaseObject*>* pPool)
{
    m_pPool = pPool;
}

void MeatChunkObject::destroy()
{
    assert( m_pScene != 0 );

    RemoveFromGameEvent* pEvent = new RemoveFromGameEvent( this );
    m_pScene->getGameCore()->getEventManager()->addEvent( pEvent );
}

void MeatChunkObject::beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal)
{
    MidtermBaseObject::beginContact( pOtherObject, worldPosition, worldNormal );
}

void MeatChunkObject::endContact(MidtermBaseObject* pOtherObject)
{
    MidtermBaseObject::endContact( pOtherObject );
}
