uniform mat4 p_matrix;
uniform mat4 m_matrix;
uniform mat4 v_matrix;

uniform sampler2D textures[4];
varying vec2 frag_texcoord;

void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
