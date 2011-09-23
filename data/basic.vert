#version 110

uniform mat4 p_matrix, m_matrix, v_matrix;
uniform sampler2D textures[4];

attribute vec3 position, normal, tangent, bitangent;
attribute vec2 texcoord;

varying mat4 mv_matrix;
varying vec3 frag_position, frag_normal, frag_tangent, frag_bitangent;
varying vec2 frag_texcoord;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
    
    frag_position = (mv_matrix * vec4(position, 1.0)).xyz;
    frag_normal = (mv_matrix * vec4(normal, 0.0)).xyz;
    frag_tangent = (mv_matrix * vec4(tangent, 0.0)).xyz;
    frag_bitangent = (mv_matrix * vec4(bitangent, 0.0)).xyz;
    
    frag_texcoord = texcoord;

}
