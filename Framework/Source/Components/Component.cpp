#include "CoreHeaders.h"
#include "Component.h"
#include "GameCore.h"
#include "EventSystem/Events.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
#include "Physics/PhysicsBody.h"
#include "Physics/PhysicsWorld.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "Resources/ResourceManager.h"
#include "Objects/FreeCamera.h"

namespace fw
{
    //==========================
    // Base component class
    //==========================
    Component::Component(GameObject* pGameObject)
        : m_pGameObject( pGameObject )
    {
    }

    Component::~Component()
    {
    }

    //void Component::AddToInspector()
    //{
    //}
    //
    //void Component::SaveToJSON(nlohmann::json& json)
    //{
    //    json["Type"] = GetType();
    //}
    //
    //void Component::LoadFromJSON(nlohmann::json& json)
    //{
    //}

    //==========================
    // Transform
    //==========================
    TransformComponent::TransformComponent(GameObject* pGameObject)
        : Component( pGameObject )
    {
    }

    TransformComponent::TransformComponent(GameObject* pGameObject, vec3 pos, vec3 rot, vec3 scale)
        : Component( pGameObject )
        , m_position( pos )
        , m_rotation( rot )
        , m_scale( scale )
    {
    }

    //void TransformComponent::AddToInspector()
    //{
    //    Component::addToInspector();
    //
    //    ImGui::DragFloat3( "Position", &m_position.x, 0.1f );
    //    ImGui::DragFloat3( "Rotation", &m_rotation.x, 0.1f );
    //    ImGui::DragFloat3( "Scale", &m_scale.x, 0.1f );
    //}
    //
    //void TransformComponent::SaveToJSON(nlohmann::json& json)
    //{
    //    Component::saveToJSON( json );
    //
    //    json["Position"] = { m_position.x, m_position.y, m_position.z };
    //    json["Rotation"] = { m_rotation.x, m_rotation.y, m_rotation.z };
    //    json["Scale"] = { m_scale.x, m_scale.y, m_scale.z };
    //}
    //
    //void TransformComponent::loadFromJSON(nlohmann::json& json)
    //{
    //    Component::loadFromJSON( json );
    //
    //    m_position = vec3( json["Position"][0], json["Position"][1], json["Position"][2] );
    //    m_rotation = vec3( json["Rotation"][0], json["Rotation"][1], json["Rotation"][2] );
    //    m_scale = vec3( json["Scale"][0], json["Scale"][1], json["Scale"][2] );
    //}

    //==========================
    // RenderComponent
    //==========================
    RenderComponent::RenderComponent(GameObject* pGameObject)
        : Component( pGameObject )
    {
    }

    RenderComponent::RenderComponent(GameObject* pGameObject, Mesh* pMesh, Material* pMaterial)
        : Component( pGameObject )
        , m_pMesh( pMesh )
        , m_pMaterial( pMaterial )
    {
    }

    RenderComponent::~RenderComponent()
    {
    }

    //void RenderComponent::addToInspector()
    //{
    //    Component::addToInspector();
    //
    //    ResourceManager* pResources = m_pGameObject->getScene()->getGameCore()->getResourceManager();
    //
    //    ImGui::Text( "Mesh: %s", pResources->getMeshName(m_pMesh).c_str() );
    //    ImGui::Text( "Material: %s", pResources->getMaterialName(m_pMaterial).c_str() );
    //}
    //
    //void RenderComponent::saveToJSON(nlohmann::json& json)
    //{
    //    ResourceManager* pResources = m_pGameObject->getScene()->getGameCore()->getResourceManager();
    //    Component::SaveToJSON( json );
    //
    //    json["Mesh"] = pResources->getMeshName( m_pMesh );
    //    json["Material"] = pResources->getMaterialName( m_pMaterial );
    //}
    //
    //void RenderComponent::loadFromJSON(nlohmann::json& json)
    //{
    //    ResourceManager* pResources = m_pGameObject->getScene()->getGameCore()->getResourceManager();
    //    Component::loadFromJSON( json );
    //
    //    m_pMesh = pResources->getMesh( json["Mesh"] );
    //    m_pMaterial = pResources->getMaterial( json["Material"] );
    //}

    //==========================
    // Physics Body
    //==========================
    PhysicsBodyComponent::PhysicsBodyComponent(GameObject* pGameObject)
        : Component( pGameObject )
    {
    }

    PhysicsBodyComponent::PhysicsBodyComponent(GameObject* pGameObject, PhysicsWorld* pWorld, bool isDynamic, fw::ShapeType shapeType)
        : Component( pGameObject )
    {
        createBody( pWorld, isDynamic, shapeType );
    }

    PhysicsBodyComponent::~PhysicsBodyComponent()
    {
        delete m_pBody;
    }

    void PhysicsBodyComponent::createBody(PhysicsWorld* pWorld, bool isDynamic, fw::ShapeType shapeType)
    {
        assert( m_pBody == nullptr );

        m_pWorld = pWorld;

        TransformComponent* pTransform = m_pGameObject->getComponent<TransformComponent>();
        assert( pTransform != nullptr );

        m_pBody = m_pWorld->createBody( pTransform, isDynamic, 1, m_pGameObject, shapeType );
    }

    void PhysicsBodyComponent::sync()
    {
        if( m_pBody )
        {
            TransformComponent* pTransform = m_pGameObject->getComponent<TransformComponent>();
            assert( pTransform != nullptr );

            pTransform->m_position = m_pBody->getPosition();
            pTransform->m_rotation = m_pBody->getRotation();
        }
    }

    void PhysicsBodyComponent::syncToTransform()
    {
        if( m_pBody )
        {
            TransformComponent* pTransform = m_pGameObject->getComponent<TransformComponent>();
            assert( pTransform != nullptr );

            //b2Vec2 pos = b2Vec2( pTransform->m_position.x, pTransform->m_position.y );
            //float angle = -pTransform->m_rotation.z * PI / 180.0f;

            m_pBody->setTransform( pTransform->m_position, pTransform->m_rotation );
        }
    }

    //==========================
    // camera component
    //==========================
    CameraComponent::CameraComponent(GameObject* pGameObject)
        : Component(pGameObject)
    {
    }

    CameraComponent::CameraComponent(GameObject* pGameObject, FreeCamera* camera)
        : Component(pGameObject)
        , m_pCamera(camera)
    {
        m_position = m_pCamera->getPosition();
    }

    CameraComponent::~CameraComponent()
    {
    }

    vec3 CameraComponent::getForward()
    {
        return m_pCamera->getForward();
    }

    vec3 CameraComponent::getRight()
    {
        return m_pCamera->getRight();
    }

    float CameraComponent::getYaw()
    {
        return m_pCamera->getYaw();
    }

    void CameraComponent::cameraRotation(vec3 direction, float delta, float speed)
    {
        m_pCamera->moveCameraRotation(direction, delta, speed);
    }



    //==========================
    // Player Component
    //==========================
    //PlayerComponent::PlayerComponent(GameObject* pGameObject, std::vector<vec3> heightMapPixelPositions)
    //    : Component(pGameObject),
    //    m_pixelPositions(heightMapPixelPositions)
    //{
    //}
    //
    //PlayerComponent::~PlayerComponent()
    //{
    //}
    //
    //void PlayerComponent::updateMovement(float deltaTime, float speed, vec3 dir)
    //{
    //    TransformComponent* pTransform = m_pGameObject->getComponent<TransformComponent>();
    //    
    //    pTransform->m_position = dir * deltaTime * speed;
    //}
} // namespace fw
