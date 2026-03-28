#pragma once

class Box2DManager;
class Game;
class NetworkManager;
class VirtualGamepad;

class SceneMarioKart : public fw::Scene
{
public:
    SceneMarioKart(Game* pGame, fw::ResourceManager* pResources);
    virtual ~SceneMarioKart();

    virtual void loadContent();

    virtual void startFrame(float deltaTime) override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;

    void addGameObject(fw::GameObject* pObject);
    bool removeGameObject(fw::GameObject* pObject);
    bool isGameObjectInScene(fw::GameObject* pObject);
    fw::GameObject* getGameObjectByName(std::string name);

    Box2DManager* getBox2DManager() { return m_pBox2DManager; }
    VirtualGamepad* getController() { return m_pController; }

protected:
    std::vector<fw::GameObject*> m_objects;

    NetworkManager* m_pNetworkManager = nullptr;
    fw::ResourceManager* m_pResources = nullptr;
    Box2DManager* m_pBox2DManager = nullptr;
    VirtualGamepad* m_pController = nullptr;

    fw::Camera* m_pCamera = nullptr;
};
