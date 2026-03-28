#pragma once

#include "DataTypes.h"

class VirtualGamepad;

class Player2DMovementComponent : public fw::Component
{
public:
    Player2DMovementComponent(fw::GameObject* pGameObject, VirtualGamepad* pGamepad);
    virtual ~Player2DMovementComponent();

    static const char* getStaticType() { return "Player2DMovementComponent"; }
    virtual const char* getType() override { return getStaticType(); }

public:
    VirtualGamepad* m_pGamepad = nullptr;

    float m_speed = 3.0f;
};
