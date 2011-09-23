#version 110

uniform float timer;
uniform mat4 p_matrix;
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform sampler2D textures[4];

varying vec3 frag_position;
varying vec2 frag_texcoord;
varying vec3 frag_normal;
varying vec3 frag_color;

varying float timestep;

const vec3 light_direction = vec3(0.3, -0.9, -0.8);
const vec4 light_ambient = vec4(0.1, 0.1, 0.1, 1.0);
const vec4 light_diffuse = vec4(0.5, 0.2, 0.9, 1.0);


void main()
{
	vec4 light_diffuse = vec4(sin(timestep)-0.2,cos(timestep)-0.2,-sin(timestep)-0.2,1);
	mat4 mv_matrix = v_matrix * m_matrix;
	vec3 mv_light_direction = (mv_matrix * vec4(light_direction, 0.0)).xyz;
    vec3 normal = normalize(frag_normal);
	vec4 frag_diffuse = vec4(0.5, 0.5, 0.5, 1.0); //texture2D(textures[0], frag_texcoord);	
    vec4 diffuse_factor = max(-dot(normal, mv_light_direction), 0.0) * light_diffuse;
	vec4 ambient_diffuse_factor = diffuse_factor + light_ambient;
    
	gl_FragColor = ambient_diffuse_factor * frag_diffuse;
	//gl_FragColor = vec4(0,0,0,1); //texture2D(textures[1], frag_texcoord);
}
