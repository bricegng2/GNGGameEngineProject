#include "Framework.h"

#include "DataTypes.h"
#include "SheepTitleCard.h"

SheepTitleCard::SheepTitleCard(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
    : MidtermBaseObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_timeAlive = 0;
}

SheepTitleCard::~SheepTitleCard()
{
}

void SheepTitleCard::reset()
{
    MidtermBaseObject::reset();

    m_timeAlive = 0;
}

void SheepTitleCard::update(float deltatime)
{
    MidtermBaseObject::update( deltatime );

    m_timeAlive += deltatime;

    if( m_timeAlive > 0.5 )
        m_position.y += deltatime*4;
}

void SheepTitleCard::display()
{
    m_position.y = 3;
    m_timeAlive = 0;
}
