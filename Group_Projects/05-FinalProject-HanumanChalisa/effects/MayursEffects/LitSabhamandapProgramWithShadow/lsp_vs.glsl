// LitSabhamandap Vertex Shader

#version 460 core
in vec4 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 u_hanumanPLVMMatrix;
uniform mat4 u_vibhishanPLVMMatrix;
uniform mat4 u_sabhamandapPLVMMatrix;
uniform mat4 ministerChairPLVMMatrix;
uniform mat4 pillarPLVMMatrix;

uniform vec4 uClippingPlane;

out vec2 oTexCoord;
out vec3 oNormal;
out vec3 oFragPos;

out vec4 hanumanShadowLightSpacePos;
out vec4 vibhishanShadowLightSpacePos;
out vec4 sabhamandapShadowLightSpacePos;
out vec4 ministerChairLightSpacePos;
out vec4 pillarChairLightSpacePos;

void main(void) {
        vec4 worldPos = uModelMatrix * aPosition;
        oFragPos = worldPos.xyz;
        // oNormal = normalize(mat3(uModelMatrix) * aNormal);
        oNormal = normalize(mat3(transpose(inverse(uModelMatrix))) * aNormal);
        oTexCoord = aTexCoord;
        gl_ClipDistance[0] = dot(worldPos, uClippingPlane);
        gl_Position = uProjectionMatrix * uViewMatrix * worldPos;

        hanumanShadowLightSpacePos = u_hanumanPLVMMatrix * aPosition;
        vibhishanShadowLightSpacePos = u_vibhishanPLVMMatrix * aPosition;
        sabhamandapShadowLightSpacePos = u_sabhamandapPLVMMatrix * aPosition;
        ministerChairLightSpacePos = ministerChairPLVMMatrix * aPosition;
        pillarChairLightSpacePos = pillarPLVMMatrix * aPosition;

}
