//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

class VirtualGamepad : public fw::EventListener
{
public:
    enum Mask
    {
        Up      = 1<<0,
        Down    = 1<<1,
        Left    = 1<<2,
        Right   = 1<<3,
        Action  = 1<<4,
    };

    VirtualGamepad(fw::EventManager* pEventManager);
    virtual ~VirtualGamepad();

    void startFrame();
    virtual void onEvent(fw::Event* pEvent) override;

    vec2 getDirection();

    bool isHeld(Mask mask);
    bool wasPressed(Mask mask);
    bool wasReleased(Mask mask);

protected:
    fw::EventManager* m_pEventManager = nullptr;

    unsigned int m_flags = 0;
    unsigned int m_oldFlags = 0;
};
