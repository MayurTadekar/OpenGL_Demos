#version 460 core

in vec3  v_worldPos;
in vec3  v_worldNormal;
in vec3  v_objectPos;
in float v_foamMask;

uniform vec3        u_cameraPos;
uniform samplerCube u_sky;
uniform sampler2D   u_dudv;
uniform float       u_time;

uniform vec3  u_shallowColor;
uniform vec3  u_deepColor;
uniform vec3  u_foamColor;

uniform vec3  u_sunDir;
uniform vec3  u_sunColor;
uniform float u_sunShininess;
uniform float u_sunIntensity;

uniform float u_fresnelStrength;
uniform float u_reflectionStrength;

uniform vec3  u_horizonFog;
uniform float u_fogDensity;

out vec4 FragColor;

float schlickFresnel(float NdotV)
{
    float F0 = 0.02;
    float x  = clamp(1.0 - NdotV, 0.0, 1.0);
    return F0 + (1.0 - F0) * pow(x, 5.0);
}

void main()
{
    vec3 N = normalize(v_worldNormal);

    vec2 uv1 = v_worldPos.xz * 0.04 + vec2( 0.012,  0.007) * u_time;
    vec2 uv2 = v_worldPos.xz * 0.11 + vec2(-0.009,  0.014) * u_time;
    vec2 ripple = (texture(u_dudv, uv1).rg + texture(u_dudv, uv2).rg - 1.0);
    N = normalize(N + vec3(ripple.x, 0.0, ripple.y) * 0.18);

    vec3 V = normalize(u_cameraPos - v_worldPos);
    float NdotV = max(dot(N, V), 0.0);

    vec3  baseColor = mix(u_deepColor, u_shallowColor, NdotV);

    vec3  R           = reflect(-V, N);
    vec3  reflectCol  = texture(u_sky, R).rgb;

    float fresnel = schlickFresnel(NdotV) * u_fresnelStrength;
    fresnel = clamp(fresnel, 0.0, 1.0);
    vec3  surface = mix(baseColor, reflectCol * u_reflectionStrength, fresnel);

    vec3  L    = normalize(u_sunDir);
    vec3  H    = normalize(L + V);
    float spec = pow(max(dot(N, H), 0.0), u_sunShininess) * u_sunIntensity;
    vec3  specular = u_sunColor * spec;

    float foamNoise = texture(u_dudv, v_worldPos.xz * 0.07 + vec2(0.03, -0.02) * u_time).r;
    float foam      = clamp(v_foamMask * (0.55 + 0.55 * foamNoise), 0.0, 1.0);
    vec3  withFoam  = mix(surface, u_foamColor, foam);

    vec3  litColor = withFoam + specular;

    float dist  = length(u_cameraPos - v_worldPos);
    float fog   = 1.0 - exp(-dist * u_fogDensity);
    fog         = clamp(fog, 0.0, 1.0);
    vec3 final  = mix(litColor, u_horizonFog, fog);

    FragColor = vec4(final, 1.0);
}
