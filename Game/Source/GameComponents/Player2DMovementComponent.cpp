#include "Framework.h"
#include "Player2DMovementComponent.h"
#include "Meshes/VertexFormats.h"
#include "Objects/VirtualGamepad.h"

#include "stb/stb_image.h"

Player2DMovementComponent::Player2DMovementComponent(fw::GameObject* pGameObject, VirtualGamepad* pGamepad)
    : fw::Component( pGameObject )
    , m_pGamepad( pGamepad )
{
}

Player2DMovementComponent::~Player2DMovementComponent()
{
}
