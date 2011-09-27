#version 120

uniform highp mat4 p_matrix, m_matrix, v_matrix, RotationMatrixInverse, TransformMatrixInverse;
uniform highp sampler2D textures[4];

uniform float currentTime;

attribute highp vec3 position, normal, tangent, bitangent;
attribute highp vec2 texcoord;

varying vec2 frag_texcoord;
varying mat4 mv_matrix;
varying vec4 frag_position;
varying vec4 frag_normal, frag_tangent, frag_bitangent;

varying mat4 TBN;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    vec3 pos = position;

    /*
    vec3 delta;
    delta.y = cos( (currentTime / (pos.x / pos.z)) / 2200.0 ) * 0.2;
    delta.x = cos( (currentTime / (pos.y / pos.z)) / 3200.0 ) * 0.2;
    delta.z = cos( (currentTime / (pos.x / pos.y)) / 3200.0 ) * 0.2;
    //pos += delta;
  */
    gl_Position = p_matrix * mv_matrix * vec4(pos, 1.0);
    frag_texcoord = texcoord;
    
    frag_position =  m_matrix * vec4(pos, 1.0);
    frag_normal = m_matrix * vec4 (normal, 0.0);
    frag_tangent = mv_matrix * vec4(pos, 1.0); 
    
    TBN = mat4(tangent.x, bitangent.x, normal.x, 0,
               tangent.y, bitangent.y, normal.y, 0,
               tangent.z, bitangent.z, normal.z, 0,
               0, 0, 0, 1 );
    
    gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);    

}

