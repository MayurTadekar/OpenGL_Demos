// #version 450 core

// in vec4 vPosition;
// in vec2 vTexcoord;

// uniform mat4 u_mMatrix;
// uniform mat4 u_vMatrix;
// uniform mat4 u_pMatrix;

// out vec2 ovTexcoord;
// void main(void) {

//         gl_Position = u_pMatrix * u_vMatrix * u_mMatrix * vPosition;

//         ovTexcoord = vTexcoord;
// }

#version 450 core

in vec4 vPosition;   // Quad vertex offsets (-0.5 to +0.5)
in vec2 vTexcoord;

uniform mat4 u_mMatrix;
uniform mat4 u_vMatrix;
uniform mat4 u_pMatrix;

out vec2 ovTexcoord;

void main(void) {

    gl_Position = u_pMatrix * u_vMatrix * u_mMatrix * vPosition;//vec4(worldPos, 1.0);

    ovTexcoord = vTexcoord;
}