#version 110

uniform mat4 p_matrix, m_matrix, v_matrix;
attribute vec3 position, normal;
attribute vec2 texcoord;

varying mat4 mv_matrix;

void main() {
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
}
