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


void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
    
    frag_position = (mv_matrix * vec4(position, 1.0)).xyz;
    frag_normal = (mv_matrix * vec4(normal, 0.0)).xyz;
    frag_tangent = (mv_matrix * vec4(tangent, 0.0)).xyz;
    frag_bitangent = (mv_matrix * vec4(bitangent, 0.0)).xyz;
    
    frag_diffuse_color = lightColor[0];
    frag_specular_color = lightColor[0];
    
    vec3 light_pos = lightPosition[0];
    light_pos = (v_matrix * vec4(lightPosition[0], 1.0)).xyz;
    vec3 light_direction = (light_pos - frag_position.xyz);
    frag_light_direction.x = dot(light_direction, frag_tangent);
    frag_light_direction.y = dot(light_direction, frag_bitangent);
    frag_light_direction.z = dot(light_direction, frag_normal);
    frag_light_direction = normalize(frag_light_direction);
    
    
    vec3 light_pos_2 = lightPosition[1];
    light_pos_2 = (v_matrix * vec4(lightPosition[1], 1.0)).xyz;
    vec3 light_direction_2 = (light_pos_2 - frag_position.xyz);
    frag_light_direction_2.x = dot(light_direction_2, frag_tangent);
    frag_light_direction_2.y = dot(light_direction_2, frag_bitangent);
    frag_light_direction_2.z = dot(light_direction_2, frag_normal);
    frag_light_direction_2 = normalize(frag_light_direction_2);
    
    vec3 viewvector = (-frag_position);
    frag_viewvector.x = dot(viewvector, frag_tangent);
    frag_viewvector.y = dot(viewvector, frag_bitangent);
    frag_viewvector.z = dot(viewvector, frag_normal);
    frag_viewvector = normalize(frag_viewvector);
    
    frag_texcoord = texcoord;
    //frag_specular = specular;
    frag_shinyness = 25.0;
    
    /* envmap */

    vec3 u = gl_Position.xyz;
    vec3 n = frag_normal;
    vec3 r = (reflect(u, n));
    float m = 2.0 * sqrt(r.x*r.x + r.y*r.y + (r.z+1.0)*(r.z+1.0));
    env_coord.s = r.x/m + 0.5;
    env_coord.t = r.y/m + 0.5;
}
