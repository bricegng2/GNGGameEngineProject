//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "FreeCamera.h"
#include "FWCore.h"
#include "GameCore.h"
#include "Scene.h"
#include "Utility/Uniforms.h"
#include "EventSystem/Events.h"
#include "EventSystem/EventManager.h"
#include <imgui/imgui.h>

namespace fw
{
    FreeCamera::FreeCamera(Scene* pScene, vec3 pos)
        : m_pScene(pScene)
        , m_position(pos)
        , m_rotation(-20, 0, 0)
    {
        m_rotationMatrix.setIdentity();

        FWCore* pFW = pScene->getGameCore()->getFramework();
        setAspectRatio((float)pFW->getWindowClientWidth() / pFW->getWindowClientHeight());

        pScene->getGameCore()->getEventManager()->registerListener<WindowResizeEvent>(this);
    }

    FreeCamera ::~FreeCamera()
    {
    }

    void FreeCamera::onEvent(Event* pEvent)
    {
        if (pEvent->getType() == WindowResizeEvent::getStaticEventType())
        {
            WindowResizeEvent* pResizeEvent = static_cast<WindowResizeEvent*>(pEvent);
            int width = pResizeEvent->getWidth();
            int height = pResizeEvent->getHeight();

            setAspectRatio((float)width / height);
        }
    }

    void FreeCamera::enable(int viewID)
    {
        myClamp(m_rotation.x, -45.0f, 45.0f);

        float m_distance = 6.0f;

        float sx = sin(m_rotation.x / 180 * PI);
        float sy = sin(m_rotation.y / 180 * PI);
        float cx = cos(m_rotation.x / 180 * PI);
        float cy = cos(m_rotation.y / 180 * PI);
        vec3 offset = vec3(cx * sy * m_distance, -sx * m_distance, -1 * cx * cy * m_distance);

        Uniforms* pUniforms = m_pScene->getGameCore()->getUniforms();

        static bool noOffset = false;
        if (ImGui::Button("Toggle First/Third person camera"))
        {
            noOffset = !noOffset;
        }

        if (noOffset)
        {
            offset = vec3(0.0f, 0.0f, 0.0f);
        }

        // Setup uniforms.
        mat4 viewMatrix = m_rotationMatrix;
        viewMatrix.translate(m_position + offset);
        viewMatrix.inverse();
        pUniforms->set("u_matView", viewMatrix);

        mat4 projMatrix;
        projMatrix.createPerspectiveVFoV(65, m_aspectRatio, 0.01f, 100.0f);
        pUniforms->set("u_matProj", projMatrix);
    }

    void FreeCamera::moveCameraPosition(vec3 direction, float delta, float speed)
    {
        //m_position.y += direction.y * m_rotationMatrix.getAt().y * delta * speed;
        //m_position.x += direction.x * m_rotationMatrix.getRight().x * delta * speed;

        if (direction.z == 1.0f)
        {
            m_position += m_rotationMatrix.getAt() * delta * speed;
        }
        if (direction.z == -1.0f)
        {
            m_position -= m_rotationMatrix.getAt() * delta * speed;
        }
        if (direction.x == 1.0f)
        {
            m_position += m_rotationMatrix.getRight() * delta * speed;
        }
        if (direction.x == -1.0f)
        {
            m_position -= m_rotationMatrix.getRight() * delta * speed;
        }
    }

    void FreeCamera::moveCameraRotation(vec3 direction, float delta, float speed)
    {
        if (direction == previousDirection)
        {
            return;
        }

        m_rotation += direction * delta * speed;
        m_rotationMatrix.createRotation(m_rotation);

        previousDirection = direction;
    }

    vec3 FreeCamera::getForward()
    {
        return m_rotationMatrix.getAt();
    }

    vec3 FreeCamera::getRight()
    {
        return m_rotationMatrix.getRight();
    }

    float FreeCamera::getYaw()
    {
        return m_rotation.y;
    }


} // namespace fw
