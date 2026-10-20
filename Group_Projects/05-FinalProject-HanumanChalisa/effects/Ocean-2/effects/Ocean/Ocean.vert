#version 460 core

layout(location = 0) in vec3 a_position;

#define MAX_WAVES 6

uniform mat4  u_model;
uniform mat4  u_view;
uniform mat4  u_projection;
uniform float u_time;

uniform int   u_numWaves;
uniform vec2  u_waveDir       [MAX_WAVES];
uniform float u_waveAmp       [MAX_WAVES];
uniform float u_waveWavelength[MAX_WAVES];
uniform float u_waveSpeed     [MAX_WAVES];
uniform float u_waveSteepness [MAX_WAVES];

uniform float u_foamThreshold;
uniform float u_foamSoftness;
uniform float u_foamChoppinessGain;

out vec3  v_worldPos;
out vec3  v_worldNormal;
out vec3  v_objectPos;
out float v_foamMask;

void gerstner(in  vec3 basePosWorld,
              out vec3 displacement,
              out vec3 normalAccum,
              out float jacobian)
{
    displacement = vec3(0.0);
    normalAccum  = vec3(0.0);
    jacobian     = 0.0;

    for (int i = 0; i < u_numWaves; ++i)
    {
        vec2  D       = normalize(u_waveDir[i]);
        float A       = u_waveAmp[i];
        float wavelen = max(u_waveWavelength[i], 0.0001);
        float w       = 6.28318530718 / wavelen;
        float phi     = u_waveSpeed[i] * w;
        float Q       = u_waveSteepness[i] / max(w * A * float(u_numWaves), 0.0001);

        float dotp = w * dot(D, basePosWorld.xz) + phi * u_time;
        float C    = cos(dotp);
        float S    = sin(dotp);

        displacement.x +=  Q * D.x * A * C;
        displacement.z +=  Q * D.y * A * C;
        displacement.y +=          A * S;

        float WA = w * A;
        normalAccum.x +=  D.x * WA * C;
        normalAccum.y +=  Q   * WA * S;
        normalAccum.z +=  D.y * WA * C;

        jacobian += Q * WA * S;
    }
}

void main()
{
    vec3 basePosWorld = (u_model * vec4(a_position, 1.0)).xyz;

    vec3 displacement;
    vec3 normalAccum;
    float jacobian;
    gerstner(basePosWorld, displacement, normalAccum, jacobian);

    vec3 worldPos = basePosWorld + displacement;

    vec3 worldNormal = normalize(vec3(-normalAccum.x, 1.0 - normalAccum.y, -normalAccum.z));

    float heightMask = smoothstep(u_foamThreshold,
                                  u_foamThreshold + max(u_foamSoftness, 0.0001),
                                  worldPos.y);
    float crestMask = clamp(jacobian * u_foamChoppinessGain, 0.0, 1.0);
    float foam      = clamp(heightMask + crestMask, 0.0, 1.0);

    v_objectPos   = a_position;
    v_worldPos    = worldPos;
    v_worldNormal = worldNormal;
    v_foamMask    = foam;

    gl_Position = u_projection * u_view * vec4(worldPos, 1.0);
}
