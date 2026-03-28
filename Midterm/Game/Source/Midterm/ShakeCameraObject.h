#pragma once

class EweScene;

class ShakeCameraObject : public fw::Camera
{
public:
    ShakeCameraObject(EweScene* pScene, vec3 pos);
    virtual ~ShakeCameraObject();

    virtual void update(float deltatime) override;

    void shake(float intensity);

protected:
    vec3 m_rootPosition;

    vec3 m_shakeOffset;
    float m_shakeIntensity;
    float m_timeLeftToShake;
};
