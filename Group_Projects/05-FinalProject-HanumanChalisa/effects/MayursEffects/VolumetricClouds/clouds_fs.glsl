// Fragment Shader

#version 450 core

in vec2 uv;

uniform vec3 cameraPos;
uniform vec3 boundsMin;
uniform vec3 boundsMax;

uniform mat4 u_viewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform float fTime;
uniform float timeScale;

uniform sampler2D mainTexture;
uniform sampler2D depthTexture;

uniform sampler3D basicCloud;
uniform sampler3D detailCloud;

uniform float cloudScale = 1;
uniform vec3 cloudOffset;//= vec3(0.0);
uniform float densityOffset;
uniform float densityMultiplier;

uniform vec4 phaseParams;// = vec4(0.0);
uniform vec4 params = vec4(1.0);

uniform vec4 lightPos;// = vec4(0.0, 1000.0, 0.0, 1.0);
uniform vec3 lightColor;// = vec3(1.0, 0.95, 0.9);
uniform int numStepsLight = 8;

uniform float lightAbsorptionTowardSun;
uniform float lightAbsorptionThroughCloud;
uniform float darknessThreshold;

uniform vec4 shapeNoiseWeights;

uniform float detailOffset = 1.0;
uniform float detailNoiseScale = 1.0;
uniform float detailNoiseWeight = 1.0;
uniform vec4 detailNoiseWeights = vec4(1.0);

uniform float bottomFadeStart = 0.0;
uniform float bottomFadeEnd = 0.15;

uniform float topFadeStart = 0.7;
uniform float topFadeEnd = 1.0;

out vec4 Fragcolor;

vec2 rayBoxDst(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir) {

    vec3 invDir = 1.0 / rayDir;

    vec3 t0 = (boundsMin - rayOrigin) * invDir;
    vec3 t1 = (boundsMax - rayOrigin) * invDir;

    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);

    float dstA = max(max(tmin.x, tmin.y), tmin.z);
    float dstB = min(min(tmax.x, tmax.y), tmax.z);

    float dstToBox = max(0.0, dstA);
    float dstInsideBox = max(0.0, dstB - dstToBox);

    return vec2(dstToBox, dstInsideBox);
}

float LinearizeDepth(float depth) {
    float near = 1.0;
    float far = 10000.0;

    float z = depth * 2.0 - 1.0;

    return (2.0 * near * far) / (far + near - z * (far - near));
}

float saturate(float x) {
    return clamp(x, 0.0, 1.0);
}
vec2 saturate(vec2 x) {
    return clamp(x, 0.0, 1.0);
}
vec3 saturate(vec3 x) {
    return clamp(x, 0.0, 1.0);
}
vec4 saturate(vec4 x) {
    return clamp(x, 0.0, 1.0);
}

// 1. 3D Hash Function for Pseudo-Random Values
float hash3D(vec3 p) {
    p = fract(p * vec3(443.8975, 397.2973, 491.1871));
    p += dot(p.xyz, p.yzx + 19.19);
    return fract(p.x * p.y * p.z);
}

// 2. Smooth 3D Value Noise
float noise3D(vec3 p) {
    vec3 i = floor(p);
    vec3 f = fract(p);

    // Smoothstep interpolation for organic cloud edges
    vec3 u = f * f * (3.0 - 2.0 * f);

    // Hash values for the 8 corners of the 3D grid cell
    float v000 = hash3D(i + vec3(0.0, 0.0, 0.0));
    float v100 = hash3D(i + vec3(1.0, 0.0, 0.0));
    float v010 = hash3D(i + vec3(0.0, 1.0, 0.0));
    float v110 = hash3D(i + vec3(1.0, 1.0, 0.0));
    float v001 = hash3D(i + vec3(0.0, 0.0, 1.0));
    float v101 = hash3D(i + vec3(1.0, 0.0, 1.0));
    float v011 = hash3D(i + vec3(0.0, 1.0, 1.0));
    float v111 = hash3D(i + vec3(1.0, 1.0, 1.0));

    // Trilinear interpolation
    return mix(mix(mix(v000, v100, u.x), mix(v010, v110, u.x), u.y), mix(mix(v001, v101, u.x), mix(v011, v111, u.x), u.y), u.z);
}

