
```c++
float GetHeightAtXZ(float x, float z)
{
    float height = 0;

    // Convert x,z to heightmap space.
    x += m_Size.x / 2;
    z += m_Size.y / 2;

    // Convert x,z to heightmap indices.
    float xPercent = x / m_Size.x;
    float zPercent = z / m_Size.y;
    int xIndex = (int)(xPercent * (m_VertCount.x - 1));
    int zIndex = (int)(zPercent * (m_VertCount.y - 1));

    // Get the 4 vertices that make up the quad.
    int stride = m_VertCount.x;
    int index = zIndex * stride + xIndex;
    vec3 bottomLeft = m_pVerts[index].pos;
    vec3 bottomRight = m_pVerts[index + 1].pos;
    vec3 topLeft = m_pVerts[index + stride].pos;
    vec3 topRight = m_pVerts[index + stride + 1].pos;

    // Get the x,z percent within the quad.
    float xPercentInQuad = xPercent * (m_VertCount.x - 1) - xIndex;
    float zPercentInQuad = zPercent * (m_VertCount.y - 1) - zIndex;

    // Get the height at x,z.
    vec3 p1, p2, p3;
    if( xPercentInQuad < zPercentInQuad )
    {
        // Top left triangle.
        p1 = vec3( 0, bottomLeft.y, 0 );
        p2 = vec3( 0, topLeft.y, 1 );
        p3 = vec3( 1, topRight.y, 1 );
    }
    else
    {
        // Bottom right triangle.
        p1 = vec3( 0, bottomLeft.y, 0 );
        p2 = vec3( 1, topRight.y, 1 );
        p3 = vec3( 1, bottomRight.y, 0 );
    }

    // Barycentric interpolation.
    {
        vec2 p0 = vec2( xPercentInQuad, zPercentInQuad );

        // Calculate Vectors.
        vec2 p10 = p0 - p1.XZ();
        vec2 p12 = p2.XZ() - p1.XZ();
        vec2 p13 = p3.XZ() - p1.XZ();

        // Cross products.
        float a123 = (p12.x*p13.y - p12.y*p13.x);
        float a3 = (p12.x*p10.y - p12.y*p10.x);
        float a2 = (p10.x*p13.y - p10.y*p13.x);

		// Weights.
        float w3 = a3 / a123;
        float w2 = a2 / a123;
        float w1 = 1.0f - w2 - w3;
        
        // Apply weights.
        height = (w1 * p1.y) + (w2 * p2.y) + (w3 * p3.y);
    }

    //float divisor = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    //float w1 = ( (p2.z - p3.z) * (xPercentInQuad - p3.x) + (p3.x - p2.x) * (zPercentInQuad - p3.z) ) / divisor;
    //float w2 = ( (p3.z - p1.z) * (xPercentInQuad - p3.x) + (p1.x - p3.x) * (zPercentInQuad - p3.z) ) / divisor;
    //float w3 = 1.0f - w1 - w2;
    //height = (w1 * p1.y) + (w2 * p2.y) + (w3 * p3.y);

    return height;
}
```
