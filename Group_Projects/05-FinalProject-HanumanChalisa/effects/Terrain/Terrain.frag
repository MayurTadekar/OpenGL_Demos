#version 460 core
precision highp float;

in vec2 Outtexcoords;
in vec3 FragPosition;
in mat3 NormalMatrix;

uniform vec3 uCamPosition;
uniform vec3 uLightDirection;
uniform vec3 uLightColor;

uniform sampler2D uAlbedoMap;
uniform sampler2D uNormalMap;
uniform sampler2D uRoughnessMap;
uniform sampler2D uAmbientOcclusionMap;

out vec4 FragColor;

const float PI = 3.14159265359;

// Functions
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
   float a = roughness * roughness;
   float a2 = a * a;

   float NdotH = max(dot(N, H), 0.0);
   float NdotH2 = NdotH * NdotH;

   float denom = (NdotH2 * (a2 - 1.0) + 1.0);

   return(a2 / (PI * denom * denom));
}

float GeometrySchlickGGX(float NdotVorL, float roughness)
{
   float r = (roughness + 1.0);
   float k = (r * r) / 8.0;

   return(NdotVorL / (NdotVorL * (1.0 - k) + k));
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
   float ggx1 = GeometrySchlickGGX(max(dot(N, V), 0.0), roughness);
   float ggx2 = GeometrySchlickGGX(max(dot(N, L), 0.0), roughness);

   return(ggx1 * ggx2);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
   return(F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0));
}

void main(void)
{
   // Data Extraction from maps
   vec3 terrainColor = textureLod(uAlbedoMap, Outtexcoords, 1.5f).rgb;
   vec3 terrainNormals = textureLod(uNormalMap, Outtexcoords, 1.5f).rgb;  // Keeping Normals in the range [0,1]
   float terrainRoughness = 1.0f - textureLod(uRoughnessMap, Outtexcoords, 1.5f).r;
   float terrainAO = textureLod(uAmbientOcclusionMap, Outtexcoords, 1.5f).r;
   float terrainMetallic = 0.0f;

   // Calculating Normal
   vec3 TransformedNormal = normalize(NormalMatrix * terrainNormals);

   vec3 N = normalize(TransformedNormal);                         // Normal
   vec3 V = normalize(uCamPosition - FragPosition);               // View
   vec3 L = normalize(-uLightDirection);                          // Directional light
   vec3 H = normalize(V + L);                                     // Half

   // Base Reflectivity
   vec3 F0 = vec3(0.04f); // for non metals
   F0 = mix(F0, terrainColor, terrainMetallic); // Based on Metallicness choose your reflectivity

   // Cook Tolerence BRDF
   float NDF = DistributionGGX(N, H, terrainRoughness);              // How are micro-surfaces oriented
   float G = GeometrySmith(N, V, L, terrainRoughness);               // How much light is blocked
   vec3 F = fresnelSchlick(max(dot(H, V), 0.0f), F0);                // How reflective is the surface at this angle

   vec3 numerator = NDF * G * F;
   float denom = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 so that denom will not be 0
   vec3 specular = numerator / denom;

   // Diffuse
   vec3 kS = F;
   vec3 kD = vec3(1.0) - kS;
   kD = kD * (1.0 - terrainMetallic); // Diffuse is inversely related to both specular and metallic

   vec3 diffuse = (kD * terrainColor) / PI; // Lambertian diffuse
   float wrap = 0.2; // try 0.2–0.5
   float NdotL = max((dot(N, L) + wrap) / (1.0 + wrap), 0.0);
   vec3 Lo = (diffuse + specular) * uLightColor * NdotL;

   // Ambient (simple for now)
   vec3 ambient = vec3(0.15) * terrainColor * terrainAO;
   vec3 color = ambient + Lo;

   FragColor = vec4(color, 1.0f);
}
