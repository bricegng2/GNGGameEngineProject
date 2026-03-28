#pragma once

#include "../Libraries/box2d/include/box2d/box2d.h"
#include "Math/Vector.h"
#include "bgfx/bgfx.h"

namespace fw
{
    class Material;
    class Uniforms;

    class MyDebugDraw : public b2Draw
    {
    public:
        struct VertexFormat
        {
            vec3 pos;
            uint8 color[4];

            static void initVertexLayout()
            {
                format
                    .begin()
                    .add( bgfx::Attrib::Position, 3, bgfx::AttribType::Float )
                    .add( bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true )
                    .end();
            };

            static bgfx::VertexLayout format;
        };

    public:
        Material* m_pMaterial = nullptr;
        Uniforms* m_pUniforms = nullptr;

        virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
        virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
        virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
        virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
        virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
        virtual void DrawTransform(const b2Transform& xf) override;
        virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

        void drawShape(VertexFormat* triangleVerts, uint16* triangleIndices, uint32_t numVertices, uint32_t numIndices);
    };
} // namespace fw
