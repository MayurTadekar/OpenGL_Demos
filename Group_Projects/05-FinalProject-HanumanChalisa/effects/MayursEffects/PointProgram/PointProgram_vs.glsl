#version 450 core

in vec4 vPosition;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_ProjectionMatrix;

void main() {

	gl_Position = u_ProjectionMatrix * u_viewMatrix * u_modelMatrix * vPosition;
}
