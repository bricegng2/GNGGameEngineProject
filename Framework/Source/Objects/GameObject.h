//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Math/Vector.h"

namespace fw
{
    class Camera;
    class Component;
    class GameCore;
    class Material;
    class Mesh;
    class Scene;
    class Uniforms;

    class GameObject
    {
    public:
        GameObject(Scene* pScene, std::string name);
        virtual ~GameObject();

        // Getters.
        Scene* getScene() { return m_pScene; }
        std::string getName() { return m_name; }

        void addComponent(Component* pComponent);
        template<typename Type> Type* getComponent()
        {
            for( Component* pComponent : m_components )
            {
                if( pComponent->getType() == Type::getStaticType() )
                {
                    return static_cast<Type*>( pComponent );
                }
            }

            return nullptr;
        }
    protected:
        Scene* m_pScene = nullptr;

        std::string m_name;

        std::vector<Component*> m_components;
    };

} // namespace fw
