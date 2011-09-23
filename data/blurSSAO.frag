uniform sampler2D textures[4];

varying vec2 frag_texcoord;

float screenWidth = 1280.0;
float screenHeight = 720.0;

void main( void )
{
	float	Weights[9];
	vec2	Coord[9];
	
	float fBiasX = 1.0/screenWidth;
	float fBiasY = 1.0/screenHeight;
	Coord[0].x = -fBiasX;
	Coord[0].y = -fBiasY;
	Coord[1].x = 0.0;
	Coord[1].y = -fBiasY;
	Coord[2].x = fBiasX;
	Coord[2].y = -fBiasY;
	Coord[3].x = -fBiasX;
	Coord[3].y = 0.0;
	Coord[4].x = 0.0;
	Coord[4].y = 0.0;
	Coord[5].x = fBiasX;
	Coord[5].y = 0.0;
	Coord[6].x = -fBiasX;
	Coord[6].y = fBiasY;
	Coord[7].x = 0.0;
	Coord[7].y = fBiasY;
	Coord[8].x = fBiasX;
	Coord[8].y = fBiasY;
	
	Weights[0] = 0.0625;
	Weights[1] = 0.125;
	Weights[2] = 0.0625;
	Weights[3] = 0.125;
	Weights[4] = 0.25;
	Weights[5] = 0.125;
	Weights[6] = 0.0625;
	Weights[7] = 0.125;
	Weights[8] = 0.0625;
	
	float ssao = 0.0;	
	for(int i=0; i<9; i++)
		ssao += texture2D( textures[0], frag_texcoord + Coord[i] ).r * Weights[i];
	
	for(int i=0; i<9; i++)
		ssao += texture2D( textures[0], frag_texcoord + Coord[i]*2.0 ).r * Weights[i];
	
    vec3 color = texture2D( textures[1], frag_texcoord).rgb;
    
	gl_FragColor =vec4(color, ssao*0.5);
}
