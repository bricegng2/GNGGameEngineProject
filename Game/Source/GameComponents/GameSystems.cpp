#include "Framework.h"
#include "Player2DMovementComponent.h"
#include "Player3DMovementComponent.h"
#include "Components/Component.h"
#include "Objects/VirtualGamepad.h"
#include "GameSystems.h"
#include "Meshes/Shapes.h"

void UpdatePlayer2DMovementComponents(fw::ComponentManager* pComponentManager, float deltaTime)
{
    std::vector<fw::Component*>& pComponents = pComponentManager->getComponentsOfType(Player2DMovementComponent::getStaticType());

    for (fw::Component* pComponent : pComponents)
    {
        Player2DMovementComponent* pMovementComponent = static_cast<Player2DMovementComponent*>(pComponent);

        fw::TransformComponent* pTransform = pMovementComponent->getGameObject()->getComponent<fw::TransformComponent>();

        vec3 dir(0);

        if (pMovementComponent->m_pGamepad->isHeld(VirtualGamepad::Up))
            dir.y++;
        if (pMovementComponent->m_pGamepad->isHeld(VirtualGamepad::Down))
            dir.y--;
        if (pMovementComponent->m_pGamepad->isHeld(VirtualGamepad::Right))
            dir.x++;
        if (pMovementComponent->m_pGamepad->isHeld(VirtualGamepad::Left))
            dir.x--;

        dir.normalize();

        pTransform->m_position += dir * deltaTime * pMovementComponent->m_speed;

        if (pMovementComponent->m_pGamepad->wasPressed(VirtualGamepad::Mask::Action))
        {
            pTransform->m_position.x = fw::Random::randomFloat(0.0f, 10.0f);
            pTransform->m_position.y = fw::Random::randomFloat(0.0f, 10.0f);
        }
    }
}

void update3DPlayerMovementComponents(fw::ComponentManager* pComponentManager, float deltaTime)
{
    std::vector<fw::Component*>& pComponents = pComponentManager->getComponentsOfType(Player3DMovementComponent::getStaticType());

    for (fw::Component* pComponent : pComponents)
    {
        Player3DMovementComponent* pPlayer = static_cast<Player3DMovementComponent*>(pComponent);
        fw::TransformComponent* pTransform = pPlayer->getGameObject()->getComponent<fw::TransformComponent>();

        vec3 dir(0);

        if (pPlayer->m_pGamepad->isHeld(VirtualGamepad::Up))
        {
            dir.z++;
        }
        if (pPlayer->m_pGamepad->isHeld(VirtualGamepad::Down))
        {
            dir.z--;
        }
        if (pPlayer->m_pGamepad->isHeld(VirtualGamepad::Left))
        {
            dir.x--;
        }
        if (pPlayer->m_pGamepad->isHeld(VirtualGamepad::Right))
        {
            dir.x++;
        }

        dir.normalize();

        vec3 cameraForward = pComponent->getGameObject()->getComponent<fw::CameraComponent>()->getForward();
        vec3 cameraRight = pComponent->getGameObject()->getComponent<fw::CameraComponent>()->getRight();

        vec3 movement = (cameraForward * dir.z) + (cameraRight * dir.x);
        movement.y = 0.0f; // make sure the player stays on the height map
        movement.normalize();

        vec3 newPosition = pTransform->m_position + movement * deltaTime * pPlayer->m_speed;
        newPosition.y = getHeightAtXZ(newPosition.x, newPosition.z);
        pTransform->m_position = newPosition;
    }

}