uniform sampler2D textures[2];
varying vec2 frag_texcoord;

float focus;

void main()
{
	const float tap = 12.0;
	const float max = 0.001;
	float aperture;
    vec4 sum = vec4(0.0,0.0,0.0,0.0);
	float i=0.0;
    
	focus = texture2D(textures[1], vec2(0.5,0.5)).a;
	float depth = texture2D(textures[1], frag_texcoord).a;
	float delta = abs(depth - focus) * abs(depth - focus) / tap;
	delta = clamp(delta, -max, max);
    
    for(i=-tap; i < tap; i=i+1.0) {
		sum += texture2D(textures[0], frag_texcoord + vec2(i, i) * delta);
	}
    
    gl_FragColor = sum / (2.0 * tap);
	
    
}