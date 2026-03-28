$input a_position, a_normal
$output v_normal

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

    vec3 rotatedNormal = mul( u_matWorld, vec4(a_normal, 0) ).xyz;
    v_normal = rotatedNormal;
}
