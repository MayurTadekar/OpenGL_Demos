// ####### FRAGMENT SHADER  ####### 

#version 450 core

out vec4 FragColor;

uniform float iTime = 1.0;
uniform float fireSize = 0.5;
uniform float speed = 0.0;   // 0.0 -> 1.0
uniform float flameRadius = 1.0;
uniform float flameIntensity = 1.0;

uniform float intensityMultiplier = 0.05;
uniform vec3 flameColor = vec3(1.0, 0.1, 0.1);

in vec3 viewPos;
in vec2 ovUV;
in vec2 localUV;

#define rotate(angle) *= mat2(cos(angle + vec4(0,33,11,0))),

void main() {
    float raySteps = 0.0;
    float rayDistance = 0.0;
    float octaveIndex = 0.0;
    float sdfDistance = 0.0;
    float noiseScale = 0.0;
    float fireIntensity = 0.0;
    float minDistance = 1.0;
    float flameHeight = 30.0;

    vec3 rotatedPos;
    vec3 timeAnimatedPos;
    vec3 rayPos;

    vec2 uv = localUV;

    vec3 rayOrigin = viewPos;
    vec3 rayDirection = normalize(vec3(uv, 1.0));

    for(; raySteps++ < 50.0 &&
            minDistance > 0.001; fireIntensity += minDistance > sdfDistance ? (minDistance = abs(sdfDistance) * 0.4 + 0.05, 1.0 / minDistance) : exp(2.0 - length(rayPos)) * 0.3, rayDistance += minDistance * 0.5) {
        rayPos = rayOrigin + rayDirection * rayDistance;

        // Flame position
        rayPos.y += 14.0;
        rayPos.z -= 20.0;

        // Stretch flame when moving fast
        rayPos.y /= (1.0 + speed * 4.0);

        minDistance = rayPos.y;

        noiseScale = 0.0025;
        octaveIndex = 0.0;

        // Narrow flame at high speed
        // float width = mix(1.0, 0.4, speed);

        // sdfDistance = 0.96 * length(rayPos.xz) / width - 0.2 * minDistance - fireSize;

        float width = mix(flameRadius, flameRadius * 0.4, speed);

        sdfDistance = 0.96 * length(rayPos.xz) / width - 0.2 * minDistance - fireSize;

        for(; octaveIndex++ < 9.0; noiseScale += noiseScale) {
            rotatedPos = rayPos;

            rotatedPos.zx rotate(octaveIndex * 2.4) timeAnimatedPos = rotatedPos;

            // Faster turbulence at higher speed
            timeAnimatedPos.y -= octaveIndex *
                iTime *
                (1.0 + speed * 5.0);

            sdfDistance += abs(dot(sin(timeAnimatedPos * 0.7 / noiseScale), vec3(noiseScale)));

            float topFade = smoothstep(flameHeight, flameHeight - 1.0, minDistance);

            sdfDistance += (1.0 - topFade) * 5.0;

            rotatedPos.z -= 5.0;

            rotatedPos.zy rotate(atan(octaveIndex * 0.18)) minDistance *= 1.0;
        }
    }

    fireIntensity *= intensityMultiplier;

    vec4 flame = tanh(fireIntensity * vec4(9.0, 1.0, 1.0, fireIntensity) / 500.0);

    FragColor = vec4(flame.rgb * (flameColor * 10.0), flame.a);
}

// ####### FRAGMENT SHADER  ####### 

// #version 450 core  

// out vec4 FragColor;

// uniform float iTime;

// uniform float fireSize = 0.1;

// in vec3 viewPos;          // Fragment position in view space
// in vec2 ovUV;

// in vec2 localUV;

// // Rotate vector.xz by angle
// #define rotate(angle) *= mat2(cos(angle + vec4(0,33,11,0))),

// void main() {
//     vec2 pixelCoord = gl_FragCoord.xy;

//     float raySteps = 0.0;
//     float rayDistance = 0.0;
//     float octaveIndex = 0.0;
//     float sdfDistance = 0.0;
//     float noiseScale = 0.0;
//     float fireIntensity = 0.0;
//     float minDistance = 1.0;
//     float flameHeight = 30.0;

//     vec3 rotatedPos, timeAnimatedPos, rayPos;

//     vec2 uv = ovUV * 2.0 - 1.0;

//     // Ray origin and direction in screen space
//     vec3 rayOrigin = vec3(0.0);  // Origin at camera
//     // vec3 rayDirection = normalize(vec3(pixelCoord + pixelCoord - iResolution.xy, iResolution.y));
//     // vec3 rayDirection = normalize(vec3(uv, 1.0));
//     vec3 rayDirection = normalize(viewPos);

//     // Main raymarching loop
//     for(; raySteps++ < 50.0 && minDistance > 0.001; fireIntensity += minDistance > sdfDistance ? (minDistance = abs(sdfDistance) * 0.4 + 0.05, 1.0 / minDistance) : exp(2.0 - length(rayPos) * 1.0) * 0.3, rayDistance += minDistance * 0.5) {
//         // Raymarch along the ray direction in screen space
//         rayPos = rayOrigin + rayDirection * rayDistance;

//         // Apply ray offset for fire positioning
//         minDistance = rayPos.y += 14.0;
//         rayPos.z += 100.0;

//         // Perturbation/noise octave loop
//         noiseScale = 0.0025;
//         octaveIndex = 0.0;

//         // Base signed distance function for fire shape (flame-like)
//         sdfDistance = 0.4 * length(rayPos.xz) + 0.2 * minDistance - fireSize;//5.34;

//         // Accumulate noise/perturbation for multiple octaves
//         for(; octaveIndex++ < 9.0; noiseScale += noiseScale) {

//             rotatedPos = rayPos;

//             // First rotation on xz plane
//             rotatedPos.zx rotate(octaveIndex * 2.4) timeAnimatedPos = rotatedPos;

//             // Apply time-based animation to y
//             timeAnimatedPos.y -= octaveIndex * iTime;

//             // Accumulate noise/perturbation
//             sdfDistance += abs(dot(sin(timeAnimatedPos * 0.7 / noiseScale), timeAnimatedPos - timeAnimatedPos + noiseScale));

//             float topFade = smoothstep(flameHeight, flameHeight - 1.0, minDistance);

//             sdfDistance += (1.0 - topFade) * 5.0;

//             rotatedPos.z -= 5.0;

//             // Second rotation on zy plane
//             rotatedPos.zy rotate(atan(octaveIndex * 0.18))

//             // Soften distance field instead of hard geometry
//             minDistance *= 1.0;
//         }
//     }

//     // Convert accumulated intensity to final fire color (hot to cool)
//     FragColor = tanh(fireIntensity * vec4(9, 3, 1, fireIntensity) / 500.0);

// }
