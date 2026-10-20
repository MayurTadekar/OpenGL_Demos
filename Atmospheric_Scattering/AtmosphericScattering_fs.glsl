// Fragment Shader
#version 450 core

in vec2 WorldPos;

out vec4 FragColor;

uniform vec3 cameraPos;
uniform vec3 sunDir;

uniform float innerRadius;
uniform float outerRadius;

uniform mat4 u_vMatrix;
uniform mat4 u_pMatrix;

uniform float Kr;
uniform float Km;
uniform float ESun;

uniform vec3 invWavelength;

uniform float rayleighScaleHeight;
uniform float mieScaleHeight;

const int VIEW_SAMPLES = 32;
const int LIGHT_SAMPLES = 16;

const float PI = 3.14159265359;

////////////////////////////////////////////////////////////

// float Scale(float cosAngle) {
//     float x = 1.0 - cosAngle;

//     return scaleDepth *
//         exp(-0.00287 +
//         x * (0.459 +
//         x * (3.83 +
//         x * (-6.80 +
//         x * 5.25))));
// }

////////////////////////////////////////////////////////////

bool RaySphere(
    vec3 center,
    vec3 rayOrigin,
    vec3 rayDir,
    float radius,
    out float tNear,
    out float tFar
) {
    vec3 oc = rayOrigin - center;

    float b = dot(oc, rayDir);
    float c = dot(oc, oc) - radius * radius;

    float h = b * b - c;

    if(h < 0.0)
        return false;

    h = sqrt(h);

    tNear = -b - h;
    tFar = -b + h;

    return true;

}

////////////////////////////////////////////////////////////
float DensityRayleigh(vec3 pos) {
    float altitude = length(pos) - innerRadius;

    return exp(-altitude / rayleighScaleHeight);
}

float DensityMie(vec3 pos) {
    float altitude = length(pos) - innerRadius;

    return exp(-altitude / mieScaleHeight);
}

////////////////////////////////////////////////////////////

vec3 IntegrateAtmosphere(vec3 rayOrigin, vec3 rayDir) {
    float t0, t1;

    if(!RaySphere(vec3(0.0), rayOrigin, rayDir, outerRadius, t0, t1))
        return vec3(0);

    t0 = max(t0, 0.0);

    float segmentLength = (t1 - t0) / float(VIEW_SAMPLES);

    vec3 sumR = vec3(0);
    vec3 sumM = vec3(0);

    float opticalDepthR = 0.0;
    float opticalDepthM = 0.0;

    for(int i = 0; i < VIEW_SAMPLES; i++) {
        float t = t0 +
            (float(i) + 0.5) *
            segmentLength;

        vec3 samplePos = rayOrigin +
            rayDir * t;

        float height = length(samplePos);

        // float localDensity = Density(samplePos);

        // opticalDepthR += localDensity * segmentLength;

        // opticalDepthM += localDensity * segmentLength;

        float densityR = DensityRayleigh(samplePos);
        float densityM = DensityMie(samplePos);

        opticalDepthR += densityR * segmentLength;
        opticalDepthM += densityM * segmentLength;

        float tSun0, tSun1;

        RaySphere(vec3(0.0), samplePos, sunDir, outerRadius, tSun0, tSun1);

        float lightSegment = tSun1 /
            float(LIGHT_SAMPLES);

        float lightDepthR = 0.0;
        float lightDepthM = 0.0;

        for(int j = 0; j < LIGHT_SAMPLES; j++) {
            float lt = (float(j) + 0.5) *
                lightSegment;

            vec3 lightPos = samplePos +
                sunDir * lt;

            float lightHeight = length(lightPos);

            // float density = Density(lightPos);

            // lightDepthR += density * lightSegment;

            // lightDepthM += density * lightSegment;

            float densityR = DensityRayleigh(lightPos);
            float densityM = DensityMie(lightPos);

            lightDepthR += densityR * lightSegment;
            lightDepthM += densityM * lightSegment;
        }

        // vec3 tau = invWavelength * (Kr * (opticalDepthR + lightDepthR) + (Km * (opticalDepthM + lightDepthM)));

        vec3 tau = Kr * invWavelength * (opticalDepthR + lightDepthR) + Km * (opticalDepthM + lightDepthM);

        vec3 attenuation = exp(-tau);

        // sumR += attenuation * localDensity * segmentLength;

        // sumM += attenuation * localDensity * segmentLength;

        sumR += attenuation *
            densityR *
            segmentLength;

        sumM += attenuation *
            densityM *
            segmentLength;
    }

    float mu = dot(rayDir, sunDir);

    float mu2 = mu * mu;

    ////////////////////////////////////////
    // Rayleigh phase
    ////////////////////////////////////////

    float phaseR = 3.0 / (16.0 * PI) *
        (1.0 + mu2);

    ////////////////////////////////////////
    // Mie phase
    ////////////////////////////////////////

    float g = 0.76;
    float g2 = g * g;

    float phaseM = (3.0 / (8.0 * PI)) *
        ((1.0 - g2) * (1.0 + mu2)) /
        ((2.0 + g2) *
        pow(1.0 + g2 - 2.0 * g * mu, 1.5));

    vec3 rayleigh = ESun *
        Kr *
        invWavelength *
        phaseR *
        sumR;

    vec3 mie = ESun *
        Km *
        phaseM *
        sumM;

    return rayleigh + mie;
}

////////////////////////////////////////////////////////////

void main() {
    // vec3 rayDir = normalize(WorldPos - cameraPos);
    vec4 clip = vec4(WorldPos, 1, 1);

    mat4 inverseProjection = inverse(u_pMatrix);
    mat4 inverseView = inverse(u_vMatrix);

    vec4 view = inverseProjection * clip;
    view /= view.w;

    vec3 rayDir = normalize((inverseView * vec4(view.xyz, 0)).xyz);

    vec3 color = IntegrateAtmosphere(cameraPos, rayDir);

    float sunDisk = pow(max(dot(rayDir, sunDir), 0.0), 5000.0);

    color += vec3(40.0, 38.0, 35.0) * sunDisk;

    color = 1.0 - exp(-color);

    FragColor = vec4(color, 1.0);
}
