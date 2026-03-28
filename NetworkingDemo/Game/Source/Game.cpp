//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "DataTypes.h"
#include "Game.h"
#include "Events/GameEvents.h"
#include "LoadResources.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "Objects/Player.h"
#include "Objects/VirtualGamepad.h"
#include "Scenes/GameScene.h"
#include "Scenes/CubeScene.h"
#include "SceneMarioKart/SceneMarioKart.h"

Game::Game(fw::FWCore& fwCore)
    : GameCore( fwCore )
{
    // General renderer settings.
    int viewID = 0;
    bgfx::setViewClear( viewID, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0 );
    bgfx::setViewRect( viewID, 0, 0, m_FWCore.getWindowClientWidth(), m_FWCore.getWindowClientHeight() );

    // Create some manager objects.
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore, 1 );
    m_pEventManager = new fw::EventManager();
    m_pResources = new fw::ResourceManager();

    // Create uniforms.
    createUniforms();

    // Create vertex formats.
    InitVertexFormats();

    // Load Resources.
    loadResources( m_pResources );

    //m_pActiveScene = new GameScene( this );
    //m_pActiveScene = new CubeScene( this );
    m_pActiveScene = new SceneMarioKart( this, m_pResources );
}

Game::~Game()
{
    delete m_pResources;
    delete m_pUniforms;

    delete m_pEventManager;
    delete m_pImGuiManager;
}

void Game::createUniforms()
{
    m_pUniforms = new fw::Uniforms();
    m_pUniforms->createUniform( "u_matWorld", bgfx::UniformType::Mat4 );
    m_pUniforms->createUniform( "u_matView", bgfx::UniformType::Mat4 );
    m_pUniforms->createUniform( "u_matProj", bgfx::UniformType::Mat4 );

    m_pUniforms->createUniform( "u_diffuseColor", bgfx::UniformType::Vec4 );
    m_pUniforms->createUniform( "u_textureColor", bgfx::UniformType::Sampler );
    m_pUniforms->createUniform( "u_uvScale", bgfx::UniformType::Vec4 );
    m_pUniforms->createUniform( "u_uvOffset", bgfx::UniformType::Vec4 );

    m_pUniforms->createUniform( "u_time", bgfx::UniformType::Vec4 );
}

void Game::startFrame(float deltaTime)
{
    m_pImGuiManager->startFrame( deltaTime );

    m_pActiveScene->startFrame( deltaTime );

    // Dispatch events.
    m_pEventManager->dispatchAllEvents( this );
}

void Game::update(float deltaTime)
{
    m_pActiveScene->update( deltaTime );

    return;

    editor_displayResources();

    if( ImGui::Begin( "Scene Selector" ) )
    {
        if( ImGui::Button( "Game" ) )
        {
            delete m_pActiveScene;
            m_pActiveScene = new GameScene( this );
}
        if( ImGui::Button( "Cube" ) )
        {
            delete m_pActiveScene;
            m_pActiveScene = new CubeScene( this );
        }

        ImGui::End();
    }
}

void Game::draw()
{
    // Setup time uniforms.
    float time = (float)fw::getSystemTimeSinceGameStart();
    m_pUniforms->set( "u_time", time );

    m_pActiveScene->draw();

    m_pImGuiManager->endFrame();
}

void Game::onCharEvent(fw::Event* pEvent)
{
    // Pass "WM_CHAR" events to imgui to handle text input.
    if( pEvent->getType() == fw::CharEvent::getStaticEventType() )
    {
        int character = static_cast<fw::CharEvent*>(pEvent)->getValue();
        m_pImGuiManager->addInputCharacter( character );
    }
}

void Game::editor_displayResources()
{
    ImGui::Begin("Resources");

    m_pResources->editor_displayResourceLists();

    ImGui::End(); // "Resources"
}
