uniform sampler2D glowTexture;

varying vec4 frag_position;
varying vec2 frag_texcoord;

const float blurSize = 1.0 / 150.0; 

void main() {   
    
    vec4 sum = vec4(0.0);
    
    sum += texture2D(glowTexture, vec2(frag_texcoord.x - 4.0 * blurSize, frag_texcoord.y)) * 0.05;
    sum += texture2D(glowTexture, vec2(frag_texcoord.x - 3.0 * blurSize, frag_texcoord.y)) * 0.09;
    sum += texture2D(glowTexture, vec2(frag_texcoord.x - 2.0 * blurSize, frag_texcoord.y)) * 0.12;
    sum += texture2D(glowTexture, vec2(frag_texcoord.x - blurSize, frag_texcoord.y)) * 0.15;
    
    sum += texture2D(glowTexture, vec2(frag_texcoord.x, frag_texcoord.y)) * 0.16;
    
    sum += texture2D(glowTexture, vec2(frag_texcoord.x + blurSize, frag_texcoord.y)) * 0.15;
    sum += texture2D(glowTexture, vec2(frag_texcoord.x + 2.0 * blurSize, frag_texcoord.y)) * 0.12;
    sum += texture2D(glowTexture, vec2(frag_texcoord.x + 3.0 * blurSize, frag_texcoord.y)) * 0.09;
    sum += texture2D(glowTexture, vec2(frag_texcoord.x + 4.0 * blurSize, frag_texcoord.y)) * 0.05;
    
    gl_FragColor = mix(
                       sum,
                       texture2D(glowTexture, frag_texcoord.xy),
                       0.0
                       ) * 1.2;
}
