#pragma once

#include "MidtermBaseObject.h"

class EweScene;

class MeatChunkObject : public MidtermBaseObject
{
public:
    MeatChunkObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);
    virtual ~MeatChunkObject();

    virtual void reset() override;
    virtual void removeFromScene();

    virtual void update(float deltatime) override;

    void setPool(std::vector<MidtermBaseObject*>* pPool);
    void destroy();

    virtual void beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal);
    virtual void endContact(MidtermBaseObject* pOtherObject);

protected:
    std::vector<MidtermBaseObject*>* m_pPool = nullptr;
};
