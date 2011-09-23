#version 110

/*
attribute vec3 position;
attribute vec2 texcoord;

varying vec2 frag_texcoord;

void main()
{
    //frag_texcoord = texcoord;
    
}

*/

uniform sampler2D textures[1];

attribute vec3 position;
attribute vec2 texcoord;

uniform float currentTime;

float real = -2.0;
float w = 3.0;
float imag = -1.0;
float h = 2.0;

varying float xpos;
varying float ypos;

varying vec2 frag_texcoord;

void main(void)
{
    xpos = clamp(position.x, 0.0,1.0) * w + real;
    ypos = clamp(position.y, 0.0,1.0) * h + imag;
    gl_Position = vec4(position.xyz, 1.0);
    frag_texcoord = texcoord;
    
}