//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "Camera.h"
#include "FWCore.h"
#include "GameCore.h"
#include "Scene.h"
#include "Utility/Uniforms.h"
#include "EventSystem/Events.h"
#include "EventSystem/EventManager.h"

namespace fw
{
    Camera::Camera(Scene* pScene, vec3 pos, vec3 at)
        : m_pScene( pScene )
        , m_position( pos )
        , m_lookAtPosition( at )
    {
        FWCore* pFW = pScene->getGameCore()->getFramework();
        setAspectRatio( (float)pFW->getWindowClientWidth()/pFW->getWindowClientHeight() );

        pScene->getGameCore()->getEventManager()->registerListener<WindowResizeEvent>( this );
    }

    Camera::~Camera()
    {
    }

    void Camera::onEvent(Event* pEvent)
    {
        if( pEvent->getType() == WindowResizeEvent::getStaticEventType() )
        {
            WindowResizeEvent* pResizeEvent = static_cast<WindowResizeEvent*>( pEvent );
            int width = pResizeEvent->getWidth();
            int height = pResizeEvent->getHeight();

            setAspectRatio( (float)width/height );
        }
    }

    void Camera::enable(int viewID)
    {
        Uniforms* pUniforms = m_pScene->getGameCore()->getUniforms();

        // Setup uniforms.
        mat4 viewMatrix;
        viewMatrix.createLookAtView( m_position, vec3(0,1,0), m_lookAtPosition );
        pUniforms->set( "u_matView", viewMatrix );

        mat4 projMatrix;
        projMatrix.createPerspectiveVFoV( 90, m_aspectRatio, 0.01f, 100.0f );
        pUniforms->set( "u_matProj", projMatrix );
    }

    void Camera::moveCamera(vec3 direction, float delta, float speed)
    {
        m_position += direction * delta * speed;
        
        m_lookAtPosition += direction * delta * speed;
    }

    void Camera::moveLookCamera(vec3 direction, float delta, float speed)
    {
        m_position += direction * delta * speed;
    }

    void Camera::rotateCamera(vec3 direction, float delta, float speed)
    {
        m_lookAtPosition += direction * delta * speed;
    }

    void Camera::moveCameraInCircle(float deltaTime)
    {
        // doesnt work dont know why
        /*float speed = 5.0f;
        float m_angle = 120.0f;

        m_position.x += m_lookAtPosition.x + cos((float)M_PI * speed * deltaTime + m_angle) * 10.0f;
        m_position.z += m_lookAtPosition.z + sin((float)M_PI * speed * deltaTime + m_angle) * 10.0f;*/
    }


} // namespace fw
