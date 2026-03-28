//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Events.h"

namespace fw
{
    class EventListener;
    class GameCore;

    class EventManager
    {
    public:
        struct ListenerFunction
        {
            ListenerFunction(std::function<void(Event*)> f) : func( f ) {}
            std::function<void(Event*)> func;
        };

    public:
        EventManager();
        ~EventManager();

        template<class Type> void registerListener(EventListener* pListener)
        {
            EventType type = Type::getStaticEventType();
            m_listeners[type].push_back( pListener );
        }

        template<class Type> void unregisterListener(EventListener* pListener)
        {
            EventType type = Type::getStaticEventType();
            std::vector<EventListener*>& list = m_listeners[type];

            auto it = std::find( list.begin(), list.end(), pListener );
            if( it != list.end() )
            {
                list.erase(it);
            }
        }

        template<class Type> void registerListenerFunction(ListenerFunction* func)
        {
            EventType type = Type::getStaticEventType();
            m_listenerFunctions[type].push_back( func );
        }

        template<class Type> void unregisterListenerFunction(ListenerFunction* func)
        {
            EventType type = Type::getStaticEventType();
            std::vector<ListenerFunction*>& list = m_listenerFunctions[type];

            auto it = std::find( list.begin(), list.end(), func );
            if( it != list.end() )
            {
                list.erase( it );
            }
        }

        void addEvent(Event* pEvent);
        void dispatchAllEvents(GameCore* pGameCore);

    protected:
        std::queue<Event*> m_eventQueue;

        std::map<EventType, std::vector<EventListener*>> m_listeners;
        std::map<EventType, std::vector<ListenerFunction*>> m_listenerFunctions;
    };
} // namespace fw
