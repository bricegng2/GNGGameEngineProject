//#pragma once
//
//#include "DataTypes.h"
//#include "Meshes/VertexFormats.h"
//
//class HeightmapComponent : public fw::RenderComponent
//{
//public:
//    HeightmapComponent(fw::GameObject* pGameObject, fw::Material* pMaterial, ivec2 vertCount, vec2 size, vec2 uvRepeat);
//    HeightmapComponent(fw::GameObject* pGameObject, fw::Material* pMaterial, const char* filename, vec2 size, vec2 uvRepeat, float heightScale);
//    virtual ~HeightmapComponent();
//
//    void CreateHeightmap(const char* filename, vec2 size, vec2 uvRepeat, float heightScale);
//    void CreateHeightmap(ivec2 vertCount, vec2 size, unsigned char* heights, vec2 uvRepeat, float heightScale);
//
//    float GetHeightAtXZ(float x, float z);
//    
//protected:
//    VertexFormat_PosUVNormal* m_pVerts = nullptr;
//    uint16* m_pIndices = nullptr;
//
//    ivec2 m_VertCount;
//    vec2 m_Size;
//};
