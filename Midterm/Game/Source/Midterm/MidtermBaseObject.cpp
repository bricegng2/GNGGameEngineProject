#include "Framework.h"

#include "EweScene.h"
#include "MidtermBaseObject.h"

MidtermBaseObject::MidtermBaseObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
    : GameObject( pScene, name, pos, pMesh, pMaterial)
    , m_pEweScene( pScene )
{
    m_renderOrder = 2;

    init( pScene, name, pos, rot, scale, pMesh, pMaterial );
}

MidtermBaseObject::~MidtermBaseObject()
{
}

void MidtermBaseObject::init(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial)
{
    m_initialPosition = pos;
    m_initialRotation = rot;

    m_pScene = pScene;

    m_name = name;

    m_position = pos;
    m_rotation = rot;
    m_scale = scale;

    m_color.set( 1, 1, 1, 1 );

    m_pPhysicsBody = nullptr;
}

void MidtermBaseObject::reset()
{
    m_position = m_initialPosition;
    m_rotation = m_initialRotation;

    if( m_pPhysicsBody )
    {
        m_pPhysicsBody->SetLinearVelocity( b2Vec2( 0, 0 ) );
        m_pPhysicsBody->SetAngularVelocity( 0 );
        m_pPhysicsBody->SetTransform( b2Vec2( m_initialPosition.x, m_initialPosition.y ), m_initialPosition.z * PI / 180 );
        m_pPhysicsBody->SetAwake( true );
    }
}

void MidtermBaseObject::addToScene(EweScene* pScene)
{
    m_pEweScene = pScene;
    m_pEweScene->addToScene( m_name, this );
}

void MidtermBaseObject::removeFromScene()
{
    if( m_pEweScene )
    {
        m_pEweScene->removeFromScene( this );
    }
}

void MidtermBaseObject::update(float deltatime)
{
    if( m_pPhysicsBody )
    {
        b2Vec2 pos = m_pPhysicsBody->GetPosition();
        float32 angle = -m_pPhysicsBody->GetAngle() / PI * 180.0f;

        m_position.x = pos.x;
        m_position.y = pos.y;

        m_rotation.z = angle;
    }
}

void MidtermBaseObject::beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal)
{
}

void MidtermBaseObject::endContact(MidtermBaseObject* pOtherObject)
{
}

b2Fixture* MidtermBaseObject::addPhysicsShape(b2Shape* shape, bool dynamic, bool active, float density, bool sensor)
{
    if( m_pPhysicsBody == nullptr )
    {
        b2BodyDef bodydef;
        bodydef.position.Set( m_position.x, m_position.y ); // bottom-left corner
        bodydef.angle = -m_rotation.z * PI / 180.0f;
        if( dynamic )
            bodydef.type = b2_dynamicBody;
        else
            bodydef.type = b2_staticBody;

        bodydef.enabled = active;

        bodydef.userData.pointer = reinterpret_cast<uintptr_t>( this );

        m_pPhysicsBody = m_pEweScene->getBox2DWorld()->CreateBody( &bodydef );
    }

    b2FixtureDef fixturedef;
    fixturedef.shape = shape;
    fixturedef.density = density;
    fixturedef.isSensor = sensor;
    fixturedef.friction = 0.2f;
    fixturedef.restitution = 0;

    return m_pPhysicsBody->CreateFixture( &fixturedef );
}

b2Fixture* MidtermBaseObject::addPhysicsBox(vec2 size, bool dynamic, bool active, float density, bool sensor)
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox( size.x/2, size.y/2 );

    return addPhysicsShape( &boxShape, dynamic, active, density, sensor );
}

b2Fixture* MidtermBaseObject::addPhysicsDentedBox(vec2 size, float indent, bool dynamic, bool active, float density, bool sensor)
{
    b2PolygonShape boxshape;

    b2Vec2 points[8];
    float hx = size.x/2;
    float hy = size.y/2;

    points[0].Set( -hx         , -hy + indent ); // lower left - left
    points[1].Set( -hx + indent, -hy          ); // lower left - lower
    points[2].Set(  hx - indent, -hy          ); // lower right - lower
    points[3].Set(  hx         , -hy + indent ); // lower right - right
    points[4].Set(  hx         ,  hy - indent ); // upper right - right
    points[5].Set(  hx - indent,  hy          ); // upper right - upper
    points[6].Set( -hx + indent,  hy          ); // upper left - upper
    points[7].Set( -hx         ,  hy - indent ); // upper left - left

    boxshape.Set( points, 8 );

    return addPhysicsShape( &boxshape, dynamic, active, density, sensor );
}

b2Fixture* MidtermBaseObject::addPhysicsCircle(float radius, bool dynamic, bool active, float density, bool sensor)
{
    b2CircleShape circleshape;
    circleshape.m_radius = radius;

    return addPhysicsShape( &circleshape, dynamic, active, density, sensor );
}

void MidtermBaseObject::setPosition(vec3 pos)
{
    m_position = pos;
    if( m_pPhysicsBody )
        m_pPhysicsBody->SetTransform( b2Vec2(m_position.x, m_position.y), -m_rotation.z * PI / 180.0f );
}

void MidtermBaseObject::setRotation(vec3 rot)
{
    m_rotation = rot;
    if( m_pPhysicsBody )
        m_pPhysicsBody->SetTransform( b2Vec2(m_position.x, m_position.y), -m_rotation.z * PI / 180.0f );
}
