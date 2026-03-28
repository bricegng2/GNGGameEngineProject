$input a_position, a_color0
$output v_color0

#include <bgfx_shader.sh>

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;

void main()
{
    vec4 objectSpacePosition = vec4( a_position, 1 );
    vec4 worldSpacePosition = mul( u_matWorld, objectSpacePosition );
    vec4 viewSpacePosition = mul( u_matView, worldSpacePosition );
    vec4 clipSpacePosition = mul( u_matProj, viewSpacePosition );

    gl_Position = clipSpacePosition;

    v_color0 = a_color0;
}
