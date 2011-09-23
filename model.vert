#version 110

#define MAX_LIGHTS 12
uniform vec3 lightPosition[MAX_LIGHTS];
uniform vec4 lightColor[MAX_LIGHTS];
uniform int numLights;

uniform mat4 p_matrix, m_matrix, v_matrix;
uniform sampler2D textures[4];
uniform float timer;

attribute vec3 position, normal, tangent, bitangent;
attribute vec2 texcoord;
attribute float shinyness;
attribute vec4 specular;

varying mat4 mv_matrix;
varying vec3 frag_position, frag_normal, frag_tangent, frag_bitangent;
varying vec2 frag_texcoord;
varying vec3 frag_viewvector;
varying float frag_shinyness;

varying vec3 frag_light_direction[MAX_LIGHTS];
varying vec4 frag_light_color[MAX_LIGHTS];


/* env-map */
varying vec2 env_coord;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
    
    frag_position = (mv_matrix * vec4(position, 1.0)).xyz;
    frag_normal = (mv_matrix * vec4(normal, 0.0)).xyz;
    frag_tangent = (mv_matrix * vec4(tangent, 0.0)).xyz;
    frag_bitangent = (mv_matrix * vec4(bitangent, 0.0)).xyz;
        
    int i;
    for (i=0; i<numLights; ++i) {
        vec3 light_pos = lightPosition[i];
        light_pos = (v_matrix * vec4(light_pos, 1.0)).xyz;
        frag_light_direction[i] = (light_pos - frag_position.xyz);
        frag_light_direction[i].x = dot(light_direction_2, frag_tangent);
        frag_light_direction[i].y = dot(light_direction_2, frag_bitangent);
        frag_light_direction[i].z = dot(light_direction_2, frag_normal);
        frag_light_direction[i] = normalize(frag_light_direction[i]);
        frag_light_color[i] = lightColor[i];
    }
        
    vec3 viewvector = (-frag_position);
    frag_viewvector.x = dot(viewvector, frag_tangent);
    frag_viewvector.y = dot(viewvector, frag_bitangent);
    frag_viewvector.z = dot(viewvector, frag_normal);
    frag_viewvector = normalize(frag_viewvector);
    
    frag_texcoord = texcoord;
    frag_specular = specular;
    frag_shinyness = 15.0;
    
    /* envmap */

    vec3 u = gl_Position.xyz;
    vec3 n = frag_normal;
    vec3 r = (reflect(u, n));
    float m = 2.0 * sqrt(r.x*r.x + r.y*r.y + (r.z+1.0)*(r.z+1.0));
    env_coord.s = r.x/m + 0.5;
    env_coord.t = r.y/m + 0.5;
}
