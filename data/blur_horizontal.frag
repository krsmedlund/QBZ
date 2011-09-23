uniform sampler2D textures[1];
varying vec2 frag_texcoord;

const float blurSize = 1.0 / 250.0; 
 
void main(void)
{
   vec4 sum = vec4(0.0);
 
   sum += texture2D(textures[0], vec2(frag_texcoord.x - 4.0 * blurSize, frag_texcoord.y)) * 0.15;
   sum += texture2D(textures[0], vec2(frag_texcoord.x - 3.0 * blurSize, frag_texcoord.y)) * 0.19;
   sum += texture2D(textures[0], vec2(frag_texcoord.x - 2.0 * blurSize, frag_texcoord.y)) * 0.22;
   sum += texture2D(textures[0], vec2(frag_texcoord.x - blurSize, frag_texcoord.y)) * 0.25;
   
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y)) * 0.16;
   
   sum += texture2D(textures[0], vec2(frag_texcoord.x + blurSize, frag_texcoord.y)) * 0.25;
   sum += texture2D(textures[0], vec2(frag_texcoord.x + 2.0 * blurSize, frag_texcoord.y)) * 0.22;
   sum += texture2D(textures[0], vec2(frag_texcoord.x + 3.0 * blurSize, frag_texcoord.y)) * 0.19;
   sum += texture2D(textures[0], vec2(frag_texcoord.x + 4.0 * blurSize, frag_texcoord.y)) * 0.15;
 
    gl_FragColor = mix(
					sum,
					texture2D(textures[0], frag_texcoord.xy),
					0.0
                       ) * 1.2;
}
