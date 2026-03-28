#pragma once

namespace fw
{
    class Component;
    class GameObject;
    class Material;

    class ComponentManager
    {
    public:
        ComponentManager();
        virtual ~ComponentManager();

        void addComponent(Component* pComponent);
        Component* createComponent(GameObject* pGameObject, const char* type);

        void updateTransforms();
        void renderMeshes(int viewID, Material* pOverrideMaterial);
        void syncPhysicsObjects();
        void syncPhysicsBodiesToGameObjectTransforms();

        void removeComponent(Component* pComponent);

        std::vector<Component*>& getComponentsOfType(const char* type) { return m_components[type]; }

    protected:
        std::map<const char*, std::vector<Component*>> m_components;
    };
} // namespace fw
