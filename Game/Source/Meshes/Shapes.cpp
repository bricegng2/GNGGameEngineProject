//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "VertexFormats.h"
#include "Shapes.h"
#include <stb/stb_image.h>

//=======================
// Triangle
//=======================
static const VertexFormat_PosColor g_TriangleVerts[] =
{
    { vec2(0.0f, 0.5f), 255, 0, 0, 255 }, // Top
    { vec2(-0.5f,-0.5f), 0, 255, 0, 255 }, // Bottom-left
    { vec2(0.5f,-0.5f), 0, 0, 255, 255 }, // Bottom-right
};
static const uint16 g_TriangleIndices[] =
{
    0, 2, 1,
};
fw::Mesh* createTriangleMesh()
{
    return new fw::Mesh(VertexFormat_PosColor::format, g_TriangleVerts, sizeof(g_TriangleVerts), g_TriangleIndices, sizeof(g_TriangleIndices));
}

//=======================
// Square
//=======================
static const VertexFormat_PosColor g_SquareVerts[] =
{
    { vec2(-0.5f, 0.5f), 0, 255, 0, 255 }, // Top-left
    { vec2(-0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-left
    { vec2(0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-right

    { vec2(-0.5f, 0.5f), 0, 255, 0, 255 }, // Top-left
    { vec2(0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-right
    { vec2(0.5f, 0.5f), 0, 255, 0, 255 }, // Top-right
};
static const uint16 g_SquareIndices[] =
{
    0,2,1, 3,5,4
};
fw::Mesh* createSquareMesh()
{
    return new fw::Mesh(VertexFormat_PosColor::format, g_SquareVerts, sizeof(g_SquareVerts), g_SquareIndices, sizeof(g_SquareIndices));
}

//=======================
// Sprite
//=======================
static const VertexFormat_PosUV g_SpriteVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0,1) }, // Top-left
    { vec2(-0.5f,-0.5f), vec2(0,0) }, // Bottom-left
    { vec2(0.5f,-0.5f), vec2(1,0) }, // Bottom-right

    { vec2(-0.5f, 0.5f), vec2(0,1) }, // Top-left
    { vec2(0.5f,-0.5f), vec2(1,0) }, // Bottom-right
    { vec2(0.5f, 0.5f), vec2(1,1) }, // Top-right
};
static const uint16 g_SpriteIndices[] =
{
    0,2,1, 3,5,4
};
fw::Mesh* createSpriteMesh()
{
    return new fw::Mesh(VertexFormat_PosUV::format, g_SpriteVerts, sizeof(g_SpriteVerts), g_SpriteIndices, sizeof(g_SpriteIndices));
}

//=======================
// D6
//=======================
static const uint16 g_D6Indices[] =
{
     0, 1, 2,  0, 2, 3,
     4, 6, 5,  4, 7, 6,
     8,10, 9,  8,11,10,
    12,13,14, 12,14,15,
    16,17,18, 16,18,19,
    20,22,21, 20,23,22,
};
fw::Mesh* createD6Mesh(float width, float height, float depth)
{
    std::vector<VertexFormat_Pos3UV> m_verts =
    {
        // Front
        { {-width / 2, -height / 2, -depth / 2},   {0,0} },
        { {-width / 2,  height / 2, -depth / 2},   {0,1} },
        { { width / 2,  height / 2, -depth / 2},   {1,1} },
        { { width / 2, -height / 2, -depth / 2},   {1,0} },
        // Back
        { {-width / 2, -height / 2,  depth / 2},   {0,0} },
        { {-width / 2,  height / 2,  depth / 2},   {0,1} },
        { { width / 2,  height / 2,  depth / 2},   {1,1} },
        { { width / 2, -height / 2,  depth / 2},   {1,0} },
        // Left
        { {-width / 2, -height / 2, -depth / 2},   {0,0} },
        { {-width / 2,  height / 2, -depth / 2},   {0,1} },
        { {-width / 2,  height / 2,  depth / 2},   {1,1} },
        { {-width / 2, -height / 2,  depth / 2},   {1,0} },
        // Right
        { { width / 2, -height / 2, -depth / 2},   {0,0} },
        { { width / 2,  height / 2, -depth / 2},   {0,1} },
        { { width / 2,  height / 2,  depth / 2},   {1,1} },
        { { width / 2, -height / 2,  depth / 2},   {1,0} },
        // Top
        { {-width / 2,  height / 2, -depth / 2},   {0,0} },
        { {-width / 2,  height / 2,  depth / 2},   {0,1} },
        { { width / 2,  height / 2,  depth / 2},   {1,1} },
        { { width / 2,  height / 2, -depth / 2},   {1,0} },
        // Bottom
        { {-width / 2, -height / 2, -depth / 2},   {0,0} },
        { {-width / 2, -height / 2,  depth / 2},   {0,1} },
        { { width / 2, -height / 2,  depth / 2},   {1,1} },
        { { width / 2, -height / 2, -depth / 2},   {1,0} },
    };

    int vertBytes = sizeof(VertexFormat_Pos3UV) * (int)m_verts.size();
    return new fw::Mesh(VertexFormat_Pos3UV::format, m_verts.data(), vertBytes, g_D6Indices, sizeof(g_D6Indices));
}

//=======================
// Grid
//=======================
fw::Mesh* createPlaneMesh(ivec2 verts, vec2 worldSize, int textureReapeatRate)
{
    // Compute step sizes
    float stepX = worldSize.x / (verts.x - 1);
    float stepY = worldSize.y / (verts.y - 1);

    // Store vertices
    std::vector<VertexFormat_PosUV> vertices;
    for (int y = 0; y < verts.x; y++)
    {
        for (int x = 0; x < verts.x; x++)
        {
            vec2 pos = vec2(x * stepX, y * stepY);
            vec2 uv = vec2(float(x) / (verts.x - 1), float(y) / (verts.x - 1)) * textureReapeatRate;
            vertices.push_back({ pos, uv });
        }
    }

    // Store indices
    std::vector<uint16_t> indices;
    for (int y = 0; y < verts.x - 1; y++)
    {
        for (int x = 0; x < verts.x - 1; x++)
        {
            int bottomLeft = y * verts.x + x;
            int bottomRight = bottomLeft + 1;
            int topLeft = bottomLeft + verts.x;
            int topRight = topLeft + 1;

            // First triangle
            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(topRight);

            // Second triangle
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(bottomRight);
        }
    }

    return new fw::Mesh(VertexFormat_PosUV::format, vertices.data(), sizeof(VertexFormat_PosUV) * vertices.size(), indices.data(), indices.size() * sizeof(uint16_t));
}

//=======================
// Obj
//=======================
fw::Mesh* createObj(const char* objFileName)
{
    fw::uint32 length = 0;
    char* buffer = fw::loadCompleteFile(objFileName, &length);
    if (buffer == 0 || length == 0)
    {
        fw::outputMessage("Error: Failed to load OBJ file: %s", objFileName);
        delete[] buffer;
        return nullptr;
    }

    std::vector<vec3> vertices;             // v
    std::vector<vec2> texCoords;            // vt
    std::vector<vec3> normals;              // vn
    std::vector<VertexFormat_PosNormalUV> final; // f (Now includes normals)
    std::vector<uint16_t> indices;

    // Split the string at line endings
    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);

    // Keep looping as long as there are lines:
    while (line)
    {
        fw::outputMessage("%s\n", line); // Print for debugging

        if (line[0] == 'v')
        {
            if (line[1] == ' ') // Vertex position
            {
                vec3 v;
                sscanf_s(line, "v %f %f %f", &v.x, &v.y, &v.z);
                vertices.push_back(v);
            }
            else if (line[1] == 't') // Texture coordinate
            {
                vec2 vt;
                sscanf_s(line, "vt %f %f", &vt.x, &vt.y);
                texCoords.push_back(vt);
            }
            else if (line[1] == 'n') // Normal
            {
                vec3 vn;
                sscanf_s(line, "vn %f %f %f", &vn.x, &vn.y, &vn.z);
                normals.push_back(vn);
            }
        }
        else if (line[0] == 'f') // face 
        {
            int v[3], vt[3], vn[3];
            int result = sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &v[0], &vt[0], &vn[0],
                &v[1], &vt[1], &vn[1],
                &v[2], &vt[2], &vn[2]);

            if (result == 9) // Ensure correct parsing
            {
                for (int i = 0; i < 3; i++) // Convert 1-based to 0-based
                {
                    VertexFormat_PosNormalUV vertex;
                    vertex.pos = vertices[v[i] - 1];
                    vertex.uv = texCoords[vt[i] - 1];
                    vertex.normal = normals[vn[i] - 1]; // Now includes normal

                    final.push_back(vertex);
                    indices.push_back((uint16)final.size() - 1); // Use final size as index
                }
            }
        }
        // Go to the next line
        line = strtok_s(nullptr, "\n", &next_token);
    }

    delete[] buffer;

    int vertBytes = sizeof(VertexFormat_PosNormalUV) * (int)final.size();
    int indexBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh(VertexFormat_PosNormalUV::format, final.data(), vertBytes, indices.data(), indexBytes);

}

std::vector<vec3> pixelPositions;
fw::Mesh* createHeightMap(const char* heightfilename, float maxHeight, vec2 worldSize, int textureReapeatRate)
{
    // Load the heightmap texture
    uint32 length;
    char* fileBuffer = fw::loadCompleteFile(heightfilename, &length);
    int width;
    int height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load_from_memory((unsigned char*)fileBuffer, length, &width, &height, &channels, 1);
    if (!pixels)
    {
        fw::outputMessage("Error: Failed to load heightmap texture: %s", heightfilename);
        delete[] pixels;
        return nullptr;
    }

    float stepX = worldSize.x / (width - 1);
    float stepY = worldSize.y / (height - 1);

    // Create the vertices
    std::vector<VertexFormat_PosNormalUV> vertices;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float normalizedHeight = static_cast<float>(pixels[y * width + x]) / 255.0f;
            
            float worldHeight = normalizedHeight * maxHeight;

            vec3 pos = vec3(x * stepX, worldHeight, y * stepY);
            vec2 uv = vec2(float(x) / (width - 1), float(y) / (width - 1)) * textureReapeatRate;
            vertices.push_back({ pos, uv });
            pixelPositions.push_back(pos);
        }
    }

    // Create the indices
    std::vector<uint16_t> indices;
    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            int bottomLeft = y * width + x;
            int bottomRight = bottomLeft + 1;
            int topLeft = bottomLeft + width;
            int topRight = topLeft + 1;

            // First triangle
            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(topRight);

            // Second triangle
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(bottomRight);
        }
    }

    for (int i = 0; i < indices.size(); i += 3)
    {
        VertexFormat_PosNormalUV& v0 = vertices[indices[i]];
        VertexFormat_PosNormalUV& v1 = vertices[indices[i + 1]];
        VertexFormat_PosNormalUV& v2 = vertices[indices[i + 2]];

        vec3 edge1 = v1.pos - v0.pos;
        vec3 edge2 = v2.pos - v0.pos;
        vec3 normal = edge1.cross(edge2).normalize();

        v0.normal += normal;
        v1.normal += normal;
        v2.normal += normal;
    }

    for (auto& vertex : vertices)
    {
        vertex.normal = vertex.normal.normalize();
    }

    // Clean up the loaded image
    stbi_image_free(pixels);

    // Create the mesh
    int vertBytes = sizeof(VertexFormat_PosNormalUV) * static_cast<int>(vertices.size());
    int indexBytes = sizeof(uint16_t) * static_cast<int>(indices.size());
    return new fw::Mesh(VertexFormat_PosNormalUV::format, vertices.data(), vertBytes, indices.data(), indexBytes);
}

