#include "Framework.h"

#include "Box2DManager.h"
#include "Box2DContactListener.h"
#include "Box2DDebugDraw.h"
#include "box2d/box2d.h"

Box2DManager::Box2DManager(fw::Material* pMaterial, fw::Camera* pCamera)
{
    m_pWorld = new b2World( b2Vec2( 0, -10 ) );
    m_pContactListener = new Box2DContactListener();
    //m_pDebugDraw = new Box2DDebugDraw( pMaterial, pCamera );

    //uint32 flags = b2Draw::e_shapeBit;
    //flags |= b2Draw::e_jointBit;
    //flags |= b2Draw::e_centerOfMassBit;
    //flags |= b2Draw::e_aabbBit;
    //flags |= b2Draw::e_pairBit;
    //m_pDebugDraw->SetFlags( flags );

    m_pWorld->SetContactListener( m_pContactListener );
    m_pWorld->SetAutoClearForces( false );

    //m_pWorld->SetDebugDraw( m_pDebugDraw );

    b2BodyDef bodyDef;
    m_pWorldBody = m_pWorld->CreateBody( &bodyDef );

    m_unusedTime = 0;
}

Box2DManager::~Box2DManager()
{
    delete m_pDebugDraw;
    delete m_pContactListener;
    delete m_pWorld;
}

void Box2DManager::update(float deltaTime)
{
    m_unusedTime += deltaTime;

    float timeStep = 1/60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    m_pWorld->Step( deltaTime, velocityIterations, positionIterations );

    //while( m_UnusedTime >= timeStep )
    //{
    //    m_pWorld->Step( timeStep, velocityIterations, positionIterations );
    //    m_UnusedTime -= timeStep;
    //}

    m_pWorld->ClearForces();
}
