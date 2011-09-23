uniform  sampler2D textures[2];
uniform mat4 p_matrix, m_matrix, v_matrix, shadowTextureMatrix;

varying mat4 mv_matrix;
varying vec2 frag_texcoord;

void main()
{
    vec4 pos = texture2D(textures[1], frag_texcoord);
    vec4 sc = shadowTextureMatrix * pos;
    vec3 scBiased = sc.xyz / sc.w;
    scBiased.z += 0.0005;

    float distanceFromLight = ((vec4(texture2D(textures[0], scBiased.st)).r)) ;

    float shadow;
    if (scBiased.z > distanceFromLight) {
        shadow = 1.0;
    } else {
        shadow = 0.0;
    }


    gl_FragColor = vec4(sc.x);
}



