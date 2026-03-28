#include "Framework.h"
#include "Player3DMovementComponent.h"
#include "Meshes/VertexFormats.h"
#include "Objects/VirtualGamepad.h"

#include "stb/stb_image.h"

Player3DMovementComponent::Player3DMovementComponent(fw::GameObject* pGameObject, VirtualGamepad* pGamepad)
    : fw::Component( pGameObject )
    , m_pGamepad( pGamepad )
{
}

Player3DMovementComponent::~Player3DMovementComponent()
{
}
