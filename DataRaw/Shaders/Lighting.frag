$input v_normal, v_wsPosition, v_texcoord0

#include <bgfx_shader.sh>
#include "LightFuncs.h"

#define c_lightRadius 20
#define c_lightAngle 5

SAMPLER2D( u_textureColor, 0 );

uniform vec4 u_diffuseColor;
uniform vec4 u_cameraPos;
uniform vec4 u_time;

void main()
{
    //vec3 lightPos = u_cameraPos.xyz;
    
    vec3 lightPos = vec3(c_lightRadius + (sin(2 * u_time.x) * c_lightAngle), 10, c_lightRadius + (cos(2 * u_time.x) * c_lightAngle)) + vec3(5,3,12.5);

    vec3 cameraPos = u_cameraPos.xyz;

    vec4 textureColor = texture2D( u_textureColor, v_texcoord0 );

    vec3 material = textureColor.xyz;
    vec3 lightColor = vec3(1, 1, 1);

    vec3 ambient = material * lightColor * 0.2;
    
    vec3 dirToLight = normalize(lightPos - v_wsPosition);
    float diffusePerc = dot(v_normal, dirToLight);

    vec3 dirToCamera = normalize(cameraPos - v_wsPosition);
    vec3 halfVector = normalize(dirToLight + dirToCamera);

    float specularPerc = max( 0, dot(halfVector, v_normal) );
    specularPerc = pow( specularPerc, 50 );

    float distanceFromLight = length( lightPos - v_wsPosition );
    float lightRange = 100;
    float falloff = max(0, 1 - distanceFromLight / lightRange);
    falloff = pow( falloff, 5 );

    vec3 diffusedColor = material * lightColor * diffusePerc;
    vec3 specularColor = lightColor * specularPerc;

    vec3 color = ambient + (diffusedColor + specularColor) * falloff;

    gl_FragColor = vec4(color, 1.0);
}