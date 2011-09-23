
uniform mat4 p_matrix, m_matrix, v_matrix;
attribute vec3 position;

varying mat4 mv_matrix;
varying vec4 frag_position;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
    frag_position = p_matrix * mv_matrix * vec4(position, 1.0);
}
