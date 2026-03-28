#pragma once

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Physics/PhysicsTypes.h"
#include "EventSystem/EventListener.h"

namespace fw
{
    class GameObject;
    class Mesh;
    class Material;
    class PhysicsBody;
    class PhysicsWorld;
    class Uniforms;

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
} // namespace fw
