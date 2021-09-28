#version 460
precision mediump float;

in vec4 frag_coord;
out vec4 frag_color;

void main() {
	frag_color[0] = 1.0;
	frag_color[1] = 0.0;
	frag_color[2] = 1.0;
	frag_color[3] = 1.0;
}
