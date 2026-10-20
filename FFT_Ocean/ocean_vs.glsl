// Grestner Wave Program Vertex Shader

#version 450 core

in vec4 vPosition;

uniform mat4 u_mMatrix;
uniform mat4 u_vMatrix;
uniform mat4 u_pMatrix;

uniform vec3 cameraPos;

uniform float time;
uniform int wavesCount;

out vec2 texCoord;
out vec3 worldPos;
out vec3 worldNormal;
out float oceanRoughness;
out vec3 normal;

const float PI = 3.14159265359;

struct Wave {
    vec2 direction;
    float amplitude;
    float wavelength;
    float speed;
    float steepness;
};

uniform Wave waves[16];

vec3 GerstnerWave(
    Wave wave,
    vec2 xz,
    float weight,
    inout vec3 tangent,
    inout vec3 binormal
) {
    vec2 d = normalize(wave.direction);

    float k = 2.0 * PI / wave.wavelength;

    // float Q = min(wave.steepness / max(k * wave.amplitude * float(max(wavesCount, 1)), 0.001), 1.0);
    float Q = wave.steepness;

    float phase = k * dot(d, xz) -
        wave.speed * time;

    float s = sin(phase);
    float c = cos(phase);

    float WA = k * wave.amplitude;
    float QWA = Q * WA;

    tangent += weight * vec3(-QWA * d.x * d.x * s, WA * d.x * c, -QWA * d.x * d.y * s);

    binormal += weight * vec3(-QWA * d.x * d.y * s, WA * d.y * c, -QWA * d.y * d.y * s);

    return weight * vec3(Q * wave.amplitude * d.x * c, wave.amplitude * s, Q * wave.amplitude * d.y * c);
}

void main() {
    //////////////////////////////////////////////////////
    // Infinite ocean patch centered on camera
    //////////////////////////////////////////////////////

    vec3 pos = vPosition.xyz;

    vec2 worldXZ = vPosition.xz + cameraPos.xz;

    //////////////////////////////////////////////////////
    // Tangent basis
    //////////////////////////////////////////////////////

    vec3 tangent = vec3(1.0, 0.0, 0.0);
    vec3 binormal = vec3(0.0, 0.0, 1.0);

    //////////////////////////////////////////////////////
    // Unresolved wave energy
    //////////////////////////////////////////////////////

    float unresolvedEnergy = 0.0;

    //////////////////////////////////////////////////////
    // Distance based LOD
    //////////////////////////////////////////////////////

    float distanceToCamera = length(vPosition.xz);

    float lodSize = max(1.0, distanceToCamera * 0.02);

    //////////////////////////////////////////////////////
    // Waves
    //////////////////////////////////////////////////////

    for(int i = 0; i < wavesCount; i++) {
        float ratio = waves[i].wavelength / lodSize;

        float weight = smoothstep(0.5, 1.25, ratio);

        unresolvedEnergy += (1.0 - weight) * waves[i].amplitude;

        pos += GerstnerWave(waves[i], worldXZ, weight, tangent, binormal);
    }

    //////////////////////////////////////////////////////
    // Normal
    //////////////////////////////////////////////////////

    normal = normalize(cross(binormal, tangent));

    //////////////////////////////////////////////////////
    // World space
    //////////////////////////////////////////////////////

    vec4 wp = u_mMatrix * vec4(pos, 1.0);

    worldPos = wp.xyz;

    worldNormal = normalize(mat3(transpose(inverse(u_mMatrix))) * normal);

    //////////////////////////////////////////////////////
    // Fragment shader inputs
    //////////////////////////////////////////////////////

    texCoord = worldXZ;

    oceanRoughness = clamp(0.03 + unresolvedEnergy * 0.05, 0.03, 0.35);

    //////////////////////////////////////////////////////
    // Render
    //////////////////////////////////////////////////////

    gl_Position = u_pMatrix *
        u_vMatrix *
        wp;
}
