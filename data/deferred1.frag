uniform sampler2D textures[5]; 
uniform vec3 cameraPosition;
varying vec2 frag_texcoord;

vec4 ambientColor = vec4(0.4, 0.6, 0.7, 1.0);
vec3 diffuse = vec3(0,0,0);
vec3 specular = vec3(0,0,0);
vec3 light = vec3(0,0,0);
vec3 lightDir = vec3(0,0,0);
vec3 vHalfVector = vec3(0,0,0); 
float lightIntensity = 0.0;

int lightCount = 4;

void main( void )
{
    vec4 texel = texture2D(textures[0], frag_texcoord);
    vec4 position = texture2D(textures[1], frag_texcoord);
    vec4 normal = texture2D(textures[2], frag_texcoord);
    
    float specularIntensity = 1.0; //normal.a;
    float selfLighting = normal.a;
    float ssao = texel.a;
    
    vec3 eyeDir = normalize(cameraPosition - position.xyz);
    
    vec3 lightColor;
    float lightDistance;
    float localDiffuse;
    
    normal.w = 0.0;
    normal = normalize(normal);

    /* Lights */
    
    for (int i=0; i < lightCount; ++i) {
        light = texture2D(textures[3], vec2(0.01, float(i) * 0.99 / float(lightCount))).xyz;
        lightColor = texture2D(textures[3], vec2(0.99, float(i) * 0.99 / float(lightCount))).xyz;
        lightDir = light - position.xyz;
        lightDistance = length(lightDir);

        
        lightDir /= lightDistance;
        vHalfVector = normalize(lightDir+eyeDir);
        
        localDiffuse = max(dot(normal.xyz, lightDir), 0.0);
        diffuse += lightColor * localDiffuse * (1.0 / ( 1.0 + 0.0005 * lightDistance + 0.0009 * pow(lightDistance, 2.0)));    
        
        if(localDiffuse > 0.0) {
            specular += lightColor * pow(max(dot(normal.xyz,vHalfVector),0.0), 40.0); 
        }
    }

    gl_FragColor =
        vec4(diffuse, 1.0) * texel 
        //+ vec4(specular * specularIntensity, 1.0) 
        + ambientColor * (ssao) * texel
        + selfLighting * texel
    ;
    
}