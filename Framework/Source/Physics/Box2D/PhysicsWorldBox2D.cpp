#include "PhysicsWorldBox2D.h"
#include "PhysicsBodyBox2D.h"

#include "Box2DDebugDraw.h"
#include "Components/Component.h"
#include "Objects/GameObject.h"
#include "EventSystem/EventManager.h"
#include "EventSystem/Events.h"

namespace fw
{
    //=======================
    // MyContactListener.
    //=======================
    MyContactListener::MyContactListener(EventManager* pEventManager)
        : m_pEventManager( pEventManager )
    {
    }

    void MyContactListener::BeginContact(b2Contact* contact)
    {
        b2Fixture* pFixtureA = contact->GetFixtureA();
        b2Fixture* pFixtureB = contact->GetFixtureB();

        b2Body* pBodyA = pFixtureA->GetBody();
        b2Body* pBodyB = pFixtureB->GetBody();

        GameObject* pObjectA = pBodyA->GetUserData().pGameObject;
        GameObject* pObjectB = pBodyB->GetUserData().pGameObject;

        // Create an event saying Object A and Object B hit each other.
        CollisionEvent* pCollision = new CollisionEvent( pObjectA, pObjectB );
        m_pEventManager->addEvent( pCollision );
    }

    //=======================
    // PhysicsWorldBox2D
    //=======================
    PhysicsWorldBox2D::PhysicsWorldBox2D(EventManager* pEventManager)
    {
        m_pWorld = new b2World( b2Vec2(0.0f, -9.8f) );

        m_pContactListener = new MyContactListener( pEventManager );
        m_pWorld->SetContactListener( m_pContactListener );

        // Create a ground body for joints in future.
        b2BodyDef bodyDef;
        m_pGroundBody = m_pWorld->CreateBody( &bodyDef );
    }

    PhysicsWorldBox2D::~PhysicsWorldBox2D()
    {
        delete m_pContactListener;
        delete m_pWorld;
    }

    //void PhysicsWorldBox2D::createDebugDraw(Uniforms* pUniforms, Material* pMaterial)
    //{
    //    MyDebugDraw* pDebugDraw = new MyDebugDraw();
    //    pDebugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_aabbBit );
    //    pDebugDraw->m_pMaterial = pMaterial;
    //    pDebugDraw->m_pUniforms = pUniforms;
    //    MyDebugDraw::VertexFormat::initVertexLayout();
    //    m_pWorld->SetDebugDraw( pDebugDraw );
    //}

    void PhysicsWorldBox2D::update(float deltaTime)
    {
        float timeStep = 1/60.0f;

        bool didAWorldStep = false;
        m_timeAccumulated += deltaTime;

        while( m_timeAccumulated >= timeStep )
        {
            didAWorldStep = true;
            m_pWorld->Step( timeStep, 8, 3 );
            m_timeAccumulated -= timeStep;
        }

        if( didAWorldStep == false )
        {
            m_pWorld->ClearForces();
        }
    }

    //void PhysicsWorldBox2D::draw()
    //{
    //    m_pWorld->DebugDraw();
    //}

    void PhysicsWorldBox2D::setGravity(vec3 gravity)
    {
        m_pWorld->SetGravity( b2Vec2(gravity.x, gravity.y) );
    }

    PhysicsBody* PhysicsWorldBox2D::createBody(TransformComponent* pTransform, bool isDynamic, float density, GameObject* pGameObject, fw::ShapeType shapeType)
    {
        vec3 pos = pTransform->m_position;
        vec3 rot = pTransform->m_rotation;
        vec3 scale = pTransform->m_scale;

        // Setup the body definition structure.
        b2BodyDef bodyDef;
        bodyDef.position.Set( pos.x, pos.y );
        bodyDef.angle = -rot.z / 180.0f * PI;
        if( isDynamic )
        {
            bodyDef.type = b2_dynamicBody;
        }
        bodyDef.userData.pGameObject = pGameObject;

        // Setup the shape.
        b2PolygonShape shape;
        shape.SetAsBox( scale.x/2, scale.y/2 );

        // Setup the fixture definition with the shape.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;

        // Create the body and the fixture.
        b2Body* pBody = m_pWorld->CreateBody( &bodyDef );
        pBody->CreateFixture( &fixtureDef );

        return new PhysicsBodyBox2D( pBody );
    }

    void PhysicsWorldBox2D::createJoint(PhysicsBody* pBody, vec3 pos)
    {
        b2RevoluteJointDef jointDef;
        jointDef.Initialize( static_cast<PhysicsBodyBox2D*>(pBody)->getb2Body(), m_pGroundBody, b2Vec2(pos.x, pos.y) );
        //jointDef.enableMotor = true;
        //jointDef.motorSpeed = 20.0f;
        //jointDef.maxMotorTorque = 3.0f;

        b2Joint* pJoint = m_pWorld->CreateJoint( &jointDef );
    }

    void PhysicsWorldBox2D::destroyBody(PhysicsBody* pBody)
    {
        m_pWorld->DestroyBody( static_cast<PhysicsBodyBox2D*>(pBody)->getb2Body() );
    }
} // namespace fw
