// Grestner Wave Program Fragment Shader
#version 450 core

in vec3 worldPos;
in vec3 worldNormal;
in vec3 texCoord;

uniform vec3 cameraPos;
uniform sampler2D waterNormalMap1Sampler;
uniform sampler2D waterNormalMap2Sampler;

// Direction FROM surface TO sun
uniform vec3 lightDir;
uniform float time;

out vec4 Fragcolor;

void main() {
    vec2 uv1 = texCoord.xz * 0.02 + vec2(time * 0.02, time * 0.01);
    vec2 uv2 = texCoord.xz * 0.02 + vec2(-time * 0.01, time * 0.02);

    vec3 n1 = texture(waterNormalMap1Sampler, uv1).rgb * 2.0 - 1.0;
    vec3 n2 = texture(waterNormalMap2Sampler, uv2).rgb * 2.0 - 1.0;

    vec3 ripple = normalize(n1 + n2);

    vec3 N = normalize(worldNormal + ripple * 0.15);

        // vec3 N = normalize(worldNormal);
    vec3 V = normalize(cameraPos - worldPos);
    vec3 L = normalize(lightDir);

    //----------------------------------------------------
    // Water colors
    //----------------------------------------------------

    vec3 deepWater = vec3(0.00, 0.05, 0.12);
    vec3 shallowWater = vec3(0.00, 0.25, 0.45);

    //----------------------------------------------------
    // Diffuse lighting
    //----------------------------------------------------

    float NdotL = max(dot(N, L), 0.0);

    vec3 waterColor = mix(deepWater, shallowWater, NdotL);

    //----------------------------------------------------
    // Blinn-Phong Specular
    //----------------------------------------------------

    vec3 H = normalize(L + V);

    float spec = pow(max(dot(N, H), 0.0), 256.0);

    //----------------------------------------------------
    // Fresnel
    //----------------------------------------------------

    float fresnel = pow(1.0 - max(dot(N, V), 0.0), 5.0);

    //----------------------------------------------------
    // Foam
    //----------------------------------------------------

    float foam = smoothstep(0.85, 1.0, N.y);

    //----------------------------------------------------
    // Final
    //----------------------------------------------------

    vec3 color = waterColor * 0.15 +          // ambient
        waterColor * NdotL * 0.85 +  // diffuse
        vec3(1.0) * spec * 1.5 +     // sun glint
        vec3(0.6, 0.7, 0.8) * fresnel; // horizon reflection

    color = mix(color, vec3(1.0), foam * 0.1);

    Fragcolor = vec4(color, 1.0);
}
