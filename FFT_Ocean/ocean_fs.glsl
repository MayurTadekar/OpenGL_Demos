// Grestner Wave Program Fragment Shader
#version 450 core

in vec3 worldPos;
in vec3 worldNormal;
in vec2 texCoord;
in float oceanRoughness;

uniform vec3 cameraPos;
uniform vec3 sunPos;

uniform sampler2D waterNormalMap1Sampler;
uniform sampler2D waterNormalMap2Sampler;

/*
    Sky cubemap
*/
uniform samplerCube skyboxSampler;

uniform float time;

out vec4 Fragcolor;

const float PI = 3.14159265359;

//////////////////////////////////////////////////////////
// GGX
//////////////////////////////////////////////////////////

float DistributionGGX(
    vec3 N,
    vec3 H,
    float roughness
) {
    float a = roughness * roughness;
    float a2 = a * a;

    float NdotH = max(dot(N, H), 0.0);

    float NdotH2 = NdotH * NdotH;

    float denom = NdotH2 * (a2 - 1.0) + 1.0;

    return a2 /
        (PI * denom * denom);
}

float GeometrySchlickGGX(
    float NdotV,
    float roughness
) {
    float r = roughness + 1.0;

    float k = (r * r) / 8.0;

    return NdotV /
        (NdotV * (1.0 - k) + k);
}

float GeometrySmith(
    vec3 N,
    vec3 V,
    vec3 L,
    float roughness
) {
    float NdotV = max(dot(N, V), 0.0);

    float NdotL = max(dot(N, L), 0.0);

    float ggx1 = GeometrySchlickGGX(NdotV, roughness);

    float ggx2 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 FresnelSchlick(
    float cosTheta,
    vec3 F0
) {
    return F0 +
        (1.0 - F0) *
        pow(1.0 - cosTheta, 5.0);
}

//////////////////////////////////////////////////////////

void main() {
    //////////////////////////////////////////////////////
    // Animated ripples
    //////////////////////////////////////////////////////

    vec2 uv1 = texCoord * 0.02 +
        vec2(time * 0.02, time * 0.01);

    vec2 uv2 = texCoord * 0.02 +
        vec2(-time * 0.01, time * 0.02);

    vec3 n1 = texture(waterNormalMap1Sampler, uv1).rgb * 2.0 - 1.0;

    vec3 n2 = texture(waterNormalMap2Sampler, uv2).rgb * 2.0 - 1.0;

    vec3 ripple = normalize(n1 + n2);

    vec3 N = normalize(worldNormal +
        ripple * 0.2);

    vec3 V = normalize(cameraPos -
        worldPos);

    vec3 L = normalize(sunPos -
        worldPos);

    vec3 H = normalize(V + L);

    float NdotV = max(dot(N, V), 0.001);

    float NdotL = max(dot(N, L), 0.001);

    //////////////////////////////////////////////////////
    // Water roughness
    //////////////////////////////////////////////////////

    float distanceFade = clamp(length(cameraPos - worldPos) / 5000.0, 0.0, 1.0);

    float roughness = mix(oceanRoughness, 0.25, distanceFade);

    //////////////////////////////////////////////////////
    // Fresnel
    //////////////////////////////////////////////////////

    vec3 F0 = vec3(0.02);

    vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

    //////////////////////////////////////////////////////
    // GGX Specular
    //////////////////////////////////////////////////////

    float D = DistributionGGX(N, H, roughness);

    float G = GeometrySmith(N, V, L, roughness);

    vec3 numerator = D * G * F;

    float denominator = max(4.0 *
        NdotV *
        NdotL, 0.001);

    vec3 specular = numerator /
        denominator;

    //////////////////////////////////////////////////////
    // Sky Reflection
    //////////////////////////////////////////////////////

    vec3 reflectionDir = reflect(-V, N);

    vec3 skyReflection = texture(skyboxSampler, reflectionDir).rgb;

    //////////////////////////////////////////////////////
    // Water absorption
    //////////////////////////////////////////////////////

    vec3 deepWater = vec3(0.0, 0.06, 0.25);

    vec3 shallowWater = vec3(0.10, 0.45, 0.75);

    float depthFactor = clamp(N.y, 0.0, 1.0);

    vec3 waterColor = mix(deepWater, shallowWater, depthFactor);

    //////////////////////////////////////////////////////
    // Bruneton-style blend
    //////////////////////////////////////////////////////

    vec3 reflectedLight = skyReflection * F;

    vec3 refractedLight = waterColor * (1.0 - F);

    //////////////////////////////////////////////////////
    // Sun glitter
    //////////////////////////////////////////////////////

    vec3 sunColor = vec3(1.0, 0.95, 0.85);

    vec3 sunlight = specular *
        sunColor *
        NdotL *
        20.0;

    //////////////////////////////////////////////////////
    // Horizon brightening
    //////////////////////////////////////////////////////

    float horizon = pow(1.0 - NdotV, 3.0);

    reflectedLight += skyReflection *
        horizon *
        0.5;

    //////////////////////////////////////////////////////
    // Final
    //////////////////////////////////////////////////////

    vec3 color = reflectedLight +
        refractedLight +
        sunlight;

    color = color /
        (color + vec3(1.0));

    color = pow(color, vec3(1.0 / 2.2));

    Fragcolor = vec4(color, 1.0);
}