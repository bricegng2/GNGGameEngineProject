$input v_normal

#include <bgfx_shader.sh>

uniform vec4 u_diffuseColor;

void main()
{
    vec3 color = (v_normal + 0.1);
    gl_FragColor = vec4(color, 1.0) * u_diffuseColor;
    //gl_FragColor = vec4(color.x, color.y * 0.0, color.z, 1.0);
}