//#include "Framework.h"
//#include "OrbitCameraComponent.h"
//#include "Meshes/VertexFormats.h"
//
//#include "stb/stb_image.h"
//
//OrbitCameraComponent::OrbitCameraComponent(fw::GameObject* pGameObject, fw::TransformComponent* pTarget)
//    : fw::Component( pGameObject )
//    , m_pTarget( pTarget )
//{
//}
//
//OrbitCameraComponent::~OrbitCameraComponent()
//{
//}
//
//void OrbitCameraComponent::Update(float deltaTime)
//{
//    fw::TransformComponent* pTransform = m_pGameObject->GetComponent<fw::TransformComponent>();
//    fw::FWCore* pFramework = m_pGameObject->GetScene()->GetGameCore()->GetFramework();
//    
//    if( m_pTarget == nullptr )
//    {
//        m_Eye = pTransform->m_Position;
//        m_At = pTransform->m_Position + vec3(0,0,1);
//        m_Up = vec3(0,1,0);
//    }
//    else
//    {
//        vec2 rotationSpeed = vec2( 1, 0.4f );
//
//        if( pFramework->IsKeyDown('J') )
//            pTransform->m_Rotation.y += 90 * deltaTime * rotationSpeed.x;
//        if( pFramework->IsKeyDown('L') )
//            pTransform->m_Rotation.y -= 90 * deltaTime * rotationSpeed.x;
//        if( pFramework->IsKeyDown('I') )
//            pTransform->m_Rotation.x -= 90 * deltaTime * rotationSpeed.y;
//        if( pFramework->IsKeyDown('K') )
//            pTransform->m_Rotation.x += 90 * deltaTime * rotationSpeed.y;
//
//        if( pFramework->IsKeyDown('U') )
//            m_Distance -= 10 * deltaTime;
//        if( pFramework->IsKeyDown('M') )
//            m_Distance += 10 * deltaTime;
//
//        fw::MyClamp( m_Distance, 0.1f, 100.0f );
//        fw::MyClamp( pTransform->m_Rotation.x, -89.9f, 89.9f );
//
//        // Calculate eye position.
//        // Method 1.
//        float sx = sin( pTransform->m_Rotation.x / 180 * PI );
//        float sy = sin( pTransform->m_Rotation.y / 180 * PI );
//        float cx = cos( pTransform->m_Rotation.x / 180 * PI );
//        float cy = cos( pTransform->m_Rotation.y / 180 * PI );
//        vec3 offset = vec3( cx * sy * m_Distance, -sx * m_Distance, -1 * cx * cy * m_Distance );
//
//        // Method 2.
//        mat4 rot;
//        rot.SetIdentity();
//        rot.Rotate( pTransform->m_Rotation.x, 1, 0, 0 );
//        rot.Rotate( pTransform->m_Rotation.y, 0, 1, 0 );
//        offset = rot * vec3(0,0,-m_Distance);
//
//        m_Eye = m_pTarget->m_Position + offset;
//        m_At = m_pTarget->m_Position;
//        m_Up = vec3(0,1,0);
//    }
//}
//
//void OrbitCameraComponent::Enable(int viewID)
//{
//    fw::Uniforms* pUniforms = m_pGameObject->GetScene()->GetGameCore()->GetUniforms();
//    fw::TransformComponent* pTransform = m_pGameObject->GetComponent<fw::TransformComponent>();
//
//    mat4 viewMatrix;
//    viewMatrix.CreateLookAtView( m_Eye, m_Up, m_At );
//
//    mat4 projMatrix;
//    projMatrix.CreatePerspectiveVFoV( 45, m_AspectRatio, 0.01f, 1000.0f );
//
//    //bgfx::setViewTransform( viewID, &viewMatrix, &projMatrix );
//    //bgfx::setViewMode( viewID, bgfx::ViewMode::DepthAscending );
//
//    // Setup uniforms.
//    bgfx::setUniform( pUniforms->GetUniform("u_ViewMatrix"), &viewMatrix );
//    bgfx::setUniform( pUniforms->GetUniform("u_ProjMatrix"), &projMatrix );
//    bgfx::setUniform( pUniforms->GetUniform("u_CameraPosition"), &pTransform->m_Position, 1 );
//}
