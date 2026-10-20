#version 460 core
precision highp float;

in vec4 aPosition;
in vec2 aTexcoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

uniform sampler2D uHeightMap;

uniform float uHeightScale;

out vec2 Outtexcoords;
out vec3 FragPosition;
out mat3 NormalMatrix;

void main(void)
{
    vec4 terrainPosition = vec4(0.0f);
    terrainPosition = aPosition;

    // Displacement: always sample mip 0. Mipmapped height in vertex stage causes terracing.
    vec2 uv = clamp(aTexcoord, 0.001, 0.999);
    float h = texture(uHeightMap, uv).r;
    terrainPosition.y = h * uHeightScale;

    // Calculating Frag Position
    FragPosition = vec3(uModelMatrix * terrainPosition);

    // Sending texcoord to attach other maps
    Outtexcoords = uv;

    // Sending Normal Matrix to get terrain normals
    NormalMatrix = mat3(transpose(inverse(uModelMatrix)));

    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * terrainPosition;
}