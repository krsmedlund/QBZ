uniform sampler2D textures[3];
varying vec2 frag_texcoord;

void main()
{
    vec4 texel = texture2D(textures[0], frag_texcoord);
    vec4 lightMap = texture2D(textures[1], frag_texcoord);
    //vec4 ssao = texture2D(textures[2], frag_texcoord);
    //float spec = lightMap.a;
    gl_FragColor = lightMap + (texel*texel.a);
}
