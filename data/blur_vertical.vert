#version 110
uniform float channel;
uniform sampler2D textures[1];

attribute vec3 position;
attribute vec2 texcoord;

varying vec2 frag_texcoord;

void main()
{
    gl_Position = vec4(position.xyz, 1.0);
    frag_texcoord = texcoord;
}