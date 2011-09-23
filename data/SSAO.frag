uniform sampler2D textures[4]; 

uniform vec3 cameraPosition;
varying vec2 frag_texcoord;

float screenWidth = 1280.0;
float screenHeight = 720.0;

const float radiusFar = 310.0;
const float occlusorRadius = 10.8;
const float PI = 3.14159265358979323846264;

//-------------------------------------------------------------------------------------------------------------------------------------
// This function computes the occlusion factor of a sphere centered in C of radius r over a sphere centered in P of radius 1
//-------------------------------------------------------------------------------------------------------------------------------------
float SOmega(vec3 P, vec3 C, float r){
	float PC = length(C-P);	
	return 2.0*PI*(1.0-cos(asin(r/PC)));
}

//-------------------------------------------------------------------------------------------------------------------------------------
// This functino computes the Ambient occlusion factor of an occluder centered in C of radius r over an hemisphere oriented toward n
// centered in P
//-------------------------------------------------------------------------------------------------------------------------------------
float APsi(vec3 C, float r, vec3 P, vec3 n) {
	vec3 P_n1 = P + (occlusorRadius + 1.0) * n;
	vec3 P_n2 = P + n * 0.5;
	
	if(length(P-C)>radiusFar) return 0.0;
	return SOmega(P_n1,C,r) * max( dot(n,normalize(C-P_n2)), 0.0);
}

//-------------------------------------------------------------------------------------------------------------------------------------
// Return random float value
//-------------------------------------------------------------------------------------------------------------------------------------
float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//-------------------------------------------------------------------------------------------------------------------------------------
// Compute SSAO
//-------------------------------------------------------------------------------------------------------------------------------------
float computeSSAO(vec4 pos, vec4 normal) {
	vec2	Coord[16];
	
	float fBiasX = 1.0 / screenWidth;
	float fBiasY = 1.0 / screenHeight;
	
	Coord[0].x = -fBiasX*0.4;		Coord[1].x =		 0.0;		Coord[2].x =  fBiasX*0.1;
	Coord[0].y = -fBiasY*0.3;		Coord[1].y = -fBiasY*0.2;		Coord[2].y = -fBiasY*0.3;
	
	Coord[3].x = -fBiasX*0.5;		Coord[4].x =  fBiasX*0.3;		Coord[5].x = -fBiasX*0.7;
	Coord[3].y =		 0.0;		Coord[4].y =		 0.0;		Coord[5].y =  fBiasY*0.2;
		
	Coord[6].x =		0.0;		Coord[7].x = fBiasX*0.6;		Coord[8].x = fBiasX*0.05;
	Coord[6].y = fBiasY*0.4;		Coord[7].y = fBiasY*0.8;		Coord[8].y = fBiasY*0.5;
		
	Coord[9].x =-fBiasX*0.5;		Coord[10].x =-fBiasX*0.9;		Coord[11].x = fBiasX*0.8;
	Coord[9].y = fBiasY*0.7;		Coord[10].y = fBiasY*0.2;		Coord[11].y = fBiasY*0.3;
		
	Coord[12].x =  fBiasX*0.6;		Coord[13].x =-fBiasX*0.3;		Coord[14].x = fBiasX*0.5;
	Coord[12].y = -fBiasY*0.3;		Coord[13].y = fBiasY*0.7;		Coord[14].y =-fBiasY*0.5;
	
	Coord[15].x =		  0.0;			
	Coord[15].y = -fBiasY*0.5;	
	
		
	float occlusion = 0.0;
	float deltaX, deltaY;
	
	vec4 sampled_position;
	vec2 sampleCoordinate;
	
	// Z-Sort the pixel
	float z = dot( pos.xyz - cameraPosition, normalize(texture2D( textures[2], vec2(0.5,0.5) ).xyz - cameraPosition));
    int piece = 0;
	for(int i=0; i<10; i++) {
		deltaX = (radiusFar * 100.0 / z) * Coord[piece].x * cos(float(i) * 200.0);
		deltaY = (radiusFar * 100.0 / z) * Coord[piece].y * sin(float(i) * 200.0);
        piece++;
        if (piece == 15) piece = 0;
		/*
		sampleCoordinate = frag_texcoord.xy + vec2(deltaX, deltaY);
		if(sampleCoordinate.x < 0.0 || sampleCoordinate.x > 1.0) sampleCoordinate.x = frag_texcoord.x - deltaX / 2.0;
		if(sampleCoordinate.y < 0.0 || sampleCoordinate.y > 1.0) sampleCoordinate.y = frag_texcoord.y - deltaY / 2.0;
		sampled_position = texture2D( textures[1], sampleCoordinate);
		*/
		occlusion += abs(APsi(vec3(15.0, 65.0, 0.0).xyz, occlusorRadius, pos.xyz, normal.xyz));
	}
	
	return (1.0 - occlusion);		
}

//-------------------------------------------------------------------------------------------------------------------------------------
// Main
//-------------------------------------------------------------------------------------------------------------------------------------
void main( void )
{
    vec4 color = texture2D( textures[1], frag_texcoord.st);
	vec4 position = texture2D( textures[2], frag_texcoord.st);
	vec4 normal	= texture2D( textures[3], frag_texcoord.st);
    vec3 eyeDir	= normalize(cameraPosition - position.xyz);
	
	normal.w = 0.0;
	normal = normalize(normal);
	
	float occlusion = computeSSAO(position, normal);
	
	gl_FragColor = vec4(occlusion, occlusion, occlusion, 1.0);
}