// 3. Fractal Brownian Motion (FBM) to build cloud fluffiness
#define NUM_OCTAVES 2
float fbm(vec3 p) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;

    for(int i = 0; i < NUM_OCTAVES; i++) {
        value += amplitude * noise3D(p * frequency);
        frequency *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

// Henyey-Greenstein
float hg(float a, float g) {
    float g2 = g * g;
    return (1 - g2) / (4 * 3.1415 * pow(1 + g2 - 2 * g * (a), 1.5));
}

float phase(float a) {
    float blend = .5;
    float hgBlend = hg(a, phaseParams.x) * (1 - blend) + hg(a, -phaseParams.y) * blend;
    return phaseParams.z + hgBlend * phaseParams.w;
}

float beer(float d) {
    float beer = exp(-d);
    return beer;
}

float sampleDensity(vec3 raypos) {
    // vec3 uvw = position * cloudScale * 0.001 + cloudOffset * 0.01;
    // vec3 shape = texture(basicCloud, uvw).rgb;
    // float density = max(0, shape.r - densityThreshold) * densityMultiplier;
    // return (density);

    // Constants
    const int mipLevel = 0;
    const float baseScale = 1 / 1000.0;
    const float offsetSpeed = 1 / 1000.0;

    // Calculate texture sample positions
    float time = fTime * timeScale;
    vec3 size = boundsMax - boundsMin;
    vec3 boundsCenter = (boundsMin + boundsMax) * 0.5;

    vec3 uvw = raypos * cloudScale * 0.01;// + cloudOffset * 0.01;//(raypos - boundsMin) / (boundsMax - boundsMin);

    vec3 shapeSamplePos = uvw + cloudOffset * offsetSpeed + vec3(time, time * 0.1, time * 0.2) * 1.0;//baseSpeed;

    // Calculate falloff at along x/z edges of the cloud container
    const float containerEdgeFadeDst = 50;
    float dstFromEdgeX = min(containerEdgeFadeDst, min(raypos.x - boundsMin.x, boundsMax.x - raypos.x));
    float dstFromEdgeZ = min(containerEdgeFadeDst, min(raypos.z - boundsMin.z, boundsMax.z - raypos.z));
    float edgeWeight = min(dstFromEdgeZ, dstFromEdgeX) / containerEdgeFadeDst;

    // Calculate base shape density
    shapeSamplePos = fract(shapeSamplePos);
    vec4 shapeNoise = texture(basicCloud, shapeSamplePos);
    vec4 normalizedShapeWeights = shapeNoiseWeights / dot(shapeNoiseWeights, vec4(1.0));
    float shapeFBM = dot(shapeNoise, normalizedShapeWeights);
    float baseShapeDensity = shapeFBM + densityOffset * 0.1;//max(0, shape.r - densityThreshold) * densityMultiplier;
    float height01 = saturate((raypos.y - boundsMin.y) / (boundsMax.y - boundsMin.y));

    // float bottomFade = smoothstep(0.0, 0.15, height01);

    // float topFade = 1.0 - smoothstep(0.7, 1.0, height01);
    float bottomFade = smoothstep(bottomFadeStart, bottomFadeEnd, height01);

    float topFade = 1.0 - smoothstep(topFadeStart, topFadeEnd, height01);

    float heightWeight = bottomFade * topFade;

    baseShapeDensity *= heightWeight;
    baseShapeDensity *= edgeWeight;

    if(baseShapeDensity > 0) {

        vec3 detailSamplePos = uvw * detailNoiseScale + detailOffset * offsetSpeed + vec3(time, time * 0.1, time * 0.2) * 1.0;
        vec4 detailNoise = texture(detailCloud, detailSamplePos);
        vec4 normalizedDetailWeights = detailNoiseWeights / dot(detailNoiseWeights, vec4(1.0));
        float detailFBM = dot(detailNoise, normalizedDetailWeights);

        // float oneMinus = 1 - shapeFBM;
        // float detailErodeWeight = oneMinus * oneMinus * oneMinus;
        float detailErodeWeight = pow(1.0 - baseShapeDensity, 4.0);

        float cloudDensity = baseShapeDensity - (1 - detailFBM) * detailErodeWeight * detailNoiseWeight;

        // cloudDensity = pow(cloudDensity, 4.0);
        // cloudDensity = smoothstep(0.3, 0.8, cloudDensity);
        cloudDensity = smoothstep(0.15, 0.75, cloudDensity);
        cloudDensity = pow(cloudDensity, 1.5);

        return (cloudDensity * densityMultiplier * 0.1);
    }

    return (baseShapeDensity);
}

float lightMarch(vec3 p) {

    // vec3 dirToLight = lightPos.xyz;
    vec3 dirToLight = normalize(lightPos.xyz - p);
    vec2 rayBoxInfo = rayBoxDst(boundsMin, boundsMax, p, dirToLight);
    float dstInsideBox = rayBoxInfo.y;

    float transmittance = 1;
    float stepSize = dstInsideBox / numStepsLight;
    p += dirToLight * stepSize * 0.5;

    float totalDensity = 0;

    for(int step = 0; step < numStepsLight; step++) {
        float density = sampleDensity(p);
        totalDensity += max(0, density * stepSize);
        p += dirToLight * stepSize;
    }

    transmittance = beer(totalDensity * lightAbsorptionTowardSun);

    float clampedTransmittance = darknessThreshold + transmittance * (1 - darknessThreshold);
    return clampedTransmittance;
}

void main(void) {
    vec2 screenUV = uv;

    // vec2 ndc = screenUV * 2.0 - 1.0;

    mat4 invProjection = inverse(u_ProjectionMatrix);
    mat4 invView = inverse(u_viewMatrix);

    // vec4 clip = vec4(ndc, 1.0, 1.0);

    // vec4 view = invProjection * clip;
    // view /= view.w;

    // vec3 rayDir = normalize((invView * vec4(view.xyz, 0.0)).xyz);
    // vec3 rayOrigin = cameraPos;

    // vec2 rayBoxInfo = rayBoxDst(boundsMin, boundsMax, rayOrigin, rayDir);
    // float dstToBox = rayBoxInfo.x;
    // float dstInsideBox = rayBoxInfo.y;

    // vec4 texColor = texture(mainTexture, screenUV);
    // float depthColor = texture(depthTexture, screenUV).r;
    // depthColor = LinearizeDepth(depthColor);

    // bool inBox = dstInsideBox > 0.0 && dstToBox < depthColor;

    vec4 clipPos;
    clipPos.xy = screenUV * 2.0 - 1.0;
    clipPos.z = texture(depthTexture, screenUV).r * 2.0 - 1.0;
    clipPos.w = 1.0;

    vec4 viewPos = inverse(u_ProjectionMatrix) * clipPos;
    viewPos /= viewPos.w;

    vec4 worldPos = inverse(u_viewMatrix) * viewPos;

    float sceneDistance = length(worldPos.xyz - cameraPos);

    vec3 rayDir = normalize(worldPos.xyz - cameraPos);

    vec3 rayOrigin = cameraPos;

    vec2 rayBoxInfo = rayBoxDst(boundsMin, boundsMax, rayOrigin, rayDir);

    float dstToBox = rayBoxInfo.x;
    float dstInsideBox = rayBoxInfo.y;

    vec4 texColor = texture(mainTexture, screenUV);
    // float depthColor = texture(depthTexture, screenUV).r;
    // depthColor = LinearizeDepth(depthColor);

    // bool inBox = dstInsideBox > 0.0 && dstToBox < sceneDistance;

    // if(!inBox) {
    //     Fragcolor = vec4(texColor);
    //     return;
    // }

    vec3 entryPoint = rayOrigin + rayDir * dstToBox;

    vec3 lightDir = normalize(lightPos.xyz - entryPoint);
    float cosAngle = dot(rayDir, lightDir);
    float phaseVal = phase(cosAngle);

    // float dstTravelled = 0;
    float dstLimit = min(sceneDistance - dstToBox, dstInsideBox);

    float stepCount = mix(32.0, 128.0, saturate(dstInsideBox / 500.0));
    // float stepSize = dstInsideBox / stepCount;
    float stepSize = dstLimit / stepCount;

    float jitter = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453);

    float dstTravelled = jitter * 0.5;

    float transmittance = 1;
    vec3 lightEnergy = vec3(0.0);

    while(dstTravelled < dstLimit) {
        rayOrigin = entryPoint + rayDir * dstTravelled;
        float density = sampleDensity(rayOrigin);

        if(density > 0) {
            float lightTransmittance = lightMarch(rayOrigin);
            lightEnergy += density * stepSize * transmittance * lightTransmittance * phaseVal * lightColor;
            transmittance *= exp(-density * lightAbsorptionThroughCloud * stepSize);

            if(transmittance < 0.01)
                break;
        }

        dstTravelled += stepSize;
    }
    // Fragcolor = vec4(lightEnergy, 1.0);

     // Composite sky + background
    vec3 backgroundCol = texColor.xyz;
    // float dstFog = 1 - exp(-max(0, depthColor) * 8 * .0001);
    // vec3 sky = dstFog * vec3(0.0, 1.0, 1.0);
    // backgroundCol = backgroundCol * (1 - dstFog) + sky;

    // Sun
    float focusedEyeCos = pow(saturate(cosAngle), params.x);
    float sun = saturate(hg(focusedEyeCos, 0.75)) * transmittance;

    // Add clouds
    vec3 cloudCol = lightEnergy * vec3(1.0);
    vec3 col = backgroundCol * transmittance + cloudCol;// * (1.0 - transmittance);
    // col = saturate(col) * (1 - sun) + vec3(1.0) * sun;
    Fragcolor = vec4(col, 1);
}
