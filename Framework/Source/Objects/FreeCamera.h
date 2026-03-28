//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Math/Matrix.h"
#include "EventSystem/EventListener.h"
#include "Objects/GameObject.h"

class VirtualGamepad;

namespace fw
{
    class FreeCamera : public EventListener
    {
    public:
        FreeCamera(Scene* pScene, vec3 pos);
        virtual ~FreeCamera();

        virtual void onEvent(Event* pEvent) override;
        void enable(int viewID);

        void moveCameraPosition(vec3 direction, float delta, float speed);

        void moveCameraRotation(vec3 direction, float delta, float speed);

        // Setters.
        void setAspectRatio(float32 aspectRatio) { m_aspectRatio = aspectRatio; }

        vec3 getPosition() { return m_position; }

        vec3 getForward();
        vec3 getRight();
        float getYaw();

        void setPosition(vec3 pos) { m_position = pos; }

    protected:
        Scene* m_pScene = nullptr;
        vec3 m_position;
        vec3 m_rotation;
        mat4 m_rotationMatrix;
        float32 m_aspectRatio = 1.0f;

        vec3 previousDirection = vec3(0.0f, 0.0f, 0.0f);
    };
} // namespace fw
