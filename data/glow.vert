#version 110

uniform mat4 p_matrix, m_matrix, v_matrix, RotationMatrixInverse, TransformMatrixInverse;
uniform sampler2D textures[4];

attribute vec3 position, normal, tangent, bitangent;
attribute vec2 texcoord;

varying vec2 frag_texcoord;
varying mat4 mv_matrix;
varying vec4 frag_position;
varying vec4 frag_normal, frag_tangent, frag_bitangent;
varying mat4 TBN;

void main()
{
    mv_matrix = v_matrix * m_matrix;
    gl_Position = p_matrix * mv_matrix * vec4(position, 1.0);
    frag_texcoord = texcoord;
    
    frag_position == p_matrix * mv_matrix * vec4(position, 1.0);
    frag_normal = RotationMatrixInverse * vec4(normal, 0.0);
    
    TBN = mat4(tangent.x, bitangent.x, normal.x, 0,
               tangent.y, bitangent.y, normal.y, 0,
               tangent.z, bitangent.z, normal.z, 0,
               0, 0, 0, 1 );
    
}

