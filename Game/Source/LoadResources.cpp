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
    //test
    // Create some meshes.
    pResources->add<fw::Mesh>( "Triangle", createTriangleMesh() );
    pResources->add<fw::Mesh>( "Square", createSquareMesh() );
    pResources->add<fw::Mesh>( "Sprite", createSpriteMesh() );
    pResources->add<fw::Mesh>( "D6", createD6Mesh( 5, 10, 5 ) );
    pResources->add<fw::Mesh>( "Cube", createD6Mesh( 1, 1, 1 ) );
    pResources->add<fw::Mesh>("Plane", createPlaneMesh(ivec2(100, 100), vec2(100.0f, 100.0f), 8));
    pResources->add<fw::Mesh>("Obj", createObj("Data/HealthBoost.obj"));
    pResources->add<fw::Mesh>("Tree", createObj("Data/Tree.obj"));
    pResources->add<fw::Mesh>("HeightMap", createHeightMap("Data/Textures/HeightMap256x256.png", 10.0f, vec2(50.0f, 50.0f), 8));

    // Load some shaders.
    pResources->add<fw::ShaderProgram>( "SolidColor", new fw::ShaderProgram( "Data/Shaders/", "SolidColor.vert.bin", "SolidColor.frag.bin" ) );
    pResources->add<fw::ShaderProgram>( "VertexColor", new fw::ShaderProgram( "Data/Shaders/", "VertexColor.vert.bin", "VertexColor.frag.bin" ) );
    pResources->add<fw::ShaderProgram>( "Texture", new fw::ShaderProgram( "Data/Shaders/", "Texture.vert.bin", "Texture.frag.bin" ) );
    pResources->add<fw::ShaderProgram>("Water", new fw::ShaderProgram("Data/Shaders/", "Water.vert.bin", "Water.frag.bin"));
    pResources->add<fw::ShaderProgram>("ColorNormals", new fw::ShaderProgram("Data/Shaders/", "ColorNormals.vert.bin", "ColorNormals.frag.bin"));
    pResources->add<fw::ShaderProgram>("Lighting", new fw::ShaderProgram("Data/Shaders/", "Lighting.vert.bin", "Lighting.frag.bin"));

    // Load some textures.
    pResources->add<fw::Texture>( "MegaMan", new fw::Texture( "Data/Textures/MegaMan.png" ) );
    pResources->add<fw::Texture>("JermaEyes", new fw::Texture("Data/Textures/jermawtf.png"));
    pResources->add<fw::Texture>("Water", new fw::Texture("Data/Textures/Water.png"));
    pResources->add<fw::Texture>("BottleTexture", new fw::Texture("Data/Textures/Lower_Half_Texture.png"));
    pResources->add<fw::Texture>("HeightMapTexture", new fw::Texture("Data/Textures/HeightMap32x32.png"));
    pResources->add<fw::Texture>("Sand", new fw::Texture("Data/Textures/Sand.png"));
    pResources->add<fw::Texture>("Tree", new fw::Texture("Data/Textures/Tree.png"));

    // Create some materials.
    pResources->add<fw::Material>( "Red", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::red(), false ) );
    pResources->add<fw::Material>( "Blue", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::blue(), false ) );
    pResources->add<fw::Material>( "Green", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::green(), false ) );
    pResources->add<fw::Material>( "VertexColor", new fw::Material( getShader("VertexColor"), nullptr, fw::color4f::white(), false ) );
    pResources->add<fw::Material>( "MegaMan", new fw::Material( getShader("Texture"), getTexture("MegaMan"), fw::color4f::white(), true ) );
    pResources->add<fw::Material>("JermaEyes", new fw::Material(getShader("Texture"), getTexture("JermaEyes"), fw::color4f::white(), true));
    pResources->add<fw::Material>("Water", new fw::Material(getShader("Water"), getTexture("Water"), fw::color4f::white(), true));
    pResources->add<fw::Material>("Bottle", new fw::Material(getShader("Lighting"), getTexture("BottleTexture"), fw::color4f::white(), true));
    pResources->add<fw::Material>("HeightMapTexture", new fw::Material(getShader("Texture"), getTexture("HeightMapTexture"), fw::color4f::white(), true));
    pResources->add<fw::Material>("Sand", new fw::Material(getShader("Texture"), getTexture("Sand"), fw::color4f::white(), true));
    pResources->add<fw::Material>("Tree", new fw::Material(getShader("Texture"), getTexture("Tree"), fw::color4f::white(), true));
    pResources->add<fw::Material>("ColorNormals", new fw::Material(getShader("ColorNormals"), getTexture("Tree"), fw::color4f::white(), true));
    pResources->add<fw::Material>("IslandLighting", new fw::Material(getShader("Lighting"), getTexture("Sand"), fw::color4f::white(), true));
    pResources->add<fw::Material>("TreeLighting", new fw::Material(getShader("Lighting"), getTexture("Tree"), fw::color4f::white(), true));

}
