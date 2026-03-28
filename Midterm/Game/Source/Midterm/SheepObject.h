#pragma once

#include "MidtermBaseObject.h"

class EweScene;
class VirtualGamepad;

class SheepObject : public MidtermBaseObject
{
public:
    SheepObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);
    virtual ~SheepObject();

    virtual void reset() override;
    void setGamepad(VirtualGamepad* pGamepad);

    virtual void update(float deltatime);

    virtual void beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal);
    virtual void endContact(MidtermBaseObject* pOtherObject);

protected:
    VirtualGamepad* m_pGamepad = nullptr;

    bool m_gotHit;
    bool m_isDead;
};
