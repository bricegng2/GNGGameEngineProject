#pragma once

#include "Framework.h"
#include "DataTypes.h"

class MidtermBaseObject;
class ShakeCameraObject;
class VirtualGamepad;

class EweScene : public fw::Scene, public fw::EventListener
{
    static const float c_InitialProjectileSpawnDelay;
    static const float c_TimeBetweenProjectileSpawns;
    static const int c_NumProjectilesInPool;
    static const int c_NumMeatChunksInPool;

public:
    EweScene(fw::GameCore* pGame, fw::ResourceManager* pResources);
    virtual ~EweScene();

    virtual void onEvent(fw::Event* pEvent) override;

    virtual void loadContent();

    virtual void reset();

    virtual void startFrame(float deltatime);
    virtual void update(float deltatime);
    virtual void draw();

    void addToScene(std::string name, MidtermBaseObject* pObject);
    void removeFromScene(MidtermBaseObject* pObject);

    MidtermBaseObject* getGameObject(std::string name);
    ShakeCameraObject* getCamera() { return m_pCamera; }

    b2World* getBox2DWorld() { return m_pBox2DWorld; }

    void spawnMeatChunks(vec3 spawnpos, unsigned int numchunks);

protected:
    std::vector<MidtermBaseObject*> m_objects;

    b2World* m_pBox2DWorld = nullptr;

    ShakeCameraObject* m_pCamera = nullptr;

    std::vector<MidtermBaseObject*> m_projectilePool;
    std::vector<MidtermBaseObject*> m_meatChunkPool;

    float m_projectileSpawnTimer;

    fw::ResourceManager* m_pResources;

    VirtualGamepad* m_pGamepad = nullptr;
};
