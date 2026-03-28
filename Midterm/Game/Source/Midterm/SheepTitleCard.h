#pragma once

#include "MidtermBaseObject.h"

class EweScene;

class SheepTitleCard : public MidtermBaseObject
{
public:
    SheepTitleCard(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);
    virtual ~SheepTitleCard();

    virtual void reset() override;

    virtual void update(float deltatime);

    void display();

protected:
    float m_timeAlive;
};
