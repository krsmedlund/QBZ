#version 110

#define MAX_LIGHTS 3
uniform vec3 lightPosition[MAX_LIGHTS];
uniform vec4 lightColor[MAX_LIGHTS];

uniform mat4 p_matrix, m_matrix, v_matrix;
uniform sampler2D textures[4];
uniform float timer;
uniform float numLights;

attribute vec3 position, normal, tangent, bitangent;
attribute vec2 texcoord;
attribute float shinyness;
//attribute vec4 specular;

varying mat4 mv_matrix;
varying vec3 frag_position, frag_normal, frag_tangent, frag_bitangent;
varying vec2 frag_texcoord;
varying float frag_shinyness;
//varying vec4 frag_specular;
varying vec3 frag_light_direction;
varying vec3 frag_light_direction_2;
varying vec3 frag_viewvector;

varying vec4 frag_diffuse_color;
varying vec4 frag_specular_color;

/* env-map */
varying vec2 env_coord;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
}
