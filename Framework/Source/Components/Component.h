#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Physics/PhysicsTypes.h"
#include "EventSystem/EventListener.h"
#include "Objects/FreeCamera.h"

namespace fw
{
    class GameObject;
    class Mesh;
    class Material;
    class PhysicsBody;
    class PhysicsWorld;
    class Uniforms;
    class FreeCamera;

    //==========================
    // Base component class
    //==========================
    class Component
    {
    public:
        Component(GameObject* pGameObject);
        virtual ~Component();

        virtual const char* getType() = 0;

        GameObject* getGameObject() { return m_pGameObject; }

    protected:
        GameObject* m_pGameObject = nullptr;
    };

    //==========================
    // Transform
    //==========================
    class TransformComponent : public Component
    {
        friend class ComponentManager;

    public:
        TransformComponent(GameObject* pGameObject);
        TransformComponent(GameObject* pGameObject, vec3 pos, vec3 rot, vec3 scale);

        static const char* getStaticType() { return "TransformComponent"; }
        virtual const char* getType() override { return getStaticType(); }

    public:
        vec3 m_position = vec3(0,0,0);
        vec3 m_rotation = vec3(0,0,0);
        vec3 m_scale = vec3(1,1,1);

    protected:
        mat4 m_worldTransform;
    };

    //==========================
    // RenderComponent
    //==========================
    class RenderComponent : public Component
    {
        friend class ComponentManager;

    public:
        RenderComponent(GameObject* pGameObject);
        RenderComponent(GameObject* pGameObject, Mesh* pMesh, Material* pMaterial);
        ~RenderComponent();

        static const char* getStaticType() { return "RenderComponent"; }
        virtual const char* getType() override { return getStaticType(); }

    public:
        Mesh* m_pMesh = nullptr;
        Material* m_pMaterial = nullptr;
    };

    //==========================
    // Physics Body
    //==========================
    class PhysicsBodyComponent : public Component
    {
        friend class ComponentManager;

    public:
        PhysicsBodyComponent(GameObject* pGameObject);
        PhysicsBodyComponent(GameObject* pGameObject, PhysicsWorld* pWorld, bool isDynamic, fw::ShapeType shapeType);
        ~PhysicsBodyComponent();

        static const char* getStaticType() { return "PhysicsBodyComponent"; }
        virtual const char* getType() override { return getStaticType(); }

        void createBody(PhysicsWorld* pWorld, bool isDynamic, fw::ShapeType shapeType);

    public:
        PhysicsWorld* m_pWorld = nullptr;
        PhysicsBody* m_pBody = nullptr;

    protected:
        void sync();
        void syncToTransform();
    };

    //==========================
    // Player Component
    //==========================
    //class PlayerComponent : public Component
    //{
    //    friend class ComponentManager;
    //
    //public:
    //    PlayerComponent(GameObject* pGameObject, std::vector<vec3> heightMapPixelPositions);
    //    ~PlayerComponent();
    //
    //    static const char* getStaticType() { return "PlayerComponent"; }
    //    virtual const char* getType() override { return getStaticType(); }
    //
    //public:
    //    std::vector<vec3> m_pixelPositions;
    //    void updateMovement(float deltaTime, float speed, vec3 dir);
    //};

    class CameraComponent : public Component
    {
        friend class ComponentManager;
    public:
        CameraComponent(GameObject* pGameObject);
        CameraComponent(GameObject* pGameObject, FreeCamera* camera);
        ~CameraComponent();

        static const char* getStaticType() { return "CameraComponent"; }
        virtual const char* getType() override { return getStaticType(); }

    public:
        fw::FreeCamera* m_pCamera = nullptr;
        vec3 m_position = vec3(0, 0, 0);

        void setPosition(vec3 pos) { m_pCamera->setPosition(pos); }

        vec3 getForward();
        vec3 getRight();
        float getYaw();

        void cameraRotation(vec3 direction, float delta, float speed);
    };
} // namespace fw
