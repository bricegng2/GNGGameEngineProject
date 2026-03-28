//#include "Framework.h"
//#include "ThirdPersonPlayerComponent.h"
//#include "Meshes/VertexFormats.h"
//#include "Objects/Controller.h"
//
//#include "stb/stb_image.h"
//
//ThirdPersonPlayerComponent::ThirdPersonPlayerComponent(fw::GameObject* pGameObject, Controller* pController)
//    : fw::Component( pGameObject )
//    , m_pController( pController )
//{
//}
//
//ThirdPersonPlayerComponent::~ThirdPersonPlayerComponent()
//{
//}
//
//void ThirdPersonPlayerComponent::HandleInputs(float deltaTime)
//{
//    fw::TransformComponent* pTransform = m_pGameObject->GetComponent<fw::TransformComponent>();
//
//    float cameraY = m_pCameraTransform->m_Rotation.y;
//
//    vec3 forward = vec3( cos((cameraY+90)/180*PI), 0, sin((cameraY+90)/180*PI) );
//    vec3 right = vec3( cos((cameraY)/180*PI), 0, sin((cameraY)/180*PI) );
//
//    vec3 dir(0);
//    
//    if( m_pController->IsHeld( Controller::Up ) )
//        dir += forward;
//    if( m_pController->IsHeld( Controller::Down ) )
//        dir -= forward;
//    if( m_pController->IsHeld( Controller::Right ) )
//        dir += right;            
//    if( m_pController->IsHeld( Controller::Left ) )
//        dir -= right;
//
//    dir.Normalize();
//    
//    pTransform->m_Position += dir * deltaTime * m_Speed;
//    pTransform->m_Rotation.y = cameraY - 90;
//
//    pTransform->m_Position.y = m_pHeightmapComponent->GetHeightAtXZ( pTransform->m_Position.x, pTransform->m_Position.z );
//}
