$input v_texcoord0, v_wsPosition

#include <bgfx_shader.sh>

uniform vec4 u_time;

SAMPLER2D( u_textureColor, 0 );

void main()
{
    vec4 color = texture2D( u_textureColor, v_texcoord0 );
    
    float saturation = clamp(v_wsPosition.y, 0, 1);
    color.rgb += vec3(0.9, 0.5, 0.8) * saturation;
    color.rgb *= vec3(0.3, 0.5, 0.8);
    //color.rgb = v_wsPosition;

    gl_FragColor = color;
}
