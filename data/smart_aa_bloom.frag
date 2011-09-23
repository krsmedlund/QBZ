uniform sampler2D textures[1];
varying vec2 frag_texcoord;
uniform float channel;
const vec3 dt = vec3(1.4,1.4,1.4);


void main() {
    if (channel != 1.0) {
    vec2 size     = vec2(250.0 * channel, 250.0 * channel);
    vec2 inv_size = vec2(1.0/250.0, 1.0/250.0);
    vec2 OGL2Pos = frag_texcoord.xy * size;
    vec2 fp  = fract(OGL2Pos);
    vec2 dx  = vec2(inv_size.x,0.0);
    vec2 dy  = vec2(0.0,inv_size.y);
    vec2 g1  = vec2( inv_size.x,inv_size.y);
    vec2 g2  = vec2(-inv_size.x,inv_size.y);

    vec2 pC4 = floor(OGL2Pos)/size;
    vec2 pC8 = pC4 + g1;

    vec3 C0 = texture2D(textures[0],pC4-g1).xyz; 
    vec3 C1 = texture2D(textures[0],pC4-dy).xyz;
    vec3 C2 = texture2D(textures[0],pC4-g2).xyz;
    vec3 D3 = texture2D(textures[0],pC8-dy-dy).xyz;
    vec3 C3 = texture2D(textures[0],pC4-dx).xyz;
    vec3 C4 = texture2D(textures[0],pC4).xyz;
    vec3 C5 = texture2D(textures[0],pC4+dx).xyz;
    vec3 D4 = texture2D(textures[0],pC8-g2).xyz;
    vec3 C6 = texture2D(textures[0],pC4+g2).xyz;
    vec3 C7 = texture2D(textures[0],pC4+dy).xyz;
    vec3 C8 = texture2D(textures[0],pC8).xyz;
    vec3 D5 = texture2D(textures[0],pC8+dx).xyz;
    vec3 D0 = texture2D(textures[0],pC4+g2+dy).xyz;
    vec3 D1 = texture2D(textures[0],pC8+g2).xyz;
    vec3 D2 = texture2D(textures[0],pC8+dy).xyz;
    vec3 D6 = texture2D(textures[0],pC8+g1).xyz;

    vec3 ul,ur,dl,dr,t1,t2;   float hl,vl,d1,d2;

    // C0 C1 C2 D3
    // C3 C4 C5 D4
    // C6 C7 C8 D5
    // D0 D1 D2 D6 

    d1=dot(abs(C0-C8),dt)+0.001;
    d2=dot(abs(C2-C6),dt)+0.001;
    hl=dot(abs(C3-C5),dt)+0.001;
    vl=dot(abs(C1-C7),dt)+0.001;

    ul =(hl*(C1+C7)+vl*(C3+C5)+(hl+vl)*C4)/(6.0*(hl+vl));
    ul+=(d1*(C2+C6)+d2*(C0+C8)+(d1+d2)*C4)/(6.0*(d1+d2));

    d1=dot(abs(C1-D5),dt)+0.001;
    d2=dot(abs(C7-D3),dt)+0.001;
    hl=dot(abs(C4-D4),dt)+0.001;
    vl=dot(abs(C2-C8),dt)+0.001;

    ur =(hl*(C2+C8)+vl*(C4+D4)+(hl+vl)*C5)/(6.0*(hl+vl));
    ur+=(d1*(C7+D3)+d2*(C1+D5)+(d1+d2)*C5)/(6.0*(d1+d2));

    d1=dot(abs(C3-D2),dt)+0.001;
    d2=dot(abs(C5-D0),dt)+0.001;
    hl=dot(abs(C6-C8),dt)+0.001;
    vl=dot(abs(C4-D1),dt)+0.001;

    dl =(hl*(C4+D1)+vl*(C6+C8)+(hl+vl)*C7)/(6.0*(hl+vl));
    dl+=(d1*(C5+D0)+d2*(C3+D2)+(d1+d2)*C7)/(6.0*(d1+d2));

    d1=dot(abs(C4-D6),dt)+0.001;
    d2=dot(abs(D1-D4),dt)+0.001;
    hl=dot(abs(C7-D5),dt)+0.001;
    vl=dot(abs(C5-D2),dt)+0.001;

    dr =(hl*(C5+D2)+vl*(C7+D5)+(hl+vl)*C8)/(6.0*(hl+vl));
    dr+=(d1*(D1+D4)+d2*(C4+D6)+(d1+d2)*C8)/(6.0*(d1+d2));

    C1 =((dr*fp.x+dl*(1.0-fp.x))*fp.y+(ur*fp.x+ul*(1.0-fp.x))*(1.0-fp.y));
    d1 = length(C1);
        
    gl_FragColor.xyz=mix(d1,1.75*normalize(vec2(d1*d1,0.82)).x,0.577*d1)*normalize(C1);
    } else {
        gl_FragColor = texture2D(textures[0], frag_texcoord.xy).rgba;
    }
}
