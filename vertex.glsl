#version 460
precision mediump float;

in vec2 vertex_pos;
out vec4 frag_coord;

void main(void) {
	frag_coord = vec4(vertex_pos, 0.0, 1.0);
}
