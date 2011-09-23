uniform sampler2D textures[1];
uniform float channel;
varying vec2 frag_texcoord;
uniform float currentTime;
 
void main(void)
{
    float amount = channel;
    float r = texture2D(textures[0], vec2(frag_texcoord.x-amount, frag_texcoord.y)).r;
    float b = texture2D(textures[0], vec2(frag_texcoord.x+amount, frag_texcoord.y)).b;
    float g = texture2D(textures[0], vec2(frag_texcoord.x, frag_texcoord.y)).g;
    vec4 twisted_fragment = vec4(r, g, b, 1.0);
    /*
    vec2 pt = -1.0 + 2.0 * frag_texcoord.xy;
    float rt = dot(pt, pt);
    if (rt > 1.0) discard;
    float ft = (1.0 - sqrt(1.0 - rt)) / rt;
    
    vec2 uv;
    uv.x = pt.x * ft + sin(amount);
    uv.y = pt.y * ft + sin(amount);
   
    vec4 fragment = texture2D(textures[0], uv.xy);
    */
    gl_FragColor = twisted_fragment;
     
}