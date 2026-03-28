#include "Framework.h"

#include "DataTypes.h"
#include "EweScene.h"
#include "SheepObject.h"
#include "SheepTitleCard.h"
#include "Objects/VirtualGamepad.h"

SheepObject::SheepObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
    : MidtermBaseObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_gotHit = false;
    m_isDead = false;
}

SheepObject::~SheepObject()
{
}

void SheepObject::reset()
{
    MidtermBaseObject::reset();
    m_gotHit = false;
    m_isDead = false;
}

void SheepObject::setGamepad(VirtualGamepad* pGamepad)
{
    m_pGamepad = pGamepad;
}

void SheepObject::update(float deltatime)
{
    MidtermBaseObject::update( deltatime );

    if( m_pGamepad == nullptr )
        return;

    if( m_isDead == true )
    {
        ((SheepTitleCard*)m_pEweScene->getGameObject( "Lose" ))->display();
        return;
    }

    if( m_gotHit )
    {
        m_pEweScene->spawnMeatChunks( m_position, 25 );

        m_isDead = true;

        m_pPhysicsBody->SetTransform( b2Vec2(10000, 0), 0 );

        return;
    }

    if( m_position.y < -5 )
    {
        ((SheepTitleCard*)m_pEweScene->getGameObject("Win"))->display();
    }

    m_pPhysicsBody->SetTransform(b2Vec2(m_position.x, m_position.y), 0.0f);

    //ImGui::Text("%s", m_pPhysicsBody->GetPosition());

    
}

void SheepObject::beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal)
{
    m_gotHit = true;
}

void SheepObject::endContact(MidtermBaseObject* pOtherObject)
{
}
