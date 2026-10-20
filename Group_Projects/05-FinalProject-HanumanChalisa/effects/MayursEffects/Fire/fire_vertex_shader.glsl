// ####### VERTEX SHADER  ####### 

#version 450 core                         

in vec4 vPosition;
in vec3 vColor;

uniform mat4 u_mMatrix;
uniform mat4 u_vMatrix;
uniform mat4 u_pMatrix;

uniform float billboardScale = 1.0;
uniform bool enableBillboard = false;

out vec3 fragPos;
out vec3 viewPos;
out vec2 screenCoord;
out vec3 ovColor;
out vec2 ovUV;
out vec2 localUV;

void main() {
    vec3 worldPos;

    if(enableBillboard) {
        // Billboard center
        vec3 center = vec3(u_mMatrix * vec4(0.0, 0.0, 0.0, 1.0));

        vec3 cameraPos = vec3(u_vMatrix[0][3], u_vMatrix[1][3], u_vMatrix[2][3]);

        // Camera axes
        vec3 cameraRight = vec3(u_vMatrix[0][0], u_vMatrix[1][0], u_vMatrix[2][0]);

        vec3 cameraUp = vec3(u_vMatrix[0][1], u_vMatrix[1][1], u_vMatrix[2][1]);

        // Local quad coords
        vec2 localPos = vPosition.xy;

        localUV = localPos;

        // Billboard world position
        worldPos = center +
            cameraRight * localPos.x * billboardScale +
            cameraUp * localPos.y * billboardScale;

        ovUV = localPos * 0.5 + 0.5;
    } else {
        // Normal mesh transform
        vec4 wp = u_mMatrix * vPosition;
        worldPos = wp.xyz;

        localUV = vPosition.xy;

        ovUV = vPosition.xy * 0.5 + 0.5;
    }

    // View transform
    vec4 viewPosition = u_vMatrix * vec4(worldPos, 1.0);

    // Projection
    gl_Position = u_pMatrix * viewPosition;

    // Outputs
    fragPos = worldPos;
    viewPos = viewPosition.xyz;
    screenCoord = gl_Position.xy / gl_Position.w;
    ovColor = vColor;
}
