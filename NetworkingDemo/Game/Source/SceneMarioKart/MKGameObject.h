#pragma once

#include "DataTypes.h"

class SceneMarioKart;

class MKGameObject : public fw::GameObject
{
public:
    MKGameObject(SceneMarioKart* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);
    virtual ~MKGameObject();

    virtual void update(float deltaTime) override;

public:
    SceneMarioKart* m_pMKScene = nullptr;

    virtual void setPosition(vec3 pos);
    virtual void setRotation(vec3 rot);

    void createBody(bool isStatic);
    b2Fixture* addFixture(b2Shape* pShape, float density);
    b2Fixture* addBox(vec2 size, float density);
    b2Fixture* addCircle(float radius, float density);

    b2Body* m_pBody = nullptr;
};
