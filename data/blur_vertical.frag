uniform sampler2D textures[1];
uniform float channel;
varying vec2 frag_texcoord;
 
const float blurSize = 1.5 / 150.0; 
 
void main(void)
{
   vec4 sum = vec4(0.0);
 
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y - blurSize)) * 0.15;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y)) * 0.16;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y + blurSize)) * 0.15;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y + 4.0*blurSize)) * 0.05;

    gl_FragColor = texture2D(textures[0], frag_texcoord.xy); /*mix(
                       sum,
                       texture2D(textures[0], frag_texcoord.xy),
                       0.5
                       );*/

}