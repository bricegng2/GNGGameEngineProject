#include "Framework.h"

#include "MKPlayerObject.h"
#include "SceneMarioKart.h"
#include "Objects/VirtualGamepad.h"

MKPlayerObject::MKPlayerObject(SceneMarioKart* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial, fw::Material* pFrontMaterial)
    : MKGameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_initialPosition = pos;
    m_initialRotation = rot;

    m_targetVelocity.set( 0, 0, 0 );

    m_pFrontMaterial = pFrontMaterial;

    m_pController = nullptr;
}

MKPlayerObject::~MKPlayerObject()
{
}

void MKPlayerObject::setController(VirtualGamepad* pController)
{
    m_pController = pController;
}

void MKPlayerObject::update(float deltaTime)
{
    MKGameObject::update( deltaTime );

    if( m_pBody == nullptr )
        return;

    m_pBody->SetLinearDamping( 2 );
    m_pBody->SetAngularDamping( 100 );

    if( m_pController == nullptr )
        return;

    // Deal with input
    {
        float speed = 50.0f;
        float turnspeed = 0.1f;

        float rot = m_pBody->GetAngle() + PI/2;
        b2Vec2 force( cos(rot), sin(rot) );

        if( m_pController->isHeld(VirtualGamepad::Up) )
        {
            force *= speed;
            m_pBody->ApplyForce( force, m_pBody->GetWorldCenter(), true );
        }
        if( m_pController->isHeld(VirtualGamepad::Down) )
        {
            force *= -speed;
            m_pBody->ApplyForce( force, m_pBody->GetWorldCenter(), true );
        }

        if( m_pController->isHeld(VirtualGamepad::Left) )
        {
            m_pBody->ApplyTorque( speed, true );
        }
        if( m_pController->isHeld(VirtualGamepad::Right) )
        {
            m_pBody->ApplyTorque( -speed, true );
        }
    }
}

void MKPlayerObject::draw(int viewID)
{
    if( m_pMesh == nullptr )
        return;

    MKGameObject::draw( viewID );

    fw::Uniforms* pUniforms = m_pScene->getGameCore()->getUniforms();

    mat4 worldMatrix;
    vec3 rot = m_rotation;
    rot.y += 180;
    worldMatrix.createSRT( m_scale, rot, m_position );
    pUniforms->set( "u_matWorld", worldMatrix );

    m_pMesh->draw( viewID, pUniforms, m_pFrontMaterial );
}

void MKPlayerObject::reset()
{
    if( m_pBody )
    {
        m_pBody->SetLinearVelocity( b2Vec2( 0, 0 ) );
        m_pBody->SetAngularVelocity( 0 );
        m_pBody->SetTransform( b2Vec2(m_initialPosition.x, m_initialPosition.y), m_initialRotation.z*PI/180.0f );
        m_pBody->SetAwake( true );

        b2Filter filterdata = m_pBody->GetFixtureList()->GetFilterData();
        filterdata.groupIndex = 0;
        m_pBody->GetFixtureList()->SetFilterData( filterdata );
    }
}

void MKPlayerObject::setTransform(vec3 pos, vec3 rot)
{
    setPosition( pos );
    setRotation( rot );
}
