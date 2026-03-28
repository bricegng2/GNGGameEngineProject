//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "Meshes/Shapes.h"

#define getMesh pResources->get<fw::Mesh>
#define getShader pResources->get<fw::ShaderProgram>
#define getTexture pResources->get<fw::Texture>
#define getMaterial pResources->get<fw::Material>

void loadResources(fw::ResourceManager* pResources)
{
    // Create some meshes.
    pResources->add<fw::Mesh>( "Triangle", createTriangleMesh() );
    pResources->add<fw::Mesh>( "Square", createSquareMesh() );
    pResources->add<fw::Mesh>( "Sprite", createSpriteMesh() );
    pResources->add<fw::Mesh>( "D6", createD6Mesh( 5, 10, 5 ) );
    pResources->add<fw::Mesh>( "Cube", createD6Mesh( 1, 1, 1 ) );

    // Load some shaders.
    pResources->add<fw::ShaderProgram>( "SolidColor", new fw::ShaderProgram( "Data/Shaders/", "SolidColor.vert.bin", "SolidColor.frag.bin" ) );
    pResources->add<fw::ShaderProgram>( "VertexColor", new fw::ShaderProgram( "Data/Shaders/", "VertexColor.vert.bin", "VertexColor.frag.bin" ) );
    pResources->add<fw::ShaderProgram>( "Texture", new fw::ShaderProgram( "Data/Shaders/", "Texture.vert.bin", "Texture.frag.bin" ) );

    // Load some textures.
    pResources->add<fw::Texture>( "MegaMan", new fw::Texture( "Data/Textures/MegaMan.png" ) );

    // Create some materials.
    pResources->add<fw::Material>( "Red", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::red(), false ) );
    pResources->add<fw::Material>( "Blue", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::blue(), false ) );
    pResources->add<fw::Material>( "Green", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::green(), false ) );
    pResources->add<fw::Material>( "VertexColor", new fw::Material( getShader("VertexColor"), nullptr, fw::color4f::white(), false ) );
    pResources->add<fw::Material>( "MegaMan", new fw::Material( getShader("Texture"), getTexture("MegaMan"), fw::color4f::white(), true ) );
}
