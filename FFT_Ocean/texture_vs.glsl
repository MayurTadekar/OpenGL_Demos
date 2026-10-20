// Grestner Wave Program Vertex Shader

#version 450 core

in vec4 vPosition;

uniform mat4 u_mMatrix;
uniform mat4 u_vMatrix;
uniform mat4 u_pMatrix;

uniform float time;
uniform int wavesCount;

out vec3 texCoord;
out vec3 worldPos;
out vec3 worldNormal;

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
    inout vec3 tangent,
    inout vec3 binormal
) {
    float k = 2.0 * PI / wave.wavelength;

    vec2 d = normalize(wave.direction);

    float phase = k * dot(d, xz) - wave.speed * time;

    float c = cos(phase);
    float s = sin(phase);

    float Q = wave.steepness;

    tangent += vec3(-Q * d.x * d.x * wave.amplitude * k * s, d.x * wave.amplitude * k * c, -Q * d.x * d.y * wave.amplitude * k * s);

    binormal += vec3(-Q * d.x * d.y * wave.amplitude * k * s, d.y * wave.amplitude * k * c, -Q * d.y * d.y * wave.amplitude * k * s);

    return vec3(Q * wave.amplitude * d.x * c, wave.amplitude * s, Q * wave.amplitude * d.y * c);
}

void main() {
    vec3 pos = vPosition.xyz;

    vec3 tangent = vec3(1.0, 0.0, 0.0);
    vec3 binormal = vec3(0.0, 0.0, 1.0);

    for(int i = 0; i < wavesCount; i++) {
        pos += GerstnerWave(waves[i], vPosition.xz, tangent, binormal);
    }

    texCoord = pos;

    vec3 normal = normalize(cross(binormal, tangent));

    vec4 wp = u_mMatrix * vec4(pos, 1.0);

    worldPos = wp.xyz;
    worldNormal = mat3(transpose(inverse(u_mMatrix))) * normal;

    gl_Position = u_pMatrix *
        u_vMatrix *
        wp;
}