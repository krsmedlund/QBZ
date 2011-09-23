uniform sampler2D textures[5]; 
uniform vec3 cameraPosition;

varying vec2 frag_texcoord;

vec3 lightColor = vec3(0.6, 0.6, 0.8);
vec3 lightDirection = vec3(-100.0, -100.0, -100.0);

float specularFactor = 10.0;
float specularIntensity = 1.5;

float specularPower = 45.4;

void main (void)
{

    vec4 texel = texture2D(textures[0], frag_texcoord);
    vec4 position = texture2D(textures[1], frag_texcoord);
    vec4 normal = texture2D(textures[2], frag_texcoord);

    float depth = position.a;
    
    vec3 lightVec = normalize(-lightDirection);
    float ndl = max(dot(normal.xyz, lightVec), 0.0);
    
    vec3 diffuseLight = texel.rgb * ndl;
    
    vec3 reflectionVec = normalize( reflect(lightVec, normal.xyz) );
    vec3 eyeDir = normalize(cameraPosition - position.xyz);
    
    float specularLight = specularIntensity * pow(max(dot(reflectionVec, eyeDir), 0.0), specularPower);
    gl_FragColor = vec4(lightColor * diffuseLight, 1.0);
    
}

