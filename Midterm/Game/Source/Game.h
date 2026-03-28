//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Framework.h"
#include "DataTypes.h"

class Player;
class RemoveFromGameEvent;
class GameScene;
class VirtualGamepad;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void createUniforms();

    virtual void startFrame(float deltaTime) override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;

    fw::ResourceManager* getResources() { return m_pResources; }

protected:
    void onCharEvent(fw::Event* pEvent);

protected:
    // Editor Interface.
    fw::ImGuiManager* m_pImGuiManager = nullptr;
    void editor_displayResources();

    // Resources.
    fw::ResourceManager* m_pResources = nullptr;

    fw::Scene* m_pActiveScene = nullptr;
};
