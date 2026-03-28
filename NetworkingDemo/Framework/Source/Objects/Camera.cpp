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

namespace fw {

    Camera::Camera(Scene* pScene, vec3 pos)
        : GameObject( pScene, "Camera", pos, nullptr, nullptr )
    {
        FWCore* pFW = pScene->getGameCore()->getFramework();
        setAspectRatio( (float)pFW->getWindowClientWidth()/pFW->getWindowClientHeight() );

        pScene->getGameCore()->getEventManager()->registerListener<WindowResizeEvent>( this );
    }

    Camera::~Camera()
    {
        m_pScene->getGameCore()->getEventManager()->unregisterListener<WindowResizeEvent>( this );
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
        viewMatrix.createLookAtView( m_position - vec3(0,0,10), vec3(0,1,0), m_position );
        pUniforms->set( "u_matView", viewMatrix );

        mat4 projMatrix;
        float zoom = 7.5;
        //projMatrix.createPerspectiveVFoV( 90, m_aspectRatio, 0.01f, 100.0f );
        projMatrix.createOrtho( -zoom*m_aspectRatio, zoom, -zoom, zoom, 0.01f, 100.0f );
        pUniforms->set( "u_matProj", projMatrix );
    }

} // namespace fw
