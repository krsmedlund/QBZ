uniform sampler2D textures[1];
uniform float channel;
varying vec2 frag_texcoord;
 
void main(void)
{
    
    vec4 real_color = texture2D(textures[0], frag_texcoord);
    vec2 sin_texcoord = frag_texcoord;
    if (channel != 0.0) {
        float x_offset = sin(frag_texcoord.y*(400.0*channel))/(5000.0*channel);
        float y_offset = sin(frag_texcoord.x*(400.0*channel))/(5000.0*channel);
        sin_texcoord = vec2(frag_texcoord.x + x_offset, frag_texcoord.y + y_offset);
    }
    
    float r = texture2D(textures[0], vec2(sin_texcoord.x, clamp(sin_texcoord.y-channel, 0.0, 1.0))).r;
    float b = texture2D(textures[0], vec2(sin_texcoord.x, clamp(sin_texcoord.y-channel, 0.0, 1.0))).b;
    
    float g = texture2D(textures[0], vec2(sin_texcoord.x, sin_texcoord.y)).g;
    float r2 = texture2D(textures[0], vec2(sin_texcoord.x, sin_texcoord.y)).r;
    
    float b2 = texture2D(textures[0], vec2(sin_texcoord.x, clamp(sin_texcoord.y+channel, 0.0, 1.0))).b;
    float g2 = texture2D(textures[0], vec2(sin_texcoord.x, clamp(sin_texcoord.y+channel, 0.0, 1.0))).g;
    
    gl_FragColor = mix(
                      vec4(
                       clamp(r+r2, 0.0, 1.0),
                       clamp(g+g2, 0.0, 1.0),
                       clamp(b+b2, 0.0, 1.0),
                       1.0),
                      real_color,
                      0.9 - channel*50.0);
}