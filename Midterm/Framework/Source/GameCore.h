//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "EventSystem/EventListener.h"

namespace fw
{
    class Event;
    class EventManager;
    class FWCore;
    class Uniforms;

    class GameCore
    {
    public:
        GameCore(FWCore& fwCore) : m_FWCore( fwCore ) {}
        virtual ~GameCore() = 0 {}

        virtual void startFrame(float deltaTime) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;

        // Getters.
        FWCore* getFramework() { return &m_FWCore; }
        EventManager* getEventManager() { return m_pEventManager; }
        Uniforms* getUniforms() { return m_pUniforms; }

    protected:
        FWCore& m_FWCore;

        // Resources.
        Uniforms* m_pUniforms = nullptr;

        // Events.
        EventManager* m_pEventManager = nullptr;
    };
} // namespace fw
