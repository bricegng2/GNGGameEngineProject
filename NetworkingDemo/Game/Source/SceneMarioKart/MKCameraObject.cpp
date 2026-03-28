#include "Framework.h"

#include "MKCameraObject.h"

MKCameraObject::MKCameraObject(fw::Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: fw::Camera( pScene, pos )
{
    m_closestZ = -10;
    m_objectFollowing = 0;
}

MKCameraObject::~MKCameraObject()
{
}

void MKCameraObject::update(float deltaTime)
{
    fw::Camera::update( deltaTime );
}

void MKCameraObject::enable(int viewID)
{
    vec3 otherpos = m_objectFollowing->getPosition();
    vec3 otherrot = m_objectFollowing->getRotation();

    mat4 mat;
    mat.createSRT( m_scale, otherrot, otherpos );
    vec3 at = mat.getAt();
    m_position = otherpos + at * m_closestZ;
    m_position.y += 2;

    mat4 viewMatrix;
    viewMatrix.createLookAtView( m_position, vec3(0,1,0), otherpos );

    fw::Uniforms* pUniforms = m_pScene->getGameCore()->getUniforms();
    pUniforms->set( "u_matView", viewMatrix );

    mat4 projMatrix;
    projMatrix.createPerspectiveVFoV( 60, m_aspectRatio, 0.01f, 100.0f );
    pUniforms->set( "u_matProj", projMatrix );
}
