//#include "Framework.h"
//#include "HeightmapComponent.h"
//#include "Meshes/VertexFormats.h"
//
//#include "stb/stb_image.h"
//
//HeightmapComponent::HeightmapComponent(fw::GameObject* pGameObject, fw::Material* pMaterial, ivec2 vertCount, vec2 size, vec2 uvRepeat)
//    : fw::RenderComponent( pGameObject, nullptr, pMaterial )
//{
//    CreateHeightmap( vertCount, size, nullptr, uvRepeat, 1 );
//}
//
//HeightmapComponent::HeightmapComponent(fw::GameObject* pGameObject, fw::Material* pMaterial, const char* filename, vec2 size, vec2 uvRepeat, float heightScale)
//    : fw::RenderComponent( pGameObject, nullptr, pMaterial )
//{
//    CreateHeightmap( filename, size, uvRepeat, heightScale );
//}
//
//HeightmapComponent::~HeightmapComponent()
//{
//    delete[] m_pVerts;
//    delete[] m_pIndices;
//    delete m_pMesh;
//}
//
//void HeightmapComponent::CreateHeightmap(const char* filename, vec2 size, vec2 uvRepeat, float heightScale)
//{
//    // Load the file contents.
//    uint32 length;
//    char* fileContents = fw::LoadCompleteFile( filename, &length );
//
//    // Have stb_image decompress png from memory into a raw color array.
//    int width;
//    int height;
//    int channels;
//    stbi_set_flip_vertically_on_load( true );
//    unsigned char* pixels = stbi_load_from_memory( (unsigned char*)fileContents, length, &width, &height, &channels, 1 );
//    assert( pixels != nullptr );
//
//    // Create the texture.
//    ivec2 vertCount( width, height );    
//    CreateHeightmap( vertCount, size, pixels, uvRepeat, heightScale );
//
//    delete[] fileContents;
//    stbi_image_free( pixels );
//}
//
//void HeightmapComponent::CreateHeightmap(ivec2 vertCount, vec2 size, unsigned char* pHeights, vec2 uvRepeat, float heightScale)
//{
//    int stride = vertCount.x;
//
//    m_VertCount = vertCount;
//    m_Size = size;
//    
//    // Create array of vertices.
//    int numVerts = vertCount.x * vertCount.y;
//    m_pVerts = new VertexFormat_PosUVNormal[numVerts];
//    
//    // Create vertices
//    float xStep = size.x / (vertCount.x-1);
//    float yStep = size.y / (vertCount.y-1);
//    float xStart = -size.x / 2;
//    float yStart = -size.y / 2;
//    for( int y = 0; y < vertCount.y; y++ )
//    {
//        for( int x = 0; x < vertCount.x; x++ )
//        {
//            int index = y*stride + x;
//
//            float height = 0;
//            
//            if( pHeights )
//            {
//                height = (pHeights[index] / 255.0f) * heightScale;
//            }
//            
//            m_pVerts[index].pos = vec3( xStart + x*xStep, height, yStart + y*yStep );
//            m_pVerts[index].uv = vec2( x/(vertCount.x-1.0f), y/(vertCount.y-1.0f) ) * uvRepeat;
//        }
//    }
//    
//    // Calculate normals.
//    for( int y=0; y<vertCount.y; y++ )
//    {
//        for( int x=0; x<vertCount.x; x++ )
//        {
//            int index = y*stride + x;
//
//            vec3 normal = vec3(0, 1, 0);
//
//            if( x > 0 && x < vertCount.x-1 && y > 0 && y < vertCount.y-1 )
//            {
//                vec3 v0 = m_pVerts[index].pos;
//                vec3 v1 = m_pVerts[index-1].pos;
//                vec3 v2 = m_pVerts[index+1].pos;
//                vec3 v3 = m_pVerts[index-stride].pos;
//                vec3 v4 = m_pVerts[index+stride].pos;
//
//                vec3 left = v1-v0;
//                vec3 right = v2-v0;
//                vec3 down = v3-v0;
//                vec3 up = v4-v0;
//
//                vec3 tr = up.Cross( right ).GetNormalized();
//                vec3 br = right.Cross( down ).GetNormalized();
//                vec3 bl = down.Cross( left ).GetNormalized();
//                vec3 tl = left.Cross( up ).GetNormalized();
//
//                normal = (tr + br + bl + tl).GetNormalized();
//                //normal.y = 0;
//            }
//
//            m_pVerts[index].normal = normal;
//        }
//    }
//
//    // Create array of indices.
//    int numIndices = (vertCount.x-1) * (vertCount.y-1) * 6;
//    m_pIndices = new uint16[numIndices];
//
//    // Create indices.
//    int index = 0;
//    for( int y = 0; y < vertCount.y-1; y++ )
//    {
//        for( int x = 0; x < vertCount.x-1; x++ )
//        {
//            int bottomLeft = y*stride + x;
//            int bottomRight = y*stride + x+1;
//            int topLeft = (y+1)*stride + x;
//            int topRight = (y+1)*stride + x+1;
//
//            m_pIndices[index++] = bottomLeft;
//            m_pIndices[index++] = topLeft;
//            m_pIndices[index++] = topRight;
//
//            m_pIndices[index++] = bottomLeft;
//            m_pIndices[index++] = topRight;
//            m_pIndices[index++] = bottomRight;
//        }
//    }
//    
//    // Create the mesh.
//    m_pMesh = new fw::Mesh( VertexFormat_PosUVNormal::format, m_pVerts, numVerts * sizeof(VertexFormat_PosUVNormal), m_pIndices, numIndices*sizeof(uint16) );
//}
//
//float HeightmapComponent::GetHeightAtXZ(float x, float z)
//{
//    float height = 0;
//    
//    // Convert x,z to heightmap space.
//    x += m_Size.x / 2;
//    z += m_Size.y / 2;
//    
//    // Convert x,z to heightmap indices.
//    float xPercent = x / m_Size.x;
//    float zPercent = z / m_Size.y;
//    int xIndex = (int)(xPercent * (m_VertCount.x - 1));
//    int zIndex = (int)(zPercent * (m_VertCount.y - 1));
//    
//    // Get the 4 vertices that make up the quad.
//    int stride = m_VertCount.x;
//    int index = zIndex * stride + xIndex;
//    vec3 bottomLeft = m_pVerts[index].pos;
//    vec3 bottomRight = m_pVerts[index + 1].pos;
//    vec3 topLeft = m_pVerts[index + stride].pos;
//    vec3 topRight = m_pVerts[index + stride + 1].pos;
//    
//    // Get the x,z percent within the quad.
//    float xPercentInQuad = xPercent * (m_VertCount.x - 1) - xIndex;
//    float zPercentInQuad = zPercent * (m_VertCount.y - 1) - zIndex;
//    
//    // Get the height at x,z.
//    vec3 p1, p2, p3;
//    if( xPercentInQuad < zPercentInQuad )
//    {
//        // Top left triangle.
//        p1 = vec3( 0, bottomLeft.y, 0 );
//        p2 = vec3( 0, topLeft.y, 1 );
//        p3 = vec3( 1, topRight.y, 1 );
//    }
//    else
//    {
//        // Bottom right triangle.
//        p1 = vec3( 0, bottomLeft.y, 0 );
//        p2 = vec3( 1, topRight.y, 1 );
//        p3 = vec3( 1, bottomRight.y, 0 );
//    }
//
//    // Barycentric interpolation.
//    float divisor = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
//    float w1 = ( (p2.z - p3.z) * (xPercentInQuad - p3.x) + (p3.x - p2.x) * (zPercentInQuad - p3.z) ) / divisor;
//    float w2 = ( (p3.z - p1.z) * (xPercentInQuad - p3.x) + (p1.x - p3.x) * (zPercentInQuad - p3.z) ) / divisor;
//    float w3 = 1.0f - w1 - w2;
//    height = (w1 * p1.y) + (w2 * p2.y) + (w3 * p3.y);
//
//    return height;
//}
