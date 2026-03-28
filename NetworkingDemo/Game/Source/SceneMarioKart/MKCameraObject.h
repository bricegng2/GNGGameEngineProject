#pragma once

#include "DataTypes.h"

class MKCameraObject : public fw::Camera
{
protected:
    GameObject* m_objectFollowing;
    float m_closestZ;

public:
    MKCameraObject(fw::Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~MKCameraObject();

    virtual void update(float deltaTime);
    virtual void enable(int viewID) override;

    void setObjectToFollow(fw::GameObject* pObject, float closestz) { m_objectFollowing = pObject; m_closestZ = closestz; }
};
