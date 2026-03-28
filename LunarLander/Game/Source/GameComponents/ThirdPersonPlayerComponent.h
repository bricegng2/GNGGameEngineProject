//#pragma once
//
//#include "DataTypes.h"
//#include "Meshes/VertexFormats.h"
//#include "HeightmapComponent.h"
//
//class Controller;
//
//class ThirdPersonPlayerComponent : public fw::Component
//{
//public:
//    ThirdPersonPlayerComponent(fw::GameObject* pGameObject, Controller* pController);
//    virtual ~ThirdPersonPlayerComponent();
//
//    static const char* GetStaticType() { return "ThirdPersonPlayerComponent"; }
//    virtual const char* GetType() override { return GetStaticType(); }
//
//    void SetController(Controller* pController) { m_pController = pController; }
//    void SetCameraTransform(fw::TransformComponent* pCameraTransform) { m_pCameraTransform = pCameraTransform; }
//    void SetHeightmapComponent(HeightmapComponent* pHeightmapComponent) { m_pHeightmapComponent = pHeightmapComponent; }
//
//    void HandleInputs(float deltaTime);
//    
//protected:
//    Controller* m_pController = nullptr;
//    fw::TransformComponent* m_pCameraTransform = nullptr;
//    HeightmapComponent* m_pHeightmapComponent = nullptr;
//
//    float m_Speed = 3.0f;
//};
