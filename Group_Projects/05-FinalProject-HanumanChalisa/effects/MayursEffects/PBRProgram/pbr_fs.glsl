#version 450 core

out vec4 Fragcolor;

in mat3 TBN;
in vec2 ovTexCoord;
in vec3 FragPos;
in vec3 LightPos;
in vec3 ViewPos;
in vec3 ovNormal;

uniform sampler2D baseImageTexture;
// uniform sampler2D normalMap;
uniform sampler2D roughness;
uniform sampler2D metallic;
uniform sampler2D emmisive;

uniform float radianceU;
uniform float emmissiveStrength;

void main() {
	vec4 albedoSample = texture(baseImageTexture, ovTexCoord);

	if(albedoSample.a < 0.5)
		discard;

	vec3 albedo = albedoSample.rgb;

    // Normal mapping
	// vec3 normal = texture(normalMap, ovTexCoord).rgb;
	// normal = normalize(normal * 2.0 - 1.0);
	vec3 N = ovNormal;//normalize(TBN * normal);

	vec3 L = normalize(LightPos - FragPos);
	vec3 V = normalize(ViewPos - FragPos);
	vec3 H = normalize(L + V);

	float metallicValue = texture(metallic, ovTexCoord).r;
	float roughnessValue = texture(roughness, ovTexCoord).r;

    // Ambient
	vec3 ambient = albedo;// * 0.1;

    // Diffuse
	float NdotL = max(dot(N, L), 0.0);
	vec3 diffuse = albedo * NdotL;

    // Specular
	float shininess = mix(128.0, 4.0, roughnessValue);

	float spec = pow(max(dot(N, H), 0.0), shininess);

	vec3 specularColor = mix(vec3(0.04), albedo, metallicValue);

	vec3 specular = specularColor * spec;

    // Emissive
	vec3 emissiveColor = texture(emmisive, ovTexCoord).rgb * emmissiveStrength;

	vec3 finalColor = ambient +
		(diffuse + specular) * radianceU +
		emissiveColor;

	Fragcolor = vec4(finalColor, 1.0);
}