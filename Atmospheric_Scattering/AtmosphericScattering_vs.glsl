// Vertex Shader

#version 450 core

in vec3 vPosition;

uniform mat4 u_mMatrix;
uniform mat4 u_vMatrix;
uniform mat4 u_pMatrix;

out vec2 WorldPos;

void main() {
    vec4 worldPos = u_mMatrix * vec4(vPosition, 1.0);

    WorldPos = worldPos.xy;

    gl_Position = worldPos;
}