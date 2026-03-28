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
#include "Components/ComponentManager.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Scene.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"

namespace fw
{
    GameObject::GameObject(Scene* pScene, std::string name)
        : m_pScene( pScene )
        , m_name( name )
    {
    }

    GameObject::~GameObject()
    {
        for( Component* pComponent : m_components )
        {
            m_pScene->getComponentManager()->removeComponent(pComponent);
            delete pComponent;
        }
    }

    void GameObject::addComponent(Component* pComponent)
    {
        m_components.push_back( pComponent );
        m_pScene->getComponentManager()->addComponent( pComponent );
    }

} // namespace fw