vec3 getHeightMapPixelPosition()
{
    float index = fw::Random::randomFloat(0.0f, pixelPositions.size());

    vec3 pixelPosition = pixelPositions[index];

    pixelPosition.y -= 0.2f; // this is here so the trees are not floating

    return pixelPosition;
}

std::vector<vec3> getHeightMapPixelPositions()
{
    //std::vector<vec3> positions;
    //
    //for (auto& pos : pixelPositions)
    //{
    //    if (pos.x >= min.x && pos.x <= max.x && pos.z >= min.y && pos.z <= max.y)
    //    {
    //        positions.push_back(pos);
    //    }
    //}
    //
    //return positions;

    return pixelPositions;
}

//=======================
// Barycentric Height Sampling
//=======================

float barycentricCoords(const vec3& p, const vec3& a, const vec3& b, const vec3& c)
{
    vec3 v0 = b - a;
    vec3 v1 = c - a;
    vec3 v2 = p - a;

    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);

    float v = (d11 * d20 - d01 * d21);
    float w = (d00 * d21 - d01 * d20);
    float u = 1.0f - v - w;

    return u * a.y + v * b.y + w * c.y;
}

float getHeightAtXZ(float x, float z)
{
    const int g_HeightmapWidth = 256;
    const int g_HeightmapHeight = 256;
    const vec2 g_HeightmapWorldSize = vec2(50, 50);

    float stepX = g_HeightmapWorldSize.x / (g_HeightmapWidth - 1);
    float stepZ = g_HeightmapWorldSize.y / (g_HeightmapHeight - 1);

    int col = (int)(x / stepX);
    int row = (int)(z / stepZ);

    fw::myClamp(col, 0, g_HeightmapWidth - 2);
    fw::myClamp(row, 0, g_HeightmapHeight - 2);

    int idx0 = row * g_HeightmapWidth + col;
    int idx1 = row * g_HeightmapWidth + (col + 1);
    int idx2 = (row + 1) * g_HeightmapWidth + col;
    int idx3 = (row + 1) * g_HeightmapWidth + (col + 1);

    vec3 p = vec3(x, 0, z);
    vec3 a, b, c;

    float fracX = (x - col * stepX) / stepX;
    float fracZ = (z - row * stepZ) / stepZ;

    if (fracX + fracZ < 1.0f)
    {
        a = pixelPositions[idx0];
        b = pixelPositions[idx1];
        c = pixelPositions[idx2];
    }
    else
    {
        a = pixelPositions[idx3];
        b = pixelPositions[idx2];
        c = pixelPositions[idx1];
    }

    return barycentricCoords(p, a, b, c) + 0.2f;
}
