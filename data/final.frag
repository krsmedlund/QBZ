#version 110

uniform sampler2D textures[1];
uniform float currentTime;
varying vec2 frag_texcoord;

/*
void main()
{
    vec4 fragment = texture2D(textures[0], frag_texcoord);
    if (fragment.a == 0.0) discard;
    gl_FragColor = fragment;
}
*/

varying float xpos;
varying float ypos;
varying float zpos;

void main (void)
{
    float iter = 0.0;
    float max_square = 3.0;
    float square = 0.0;
    float r = 0.0;
    float i = 0.0;
    float rt = 0.0;
    float it = 0.0;
    
    vec4 fragment = texture2D(textures[0], frag_texcoord);
        while(iter < 1.0 && square < max_square)
        {
            rt = (r*r) - (i*i) + xpos;
            it = (2.0 * r * i) + ypos;
            r = rt;
            i = it;
            square = (r*r)+(i*i);
            iter += 0.005;
        } 
        gl_FragColor = mix(
                           vec4(1.0, 1.0, sin(iter*2.00), 1.0),
                           fragment, 
                           0.7
                           );
    
}