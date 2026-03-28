$input a_position, a_texcoord0
$output v_texcoord0, v_wsPosition

#include <bgfx_shader.sh>

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProj;
uniform vec4 u_time;

void main()
{
    vec4 objectSpacePosition = vec4( a_position, 1 );
    vec4 worldSpacePosition = mul( u_matWorld, objectSpacePosition );

    float dist = distance(worldSpacePosition.xz, vec2(5,5));
    worldSpacePosition.y += sin(dist - (u_time.x)) * 0.23;
    v_wsPosition = worldSpacePosition.xyz;

    vec4 viewSpacePosition = mul( u_matView, worldSpacePosition );
    vec4 clipSpacePosition = mul( u_matProj, viewSpacePosition );
    gl_Position = clipSpacePosition;

    v_texcoord0 = a_texcoord0;
}
