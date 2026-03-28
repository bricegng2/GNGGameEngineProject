#include "Framework.h"

#include "Box2DContactListener.h"
#include "DataTypes.h"

Box2DContactListener::Box2DContactListener()
{
}

Box2DContactListener::~Box2DContactListener()
{
}

void Box2DContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* pFixture[2];
    fw::GameObject* pGameObjects[2];

    pFixture[0] = contact->GetFixtureA();
    pFixture[1] = contact->GetFixtureB();

    pGameObjects[0] = reinterpret_cast<fw::GameObject*>( pFixture[0]->GetBody()->GetUserData().pointer );
    pGameObjects[1] = reinterpret_cast<fw::GameObject*>( pFixture[1]->GetBody()->GetUserData().pointer );

    b2WorldManifold worldManifold;
    contact->GetWorldManifold( &worldManifold );
    vec2 position( worldManifold.points[0].x, worldManifold.points[0].y );
    vec2 normal( worldManifold.normal.x, worldManifold.normal.y );

    //pGameObjects[0]->beginContact( pFixture[1], position, normal );
    //pGameObjects[1]->beginContact( pFixture[0], position, normal * -1 );
}

void Box2DContactListener::EndContact(b2Contact* contact)
{
}

void Box2DContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}
