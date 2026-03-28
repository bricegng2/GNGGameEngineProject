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

VirtualGamepad::VirtualGamepad(fw::EventManager* pEventManager)
    : m_pEventManager( pEventManager )
    , onInputEventHandler( std::bind(&VirtualGamepad::onInputEvent, this, std::placeholders::_1) )
{
    m_pEventManager->registerListenerFunction<fw::InputEvent>( &onInputEventHandler );
}

VirtualGamepad::~VirtualGamepad()
{
    m_pEventManager->unregisterListenerFunction<fw::InputEvent>( &onInputEventHandler );
}

void VirtualGamepad::startFrame()
{
    m_oldFlags = m_flags;
}

void VirtualGamepad::onInputEvent(fw::Event* pEvent)
{
    if( pEvent->getType() == fw::InputEvent::getStaticEventType() )
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>( pEvent );
        
        if( pInputEvent->getDeviceType() == fw::InputEvent::DeviceType::Keyboard )
        {
            if( pInputEvent->getDeviceState() == fw::InputEvent::DeviceState::Pressed )
            {
                switch( pInputEvent->getKeyCode() )
                {
                case 'W': case VK_UP:       { m_flags |= Mask::Up; }        break;
                case 'S': case VK_DOWN:     { m_flags |= Mask::Down; }      break;
                case 'A': case VK_LEFT:     { m_flags |= Mask::Left; }      break;
                case 'D': case VK_RIGHT:    { m_flags |= Mask::Right; }     break;
                case 'Z':                   { m_flags |= Mask::Action; }    break;
                }
            }

            if( pInputEvent->getDeviceState() == fw::InputEvent::DeviceState::Released )
            {
                switch( pInputEvent->getKeyCode() )
                {
                case 'W': case VK_UP:       { m_flags &= ~Mask::Up; }        break;
                case 'S': case VK_DOWN:     { m_flags &= ~Mask::Down; }      break;
                case 'A': case VK_LEFT:     { m_flags &= ~Mask::Left; }      break;
                case 'D': case VK_RIGHT:    { m_flags &= ~Mask::Right; }     break;
                case 'Z':                   { m_flags &= ~Mask::Action; }    break;
                }
            }
        }
    }
}

vec2 VirtualGamepad::getDirection()
{
    vec2 dir;
    
    if( isHeld( VirtualGamepad::Mask::Up ) )
    {
        dir.y += 1;
    }
    if( isHeld( VirtualGamepad::Mask::Down ) )
    {
        dir.y += -1;
    }
    if( isHeld( VirtualGamepad::Mask::Left ) )
    {
        dir.x += -1;
    }
    if( isHeld( VirtualGamepad::Mask::Right ) )
    {
        dir.x += 1;
    }

    dir.normalize();

    return dir;
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
