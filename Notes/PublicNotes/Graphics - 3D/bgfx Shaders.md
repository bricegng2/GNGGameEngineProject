
Shaders in BGFX are a bit different to raw GLSL shaders, but very similar.

#### Debugging

The way the project is set up, shaders are compiled when you run. If there are errors in your shader code, this will often pop up a window with info.

Sometimes, you won't get a pop-up, but will instead get a crash, check the call-stack and the output window to see if you can work out what the issue is.

## Differences from GLSL

#### Attributes

In GLSL, names are arbitrary, so you can choose anything.

```glsl
In "vert" files:
	attribute vec3 a_Position
```

In bgfx, there are more restrictions, position must be called "a_position".

```
In the "varying.def.sc" file:
	vec3 a_position : POSITION;

In "vert" files:
	$input a_position
```

#### Uniforms

Uniforms work the same in shader code, with one exception. There are no `float`, `vec2`, or `vec3` uniform types. Make them `vec4` or `mat4`.

```
uniform vec4 u_Time;
uniform mat4 u_MatWorld;
```

#### Transforming Vectors by Matrices

In GLSL:

```glsl
// This is not a complete shader, just an example.

attribute vec3 a_Position;
uniform mat4 u_MatWorld;

void main()
{
	vec4 result = u_MatWorld * vec4(a_Position, 1);
}
```

In BGFX:

```bgfx shader language
// This is not a complete shader, just an example.

$input a_position;
uniform mat4 u_MatWorld;

void main()
{
	vec4 result = mul( u_MatWorld, vec4(a_position, 1) );
}
```

#### Varyings

Varyings are defined in the `varying.def.sc` file.

Each new varyings needs a "Semantic". This is required for hlsl shaders and since bgfx shaders can be translated into hlsl, they're required here as well.

From the hlsl docs: "A semantic is a string attached to a shader input or output that conveys information about the intended use of a parameter. Semantics are required on all variables passed between shader stages."

```varying.def.sc
vec4 v_color0    : COLOR0    = vec4(0.0, 0.0, 0.0, 1.0);
vec2 v_texcoord0 : TEXCOORD0 = vec2(0.0, 0.0);
```

Usually the semantic can be matched to the data being passed, but sometimes there's no appropriate semantic. Since this is just data being passed, we can just use any of them. For example:

```varying.def.sc
vec3 v_worldSpacePosition : TEXCOORD1 = vec3(0.0, 0.0, 0.0);
```

Here's a full example from the bgfx samples (41-tess)

```varying.def.sc
vec2 v_texcoord0 : TEXCOORD0 = vec2(0.0, 0.0);
vec3 v_position  : TEXCOORD1 = vec3(0.0, 0.0, 0.0);
vec3 v_view      : TEXCOORD2 = vec3(0.0, 0.0, 0.0);
vec3 v_normal    : NORMAL    = vec3(0.0, 0.0, 1.0);
vec3 v_tangent   : TANGENT   = vec3(1.0, 0.0, 0.0);
vec3 v_bitangent : BINORMAL  = vec3(0.0, 1.0, 0.0);
vec4 v_color0    : COLOR     = vec4(1.0, 0.0, 0.0, 1.0);

vec3 a_position  : POSITION;
vec4 a_normal    : NORMAL;
vec4 a_tangent   : TANGENT;
vec2 a_texcoord0 : TEXCOORD0;
vec4 a_color0    : COLOR0;
```