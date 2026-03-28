#include "Framework.h"
#include "Player2DMovementComponent.h"
#include "Objects/VirtualGamepad.h"

void UpdatePlayer2DMovementComponents(fw::ComponentManager* pComponentManager, float deltaTime)
{
    std::vector<fw::Component*>& pComponents = pComponentManager->getComponentsOfType( Player2DMovementComponent::getStaticType() );

    for( fw::Component* pComponent : pComponents )
    {
        Player2DMovementComponent* pMovementComponent = static_cast<Player2DMovementComponent*>(pComponent);

        fw::TransformComponent* pTransform = pMovementComponent->getGameObject()->getComponent<fw::TransformComponent>();

        vec3 dir(0);

        if( pMovementComponent->m_pGamepad->isHeld( VirtualGamepad::Up ) )
            dir.y++;
        if( pMovementComponent->m_pGamepad->isHeld( VirtualGamepad::Down ) )
            dir.y--;
        if( pMovementComponent->m_pGamepad->isHeld( VirtualGamepad::Right ) )
            dir.x++;
        if( pMovementComponent->m_pGamepad->isHeld( VirtualGamepad::Left ) )
            dir.x--;

        dir.normalize();

        pTransform->m_position += dir * deltaTime * pMovementComponent->m_speed;

        if( pMovementComponent->m_pGamepad->wasPressed( VirtualGamepad::Mask::Action ) )
        {
            pTransform->m_position.x = fw::Random::randomFloat( 0.0f, 10.0f );
            pTransform->m_position.y = fw::Random::randomFloat( 0.0f, 10.0f );
        }
    }
}
