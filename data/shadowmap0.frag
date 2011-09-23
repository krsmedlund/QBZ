varying vec4 frag_position;
float depth;

void main() {
    depth = frag_position.z / frag_position.w;
    gl_FragColor = vec4(depth, depth, depth, 1.0);
}
