#version 110

uniform mat4 v_matrix, p_matrix, m_matrix;
uniform sampler2D textures[5];

attribute vec3 position;
attribute vec2 texcoord;

varying vec4 frag_position;
varying vec2 frag_texcoord;

varying mat4 mv_matrix;

void main()
{    
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);

    vec4 worldPosition = m_matrix * vec4(position, 1.0);
    
    frag_texcoord = texcoord;
    frag_position = p_matrix * v_matrix * worldPosition;
}
