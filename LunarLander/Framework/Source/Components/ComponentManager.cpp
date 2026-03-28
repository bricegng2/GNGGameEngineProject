#include "CoreHeaders.h"
#include "ComponentManager.h"
#include "Component.h"
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"
#include "../Libraries/bgfx/include/bgfx/bgfx.h"

namespace fw
{
    ComponentManager::ComponentManager()
    {
    }

    ComponentManager::~ComponentManager()
    {
    }

    void fw::ComponentManager::addComponent(Component* pComponent)
    {
        std::vector<Component*>& list = m_components[pComponent->getType()];

        assert( std::find(list.begin(), list.end(), pComponent) == list.end() );

        m_components[pComponent->getType()].push_back( pComponent );
    }

    Component* ComponentManager::createComponent(GameObject* pGameObject, const char* type)
    {
        if( strcmp( type, TransformComponent::getStaticType() ) == 0 )
        {
            return new TransformComponent( pGameObject );
        }
        else if( strcmp( type, RenderComponent::getStaticType() ) == 0 )
        {
            return new RenderComponent( pGameObject );
        }
        return nullptr;
    }

    void ComponentManager::updateTransforms()
    {
        for( Component* pComponent : m_components[TransformComponent::getStaticType()] )
        {
            TransformComponent* pTransform = static_cast<TransformComponent*>(pComponent);
            pTransform->m_worldTransform.createSRT( pTransform->m_scale, pTransform->m_rotation, pTransform->m_position );
        }
    }

    void ComponentManager::renderMeshes(int viewID, Material* pOverrideMaterial)
    {
        for( Component* pComponent : m_components[RenderComponent::getStaticType()] )
        {
            if (pComponent->getGameObject()->isActive())
            {
                RenderComponent* pRender = static_cast<RenderComponent*>(pComponent);
                mat4& worldMatrix = pRender->getGameObject()->getComponent<TransformComponent>()->m_worldTransform;

                Uniforms* pUniforms = pRender->getGameObject()->getScene()->getGameCore()->getUniforms();
                bgfx::setUniform(pUniforms->getUniform("u_matWorld"), &worldMatrix);

                pRender->m_pMesh->draw(viewID, pUniforms, pOverrideMaterial ? pOverrideMaterial : pRender->m_pMaterial);
            }
        }
    }

    void ComponentManager::syncPhysicsObjects()
    {
        for( Component* pComponent : m_components[PhysicsBodyComponent::getStaticType()] )
        {
            PhysicsBodyComponent* pPhysics = static_cast<PhysicsBodyComponent*>( pComponent );
            pPhysics->sync();
        }
    }

    void ComponentManager::syncPhysicsBodiesToGameObjectTransforms()
    {
        for( Component* pComponent : m_components[PhysicsBodyComponent::getStaticType()] )
        {
            PhysicsBodyComponent* pPhysics = static_cast<PhysicsBodyComponent*>( pComponent );
            pPhysics->syncToTransform();
        }
    }

    void ComponentManager::removeComponent(Component* pComponent)
    {
        std::vector<Component*>& list = m_components[pComponent->getType()];

        // Remove all entries of pComponent from our list.
        list.erase( std::remove(list.begin(), list.end(), pComponent), list.end() );
    }
} // namespace fw
