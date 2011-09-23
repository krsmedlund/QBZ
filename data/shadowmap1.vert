uniform mat4 p_matrix, m_matrix, v_matrix, shadowTextureMatrix;
uniform sampler2D textures[2];

attribute vec3 position;
attribute vec2 texcoord;

varying mat4 mv_matrix;
varying vec2 frag_texcoord;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = vec4(position.xy, 0.0, 1.0);
    frag_texcoord = texcoord;
}
