//#pragma once
//
//#include "DataTypes.h"
//#include "Meshes/VertexFormats.h"
//#include "HeightmapComponent.h"
//
//class OrbitCameraComponent : public fw::Component
//{
//public:
//    OrbitCameraComponent(fw::GameObject* pGameObject, fw::TransformComponent* pTarget);
//    virtual ~OrbitCameraComponent();
//
//    static const char* GetStaticType() { return "OrbitCameraComponent"; }
//    virtual const char* GetType() override { return GetStaticType(); }
//
//    void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
//
//    void Update(float deltaTime);
//    void Enable(int viewID);
//    
//protected:
//    fw::TransformComponent* m_pTarget = nullptr;
//
//    float m_Distance = 10.0f;
//    float m_AspectRatio = 1.0f;
//    
//    vec3 m_Eye = vec3(0, 0, 0);
//    vec3 m_At = vec3(0, 0, 1);
//    vec3 m_Up = vec3(0, 1, 0);
//};
