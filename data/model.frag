#version 110

uniform mat4 p_matrix, m_matrix;
uniform sampler2D textures[4];
uniform vec4 lightColor[12];

varying mat4 mv_matrix;

varying vec3 frag_position, frag_normal, frag_tangent;
varying vec2 frag_texcoord;
varying float frag_shinyness;
varying vec4 frag_specular;
varying vec3 frag_viewvector;

/* lights */
varying vec3 frag_light_direction, frag_light_direction_2;
varying vec4 frag_diffuse_color, frag_specular_color;

// faked
const vec4 light_ambient = vec4(0.2, 0.2, 0.2, 0.7);
varying vec2 env_coord;


float warp_diffuse(float d) {
    return d * d;
}

vec2 warp_texcoord(vec2 i) {
    return vec2(i.x * cos(i.y), i.y * sin(i.x));
}

void main() {
    vec4 frag_diffuse_color_2 = lightColor[1];
    vec4 frag_specular_color_2 = lightColor[1];

    // warp coords
    //vec2 sin_coord = warp_texcoord(frag_texcoord);
    vec2 sin_coord = frag_texcoord;
    
    // load texture data
    vec4 frag_texel = vec4(texture2D(textures[0],sin_coord).rgb, 0.7);
    vec3 frag_bump = texture2D(textures[1], sin_coord).xyz * 2.0 - 1.0;
    vec4 frag_spec = texture2D(textures[2], sin_coord);
    vec4 frag_env = texture2D(textures[3], env_coord);

    
    //ambient light
    vec4 ambient_color = light_ambient * frag_texel;
    
    // diffuse light
    float diffuse_intensity = max(warp_diffuse(dot(frag_light_direction, frag_bump)), 0.0);
    vec4 diffuse_color = frag_diffuse_color * frag_texel * diffuse_intensity;
    
    float diffuse_intensity_2 = max(warp_diffuse(dot(frag_light_direction_2, frag_bump)), 0.0);
    vec4 diffuse_color_2 = frag_diffuse_color_2 * frag_texel * diffuse_intensity_2;
    
    // specular light
    vec4 specular_color = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 specular_color_2 = vec4(0.0, 0.0, 0.0, 0.0);

    vec4 env_color = vec4(0.0, 0.0, 0.0, 0.0);

    if (diffuse_intensity > 0.0) {
        float specular_intensity = max(dot(frag_bump, normalize(frag_light_direction)), 0.0);
        specular_color = frag_specular_color * frag_spec * pow(specular_intensity, frag_shinyness);
        if (frag_shinyness < 1.0) {
            specular_color = specular_color * frag_shinyness;
        }
    }
    
    if (diffuse_intensity_2 > 0.0) {
        float specular_intensity = max(dot(frag_bump, normalize(frag_light_direction_2)), 0.0);
        specular_color_2 = frag_specular_color_2 * frag_spec * pow(specular_intensity, frag_shinyness);
        if (frag_shinyness < 1.0) {
            specular_color_2 = specular_color_2 * frag_shinyness;
        }
        //env_color = frag_env * diffuse_intensity * specular_intensity * 0.4;
    }
    
    // set final color
    gl_FragColor = ambient_color + diffuse_color + diffuse_color_2 + specular_color + specular_color_2;// + env_color;    
}



