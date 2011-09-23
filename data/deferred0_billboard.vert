#version 110

uniform mat4 p_matrix, m_matrix, v_matrix, RotationMatrixInverse, TransformMatrixInverse;
uniform sampler2D textures[1];

attribute vec3 position, color;
attribute vec2 texcoord;

varying vec2 frag_texcoord;
varying mat4 mv_matrix;
varying vec4 frag_position, frag_tangent;
varying vec3 frag_color;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
    frag_texcoord = texcoord;

    frag_position =  m_matrix * vec4(position, 1.0);
    frag_tangent = p_matrix * mv_matrix * vec4(position, 1.0); 

    frag_color = color;
    gl_FrontColor = vec4(color, 1.0);    
}

