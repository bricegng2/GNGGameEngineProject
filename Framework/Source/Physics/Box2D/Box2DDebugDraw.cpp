#include "Box2DDebugDraw.h"
#include "Math/Matrix.h"
#include "Resources/Material.h"
#include "Resources/ShaderProgram.h"
#include "Utility/Uniforms.h"

namespace fw
{
    bgfx::VertexLayout MyDebugDraw::VertexFormat::format;

    void MyDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
    }

    void MyDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        VertexFormat verts[4];
        for( int i=0; i<4; i++ )
        {
            verts[i].pos.set( vertices[i].x, vertices[i].y, 0 );
            verts[i].color[0] = (uint8)(color.r * 255);
            verts[i].color[1] = (uint8)(color.g * 255);
            verts[i].color[2] = (uint8)(color.b * 255);
            verts[i].color[3] = 64;//(uint8)(color.a * 255);
        }

        uint16 indices[6] =
        {
            0, 1, 2, 0, 2, 3,
        };

        drawShape( verts, indices, 4, 6 );
    }

    void MyDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
    {
    }

    void MyDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
    {
    }

    void MyDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
    }

    void MyDebugDraw::DrawTransform(const b2Transform& xf)
    {
    }

    void MyDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
    {
    }

    void MyDebugDraw::drawShape(VertexFormat* triangleVerts, uint16* triangleIndices, uint32_t numVertices, uint32_t numIndices)
    {
        bgfx::TransientVertexBuffer tvb;
        bgfx::TransientIndexBuffer tib;

        int maxVerts = bgfx::getAvailTransientVertexBuffer( numVertices, VertexFormat::format );
        int maxIndices = bgfx::getAvailTransientIndexBuffer( numIndices );
        if( (numVertices != maxVerts) || (numIndices != maxIndices) )
        {
            // Not enough space in transient buffer, quit drawing the rest...
            return;
        }

        mat4 worldMatrix;
        worldMatrix.setIdentity();
        bgfx::setUniform( m_pUniforms->getUniform("u_matWorld"), &worldMatrix );

        bgfx::allocTransientVertexBuffer( &tvb, numVertices, VertexFormat::format );
        bgfx::allocTransientIndexBuffer( &tib, numIndices );

        VertexFormat* vertData = (VertexFormat*)tvb.data;
        memcpy( vertData, triangleVerts, numIndices * sizeof(VertexFormat::format) );
        uint16* indexData = (uint16*)tib.data;
        memcpy( indexData, triangleIndices, numIndices * sizeof(uint16) );

        uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA |
            BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);

        int viewID = 1;

        bgfx::setState( state );
        bgfx::setVertexBuffer( 0, &tvb, 0, numVertices );
        bgfx::setIndexBuffer( &tib, 0, numIndices );
        bgfx::submit( viewID, m_pMaterial->getShader()->getProgram() );
    }
} // namespace fw
