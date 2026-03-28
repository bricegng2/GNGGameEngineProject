#pragma once

#include "MKGameObject.h"

class SceneMarioKart;
class VirtualGamepad;

class MKPlayerObject : public MKGameObject
{
protected:
    vec3 m_initialPosition;
    vec3 m_initialRotation;

    vec3 m_targetVelocity;

    fw::Material* m_pFrontMaterial;

    VirtualGamepad* m_pController;

public:
    MKPlayerObject(SceneMarioKart* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial, fw::Material* pFrontMaterial);
    virtual ~MKPlayerObject();

    void setController(VirtualGamepad* pController);

    virtual void update(float deltaTime) override;
    virtual void draw(int viewID) override;
    virtual void reset();

    bool IsLocallyControlled() { return (m_pController != nullptr); }

    void setTransform(vec3 pos, vec3 rot);
};
