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

uniform float billboardScale = 1.0;

out vec2 ovTexcoord;

void main(void) {
    // Billboard center in world space
    vec3 center = vec3(u_mMatrix * vec4(0.0, 0.0, 0.0, 1.0));

    // Extract camera right and up vectors from view matrix
    vec3 cameraRight = vec3(u_vMatrix[0][0], u_vMatrix[1][0], u_vMatrix[2][0]);

    vec3 cameraUp = vec3(u_vMatrix[0][1], u_vMatrix[1][1], u_vMatrix[2][1]);

    // Apply billboard offset
    vec3 worldPos = center +
        cameraRight * vPosition.x * billboardScale +
        cameraUp * vPosition.y * billboardScale;

    gl_Position = u_pMatrix * u_vMatrix * vec4(worldPos, 1.0);

    ovTexcoord = vTexcoord;
}