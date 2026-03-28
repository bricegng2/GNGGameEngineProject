//
// Copyright (c) 2022-2025 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "Uniforms.h"

namespace fw {

    Uniforms::Uniforms()
    {
    }

    Uniforms::~Uniforms()
    {
        for( auto& uniformPair : m_map )
        {
            bgfx::destroy( uniformPair.second );
        }
    }

    void Uniforms::createUniform(const char* name, bgfx::UniformType::Enum type)
    {
        m_map[name] = bgfx::createUniform( name, type );
    }

    void Uniforms::set(const char* name, float value)
    {
        m_values[name].valueVec4 = value;
    }

    void Uniforms::set(const char* name, vec2 value)
    {
        m_values[name].valueVec4 = vec4( value, 0, 0 );
    }

    void Uniforms::set(const char* name, vec3 value)
    {
        m_values[name].valueVec4 = vec4( value, 0 );
    }

    void Uniforms::set(const char* name, vec4 value)
    {
        m_values[name].valueVec4 = value;
    }

    void Uniforms::set(const char* name, color4f value)
    {
        m_values[name].valueVec4 = vec4( value.r, value.g, value.b, value.a );
    }

    void Uniforms::set(const char* name, mat4 value)
    {
        m_values[name].valueMat4 = value;
    }

    void Uniforms::set(const char* name, int value)
    {
        m_values[name].valueSampler = value;
    }

    void Uniforms::setUniforms() const
    {
        for( auto& pair : m_map )
        {
            // If the uniform isn't set, skip it.
            if( m_values.find(pair.first) == m_values.end() )
                continue;

            bgfx::UniformHandle handle = pair.second;
            UniformValue value = m_values.at( pair.first );
            bgfx::UniformInfo info;
            bgfx::getUniformInfo( handle, info );

            if( info.type == bgfx::UniformType::Vec4 )
                bgfx::setUniform( handle, &value.valueVec4, 1 );
            if( info.type == bgfx::UniformType::Mat4 )
                bgfx::setUniform( handle, &value.valueMat4.m11, 1 );
            if (info.type == bgfx::UniformType::Sampler)
                bgfx::setUniform( handle, &value.valueSampler, 1 );
        }
    }

} // namespace fw
