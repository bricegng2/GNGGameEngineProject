#pragma once

#include "DataTypes.h"

class VirtualGamepad;

class Player3DMovementComponent : public fw::Component
{
public:
    Player3DMovementComponent(fw::GameObject* pGameObject, VirtualGamepad* pGamepad);
    virtual ~Player3DMovementComponent();

    static const char* getStaticType() { return "Player3DMovementComponent"; }
    virtual const char* getType() override { return getStaticType(); }

public:
    VirtualGamepad* m_pGamepad = nullptr;

    float m_speed = 10.0f;
};
