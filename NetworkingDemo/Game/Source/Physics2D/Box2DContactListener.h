#pragma once

class Box2DContactListener : public b2ContactListener
{
public:

public:
    Box2DContactListener();
    ~Box2DContactListener();

    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
};
