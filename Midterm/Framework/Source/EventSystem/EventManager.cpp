//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "EventManager.h"
#include "Events.h"
#include "GameCore.h"

namespace fw {

    EventManager::EventManager()
    {
    }

    EventManager::~EventManager()
    {
        while( m_eventQueue.empty() == false )
        {
            delete m_eventQueue.front();
            m_eventQueue.pop();
        }
    }

    void EventManager::addEvent(Event* pEvent)
    {
        m_eventQueue.push( pEvent );
    }

    void EventManager::dispatchAllEvents(GameCore* pGameCore)
    {
        if( m_eventQueue.empty() )
            return;

        while( m_eventQueue.empty() == false )
        {
            // Remove it from the queue.
            Event* pEvent = m_eventQueue.front();
            m_eventQueue.pop();

            // Send it to all the listener subclasses.
            EventType type = pEvent->getType();
            for( auto listener : m_listeners[type] )
            {
                listener->onEvent( pEvent );
            }

            // Delete the event.
            delete pEvent;
        }
    }

} // namespace fw
