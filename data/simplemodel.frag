#version 110

uniform sampler2D textures[1];

varying vec3 frag_position, frag_normal;
varying vec2 frag_texcoord;

const vec4 light_diffuse = vec4(0.9, 0.8, 0.9, 1.0);
const vec4 light_ambient = vec4(0.6, 0.6, 0.6, 1.0);
const vec4 light_specular = vec4(0.9 , 0.9, 0.9, 1.0);


void main() {
    
    vec4 frag_texel = texture2D(textures[0], frag_texcoord.st);
    
    //ambient light
    vec4 ambient_color = light_ambient * frag_texel;
    
    // diffuse light
    //float diffuse_intensity = max((dot(light_direction, frag_normal)), 0.0);
    //vec4 diffuse_color = light_diffuse * frag_texel * diffuse_intensity;
    
    // set final color
    gl_FragColor = ambient_color; // + diffuse_color + specular_color + env_color;    
}



