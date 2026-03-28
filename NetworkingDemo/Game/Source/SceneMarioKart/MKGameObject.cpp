#include "Framework.h"

#include "MKGameObject.h"
#include "SceneMarioKart.h"
#include "Physics2D/Box2DManager.h"

MKGameObject::MKGameObject(SceneMarioKart* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
    : GameObject( pScene, name, pos, pMesh, pMaterial )
    , m_pMKScene( pScene )
{
    m_rotation = rot;
    m_scale = scale;
    m_pBody = nullptr;
}

MKGameObject::~MKGameObject()
{
}

void MKGameObject::update(float deltaTime)
{
    //GameObject::Update( deltaTime );

    if( m_pBody )
    {
        b2Vec2 pos = m_pBody->GetPosition();
        float32 angle = m_pBody->GetAngle() / PI * 180.0f;

        m_position.x = pos.x;
        m_position.z = pos.y;

        m_rotation.y = angle;
    }
}

void MKGameObject::setPosition(vec3 pos)
{
    m_position = pos;
    if( m_pBody )
        m_pBody->SetTransform( b2Vec2( m_position.x, m_position.z ), m_rotation.y * PI / 180.0f );
}

void MKGameObject::setRotation(vec3 rot)
{
    m_rotation = rot;
    if( m_pBody )
        m_pBody->SetTransform( b2Vec2( m_position.x, m_position.z ), m_rotation.y * PI / 180.0f );
}

void MKGameObject::createBody(bool isStatic)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set( m_position.x, m_position.y );
    bodyDef.angle = -m_rotation.z * PI / 180.0f;
    if( isStatic )
        bodyDef.type = b2_staticBody;
    else
        bodyDef.type = b2_dynamicBody;
    bodyDef.awake = true;
    bodyDef.userData.pointer = (uintptr_t)this;

    m_pBody = m_pMKScene->getBox2DManager()->getWorld()->CreateBody( &bodyDef );
}

b2Fixture* MKGameObject::addFixture(b2Shape* pShape, float density)
{
    assert( m_pBody != nullptr );

    b2FixtureDef fixture;
    fixture.shape = pShape;
    fixture.density = density;
    fixture.friction = 1.0f;
    fixture.isSensor = false;
    fixture.restitution = 0.0f;
    fixture.userData.pointer = (uintptr_t)this;

    return m_pBody->CreateFixture( &fixture );
}

b2Fixture* MKGameObject::addBox(vec2 size, float density)
{
    b2PolygonShape shape;
    shape.SetAsBox( size.x/2, size.y/2 );

    return addFixture( &shape, density );
}

b2Fixture* MKGameObject::addCircle(float radius, float density)
{
    b2CircleShape shape;
    shape.m_p = b2Vec2( 0, 0 );
    shape.m_radius = radius;

    return addFixture( &shape, density );
}
