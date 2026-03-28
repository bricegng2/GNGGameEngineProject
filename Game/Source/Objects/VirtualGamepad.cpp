//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"
#include "DataTypes.h"

#include "VirtualGamepad.h"

VirtualGamepad::VirtualGamepad(fw::EventManager* pEventManager, fw::FWCore* fwcore)
    : m_pEventManager(pEventManager)
    , m_pFWCore(fwcore)
    , onInputEventHandler(std::bind(&VirtualGamepad::onInputEvent, this, std::placeholders::_1))
{
    m_pEventManager->registerListenerFunction<fw::InputEvent>(&onInputEventHandler);
    m_pEventManager->registerListenerFunction<fw::MouseEvent>(&onInputEventHandler);
}

VirtualGamepad::~VirtualGamepad()
{
    m_pEventManager->unregisterListenerFunction<fw::InputEvent>(&onInputEventHandler);
    m_pEventManager->unregisterListenerFunction<fw::MouseEvent>(&onInputEventHandler);
}

void VirtualGamepad::startFrame()
{
    m_oldFlags = m_flags;
}

void VirtualGamepad::onInputEvent(fw::Event* pEvent)
{
    if (pEvent->getType() == fw::InputEvent::getStaticEventType())
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>(pEvent);

        if (pInputEvent->getDeviceType() == fw::InputEvent::DeviceType::Keyboard)
        {
            if (pInputEvent->getDeviceState() == fw::InputEvent::DeviceState::Pressed)
            {
                switch (pInputEvent->getKeyCode())
                {
                case 'W':               { m_flags |= Mask::Up; }        break;
                case 'S':               { m_flags |= Mask::Down; }      break;
                case 'A':               { m_flags |= Mask::Left; }      break;
                case 'D':               { m_flags |= Mask::Right; }     break;
                case 'Z':               { m_flags |= Mask::Action; }    break;
                case 'J':               { m_flags |= Mask::ZoomIn; }    break;
                case 'K':               { m_flags |= Mask::ZoomOut; }   break;
                case VK_UP:             { m_flags |= Mask::RotateUp; }   break;
                case VK_DOWN:           { m_flags |= Mask::RotateDown; }   break;
                case VK_LEFT:           { m_flags |= Mask::RotateRight; }   break;
                case VK_RIGHT:          { m_flags |= Mask::RotateLeft; }   break;
                case 'E':               { m_flags |= Mask::CreateBox; } break;
                case 'Q':               { m_flags |= Mask::DestroyBox; } break;
                case VK_SPACE:          { m_flags |= Mask::Space; } break;
                }
            }

            if (pInputEvent->getDeviceState() == fw::InputEvent::DeviceState::Released)
            {
                switch (pInputEvent->getKeyCode())
                {
                case 'W':               { m_flags &= ~Mask::Up; }        break;
                case 'S':               { m_flags &= ~Mask::Down; }      break;
                case 'A':               { m_flags &= ~Mask::Left; }      break;
                case 'D':               { m_flags &= ~Mask::Right; }     break;
                case 'Z':               { m_flags &= ~Mask::Action; }    break;
                case 'J':               { m_flags &= ~Mask::ZoomIn; }     break;
                case 'K':               { m_flags &= ~Mask::ZoomOut; }    break;
                case VK_UP:             { m_flags &= ~Mask::RotateUp; }   break;
                case VK_DOWN:           { m_flags &= ~Mask::RotateDown; }   break;
                case VK_LEFT:           { m_flags &= ~Mask::RotateRight; }   break;
                case VK_RIGHT:          { m_flags &= ~Mask::RotateLeft; }   break;
                case 'E':               { m_flags &= ~Mask::CreateBox; } break;
                case 'Q':               { m_flags &= ~Mask::DestroyBox; } break;
                case VK_SPACE:          { m_flags &= ~Mask::Space; } break;
                }
            }
        }
    }

    else if (pEvent->getType() == fw::MouseEvent::getStaticEventType())
    {
        fw::MouseEvent* pMouseEvent = static_cast<fw::MouseEvent*>(pEvent);

        calculateMouseDirection(vec2(pMouseEvent->getX(), pMouseEvent->getY()));
    }
}

vec3 VirtualGamepad::getDirection()
{
    vec3 dir;

    if (isHeld(VirtualGamepad::Mask::ZoomIn))
    {
        dir.y += -1;
    }
    if (isHeld(VirtualGamepad::Mask::ZoomOut))
    {
        dir.y += 1;
    }
    if (isHeld(VirtualGamepad::Mask::Right))
    {
        dir.x += 1;
    }
    if (isHeld(VirtualGamepad::Mask::Left))
    {
        dir.x += -1;
    }
    if (isHeld(VirtualGamepad::Mask::Up))
    {
        dir.z += 1;
    }
    if (isHeld(VirtualGamepad::Mask::Down))
    {
        dir.z += -1;
    }

    dir.normalize();

    return dir;
}

vec3 VirtualGamepad::getRotation()
{
    vec3 dir;

    if (isHeld(VirtualGamepad::Mask::RotateUp))
    {
        dir.x += -1;
    }
    if (isHeld(VirtualGamepad::Mask::RotateDown))
    {
        dir.x += 1;
    }
    if (isHeld(VirtualGamepad::Mask::RotateRight))
    {
        dir.y += 1;
    }
    if (isHeld(VirtualGamepad::Mask::RotateLeft))
    {
        dir.y += -1;
    }

    dir.normalize();

    return dir;
}

void VirtualGamepad::calculateMouseDirection(vec2 mouseCoords)
{
    static vec2 smoothedMouseDelta = { 0.0f, 0.0f };                                               // this needs to be used so the mouse feels smooth
    float smoothingFactor = 0.1f;                                                                  // this needs to be used so the mouse feels smooth
    smoothedMouseDelta = smoothedMouseDelta + (mouseCoords - smoothedMouseDelta) * smoothingFactor;// this needs to be used so the mouse feels smooth

    m_direction.x = -smoothedMouseDelta.y * 0.8;
    m_direction.y = -smoothedMouseDelta.x * 0.8;

    prevMousePos = mouseCoords;

    RECT rc = { 0, 0, m_pFWCore->getWindowClientWidth(), m_pFWCore->getWindowClientHeight()};
    ClipCursor(&rc);
}

vec3 VirtualGamepad::getMouseDirection()
{
    return m_direction;
}

bool VirtualGamepad::isHeld(Mask mask)
{
    return (m_flags & mask) != 0;
}

bool VirtualGamepad::wasPressed(Mask mask)
{
    return ((m_flags & mask) != 0) && ((m_oldFlags & mask) == 0);
}

bool VirtualGamepad::wasReleased(Mask mask)
{
    return ((m_flags & mask) == 0) && ((m_oldFlags & mask) != 0);
}
