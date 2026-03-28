#pragma once

class EweScene;

class MidtermBaseObject : public fw::GameObject
{
public:
    MidtermBaseObject(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);
    virtual ~MidtermBaseObject();

    virtual void init(EweScene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, fw::Mesh* pMesh, fw::Material* pMaterial);

    virtual void reset();
    virtual void addToScene(EweScene* pScene);
    virtual void removeFromScene();

    virtual void update(float deltatime);

    virtual void beginContact(MidtermBaseObject* pOtherObject, vec2 worldPosition, vec2 worldNormal);
    virtual void endContact(MidtermBaseObject* pOtherObject);
    
    b2Fixture* addPhysicsBox(vec2 size, bool dynamic, bool active, float density, bool sensor = false);
    b2Fixture* addPhysicsDentedBox(vec2 size, float indent, bool dynamic, bool active, float density, bool sensor = false);
    b2Fixture* addPhysicsCircle(float radius, bool dynamic, bool active, float density, bool sensor = false);

    void setPosition(vec3 pos);
    void setRotation(vec3 rot);

    // Getters/Setters
    EweScene* getEweScene() { return m_pEweScene; }
    void setColor(vec4 color) { m_color = color; }

    b2Body* getPhysicsBody() { return m_pPhysicsBody; }

    virtual void setInitialPosition(vec3 pos) { m_initialPosition = pos; }
    virtual void setInitialRotation(vec3 rot) { m_initialRotation = rot; }

protected:
    b2Fixture* addPhysicsShape(b2Shape* shape, bool dynamic, bool active, float density, bool sensor);

protected:
    EweScene* m_pEweScene = nullptr;

    vec3 m_initialPosition;
    vec3 m_initialRotation;

    unsigned int m_renderOrder;

    vec4 m_color;

    b2Body* m_pPhysicsBody;
};
