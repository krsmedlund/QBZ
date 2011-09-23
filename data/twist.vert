#version 110

uniform mat4 p_matrix;
uniform mat4 m_matrix;
uniform mat4 v_matrix;

uniform float timer;
uniform sampler2D textures[4];

attribute vec3 position;
attribute vec2 texcoord;
attribute vec3 normal;
attribute vec3 color;

varying float timestep;
varying vec3 frag_position;
varying vec2 frag_texcoord;
varying vec3 frag_normal;
varying vec3 frag_color;


vec3 twist_y(vec3 in_pos, float theta) {
	float ct = cos(theta);
	float st = sin(theta);
	vec3 out_pos;
	out_pos.x = in_pos.x * ct - in_pos.z * st;
	out_pos.z = in_pos.x * st + in_pos.z * ct;
	out_pos.y = in_pos.y;
	return out_pos;
}

vec3 twist_x(vec3 in_pos, float theta) {
	float ct = cos(theta);
	float st = sin(theta);
	vec3 out_pos;
	out_pos.y = in_pos.y * ct - in_pos.z * st;
	out_pos.z = in_pos.y * st + in_pos.z * ct;
	out_pos.x = in_pos.x;	
	return out_pos;
}

mat4 scale(float x, float y, float z)
{
    return mat4(
        vec4(x, 0.0, 0.0, 0.0),
        vec4(0.0, y, 0.0, 0.0),
        vec4(0.0, 0.0, z, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

mat4 translate(float x, float y, float z)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(x, y, z, 1.0)
    );
}

mat4 rotate_x(float theta)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, cos(timer), sin(timer), 0.0),
        vec4(0.0, -sin(timer), cos(timer), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

void main()
{
	mat4 mv_matrix = v_matrix * m_matrix;
	mat4 m_trans = rotate_x(timer) * scale(4.0/3.0, 1.0, 1.0);
	
	float twist_angle = position.x / 1.0 * ((0.0 * sin(timer)) * 3.14 / 180.0);
	vec3 twisted_pos = twist_x(position, twist_angle);
	twisted_pos = twist_y(twisted_pos, twist_angle);
	vec3 twisted_norm = twist_x(normal, twist_angle);
	twisted_norm = twist_y(normal, twist_angle);
	frag_normal   = (mv_matrix * m_trans * vec4(twisted_norm, 0.0)).xyz;
	gl_Position = p_matrix * mv_matrix * m_trans * vec4(position.xyz, 1.0);		
	
	timestep = timer;
    frag_texcoord = texcoord;
	frag_position = position;
	//frag_normal = normal;
	frag_color = color;
}
