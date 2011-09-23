uniform sampler2D textures[3];

varying vec4 frag_position;
varying vec4 frag_normal;
varying vec2 frag_texcoord;
varying mat4 TBN;

void main( void )
{
    gl_FragData[0] = texture2D(textures[0], frag_texcoord.st);
    gl_FragData[0].a = 1.0;
    gl_FragData[1] = vec4(frag_position.xyz,1);
    gl_FragData[1].a = 1.0;
    //gl_FragData[2] = (texture2D(textures[1], frag_texcoord.st) * 2.0 - vec4(1.0, 1.0, 1.0, 0.0)) * TBN;
    gl_FragData[2] = vec4(frag_normal.xyz, 1);
   
}