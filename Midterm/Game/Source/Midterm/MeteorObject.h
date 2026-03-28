#pragma once

#include "MidtermBaseObject.h"
#include "Midterm/EweScene.h"
#include "Midterm/ShakeCameraObject.h"

class EweScene;

class MeteorObject : public MidtermBaseObject
{
public:
    MeteorObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);
    virtual ~MeteorObject();

    virtual void reset() override;
    virtual void removeFromScene();

    virtual void update(float deltatime);

    void setPool(std::vector<MidtermBaseObject*>* pPool);

    void destroy();

    virtual void beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal);
    virtual void endContact(MidtermBaseObject* pOtherObject);

protected:
    std::vector<MidtermBaseObject*>* m_pPool = nullptr;

    bool m_destroyed = false;
};
