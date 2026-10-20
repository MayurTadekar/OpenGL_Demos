#version 450 core

out vec4 Fragcolor;

uniform vec3 color;

void main() {

	Fragcolor = vec4(color, 1.0);
}
