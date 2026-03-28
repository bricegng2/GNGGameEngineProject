#include "Framework.h"

#include "DataTypes.h"
#include "EweScene.h"
#include "ShakeCameraObject.h"

ShakeCameraObject::ShakeCameraObject(EweScene* pScene, vec3 pos)
    : fw::Camera( pScene, pos )
{
    m_rootPosition = pos;
    m_shakeOffset.set( 0, 0, 0 );

    m_shakeIntensity = 0;
    m_timeLeftToShake = 0;
}

ShakeCameraObject::~ShakeCameraObject()
{
}

void ShakeCameraObject::shake(float intensity)
{
    m_shakeIntensity += intensity;
    m_timeLeftToShake = 0.05f;
}

void ShakeCameraObject::update(float deltatime)
{
    if( m_timeLeftToShake > 0 )
    {
        if( m_shakeIntensity > 0.1f )
            m_shakeIntensity = 0.1f;

        m_timeLeftToShake -= deltatime;

        m_shakeOffset.x = rand()%100/100.0f * m_shakeIntensity;
        m_shakeOffset.y = rand()%100/100.0f * m_shakeIntensity;
        m_shakeOffset.z = rand()%100/100.0f * m_shakeIntensity;
    }
    else
    {
        m_shakeOffset = 0;
        m_shakeIntensity = 0;
    }

    m_position = m_rootPosition + m_shakeOffset;
}
