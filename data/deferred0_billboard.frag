uniform sampler2D textures[1];

varying vec4 frag_position;
varying vec2 frag_texcoord;
varying vec3 frag_color;

void main(void) {
    
    /* color 3f */
    gl_FragData[0]	 =  vec4(texture2D(textures[0], frag_texcoord.st));
    
    /* SSAO 1f */
    gl_FragData[0].a = 1.0;
    
    /* position 3f */
    gl_FragData[1]	 = vec4(0.0, 0.0, 0.0, 0.0);
    
    /* depth 1f */
    gl_FragData[1].a = 0.0;
    
    /* normal 3f */
    gl_FragData[2] = vec4(0.0, 0.0, 0.0, 0.0);
    
    /* specmap */
    gl_FragData[2].a = 0.0; 
}