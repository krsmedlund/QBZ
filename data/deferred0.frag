uniform sampler2D textures[3];

varying vec4 frag_position, frag_tangent;
varying vec4 frag_normal;
varying vec2 frag_texcoord;
varying mat4 TBN;

void main( void )
{
    /* color 3f */
    gl_FragData[0] = texture2D(textures[0], frag_texcoord.st);

    /* SSAO 1f */
    gl_FragData[0].a = 0.0; 
    
    /* position 3f */
    gl_FragData[1] = vec4(frag_position.xyz, 0.0);
    
    /* depth 1f */
    gl_FragData[1].a = frag_tangent.w / frag_tangent.z;

    /* normal 3f */
    //gl_FragData[2] = (texture2D(textures[1], frag_texcoord.st) * 2.0 - vec4(1.0, 1.0, 1.0, 0.0)) * TBN;
    gl_FragData[2] = vec4(frag_normal.xyz, 0.0);
    
    /* spec-map 1f */
    gl_FragData[2].a = texture2D(textures[2], frag_texcoord.st).r;
    
}
