uniform sampler2D textures[3]; 
uniform vec3 cameraPosition;

varying vec2 frag_texcoord;
varying vec4 frag_position;

uniform vec3 lightColor;
uniform vec3 lightPos;


//!{name:'lightRadius', type:'float', max:15.0 , min: 0.0 }
uniform float lightRadius;

//!{name:'shininess', type:'float', max:250.0 , min: 5.0 }
uniform float shininess;

void main (void)
{
    vec2 tmppos = frag_position.xy / frag_position.w;
    vec2 texcoord = (tmppos + vec2(1.0)) * 0.5;

    vec3 texel = texture2D(textures[0], texcoord.st).rgb;
    vec3 position = texture2D(textures[1], texcoord.st).xyz;
    vec4 normal = texture2D(textures[2], texcoord.st);
    
    float specularIntensity = 1.0;//normal.a;
    
    normal.a = 0.0;
    normal = normalize(normal);
    
    vec3 lightVec = lightPos - position;
    float attenuation = clamp(1.0 - length(lightVec) / lightRadius, 0.0, 1.0);
    vec3 eyeDir = normalize(cameraPosition - position.xyz);
    vec3 vHalfVector = normalize(lightVec + eyeDir);
    lightVec = normalize(lightVec);
    
    float NdotL = max(dot(normal.xyz, lightVec), 0.0);
    vec3 diffuseLight = lightColor * NdotL * attenuation;

    float specularLight = 0.0;
    if (NdotL > 0.0)
        specularLight = attenuation * specularIntensity * pow(clamp(dot(normal.xyz, vHalfVector), 0.0, 1.0), shininess*2.0);
    
    gl_FragColor = vec4(diffuseLight + lightColor*specularLight, 1.0);
    
}

/*
 vec3 eyeDir = normalize(cameraPosition - position.xyz);

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
 */