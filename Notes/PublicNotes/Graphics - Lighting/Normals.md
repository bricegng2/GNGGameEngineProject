
For lighting calculations, we're going to need normals for each vertex.

The vertex normal is simply the direction the vertex faces.

For example:
A flat ground plane would need a normal of 0,1,0 for each vertex
A wall facing the default camera would need a normal of 0,0,-1 for each vertex

In general to do light calculations on textured objects, we'll need a vertex format with at least positions, normals and uvs.

```c++
struct VertexFormat_PosNormalUV
{
    vec3 pos;
    vec3 normal;
    vec2 uv;

    static void InitVertexLayout()
    {
        format
            .begin()
            .add( bgfx::Attrib::Position,  3, bgfx::AttribType::Float )
            .add( bgfx::Attrib::Normal,    3, bgfx::AttribType::Float )
            .add( bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float )
            .end();
    };

    static bgfx::VertexLayout format;
};
```

#### Attributes

A normal vector is a property of a vertex, a.k.a. an attribute
See [Vertex Attributes and VBOs](../Graphics%20-%20OpenGL%20Basics/Vertex%20Attributes%20and%20VBOs.md)

Attributes need to be sent to the [Vertex Shader](../Graphics%20-%20OpenGL%20Basics/Vertex%20Shader.md) for processing, normals are no different.
See [bgfx Shaders](../Graphics%20-%203D/bgfx%20Shaders.md)

#### Debugging Normals

To ensure that your vertex's normal vector is correct, it's common to output values as colors from your shader. Since only [Fragment Shaders](../Graphics%20-%20OpenGL%20Basics/Fragment%20Shaders.md) can display colors, we need to pass the attribute to the fragment shader via a varying.

Once in the fragment shader, the normal can be displayed as a color with the x-axis displayed as red, the y-axis as green and the z-axis as blue. Alpha can be set to 1.

#### World-space Normals

Normal direction vectors will be in object space by default, so regardless of the rotation of the object, the normals will continue to point in their original direction relative to the object.

i.e. the top of the cube will always have normals pointing in the direction (0,1,0) regardless of the rotation of the cube. If the cube is on it's side, we'd expect the top face to be facing sideways, nor up.

This will break lighting calculations, so it's important to rotate the normals into world space.

To accomplish this, we first need to pass in a copy of the world matrix without translation or scale. Then in the vertex shader, transform the normal vector by this matrix. The matrix itself will be the same for all vertices, so pass it in as a uniform.

Beware the vec3 and vec4 conversions:

```glsl
vec3 rotatedNormal = mul( u_MatWorldRotation, vec4(a_normal,0) ).xyz;
```

