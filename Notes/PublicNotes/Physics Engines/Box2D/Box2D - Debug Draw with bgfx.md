Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

Drawing Box2D debug draw data with bgfx transient buffers.

Could be done more efficiently by buffering up all the vertices and drawing them once, rather than this code that draws once per shape.

##### Create and assign an instance of the b2Draw subclass

Setting the flags determines what kind of objects Box2D will try to draw, look at the source for the full list.

```c++
MyDebugDraw* pDebugDraw = new MyDebugDraw();
pDebugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_aabbBit );
pDebugDraw->m_pMaterial = pMaterial;
pDebugDraw->m_pUniforms = pUniforms;

m_pWorld->SetDebugDraw( pDebugDraw );
```

##### Create the b2Draw subclass

Each of the virtual methods would need to be overridden and are called from the Box2D source for various types of objects.

```c++
class MyDebugDraw : public b2Draw
{
public:
    bgfx::ProgramHandle m_ShaderHandle;
    fw::Uniforms* m_pUniforms;
    
    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {}
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {}    
    virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override {}
    virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override {}
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override {}
    virtual void DrawTransform(const b2Transform& xf) override {}
    virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override {}
    
    void DrawShape(VertexFormat_PosColor* triangleVerts, uint16* triangleIndices, uint32_t numVertices, uint32_t numIndices)
    {
        bgfx::TransientVertexBuffer tvb;
        bgfx::TransientIndexBuffer tib;
    
        int maxVerts = bgfx::getAvailTransientVertexBuffer( numVertices, VertexFormat_PosColor::format );
        int maxIndices = bgfx::getAvailTransientIndexBuffer( numIndices );
        if( (numVertices != maxVerts) || (numIndices != maxIndices) )
        {
            // Not enough space in transient buffer, quit drawing the rest...
            return;
        }
    
        mat4 worldMatrix;
        worldMatrix.SetIdentity();
        bgfx::setUniform( m_pUniforms->GetUniform("u_WorldMatrix"), &worldMatrix );
    
        bgfx::allocTransientVertexBuffer( &tvb, numVertices, VertexFormat_PosColor::format );
        bgfx::allocTransientIndexBuffer( &tib, numIndices );
    
        VertexFormat_PosColor* vertData = (VertexFormat_PosColor*)tvb.data;
        memcpy( vertData, triangleVerts, numIndices * sizeof(VertexFormat_PosColor::format) );
        uint16* indexData = (uint16*)tib.data;
        memcpy( indexData, triangleIndices, numIndices * sizeof(uint16) );
    
        uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA |
                         BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
    
        int viewID = 1;
        
        bgfx::setState( state );
        bgfx::setVertexBuffer( 0, &tvb, 0, numVertices );
        bgfx::setIndexBuffer( &tib, 0, numIndices );
        bgfx::submit( viewID, m_ShaderHandle );
    }
};
```
