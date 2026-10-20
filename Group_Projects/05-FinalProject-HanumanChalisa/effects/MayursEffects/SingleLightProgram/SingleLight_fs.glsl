#version 450 core

out vec4 Fragcolor;

in mat3 TBN;
in vec2 ovTexCoord;
in vec3 FragPos;
in vec3 LightPos;
in vec3 ViewPos;

uniform vec3 u_la;
uniform vec3 u_ld;
uniform vec3 u_ls;

uniform vec3 u_ka;
uniform vec3 u_kd;
uniform vec3 u_ks;

uniform float u_kshiny;

uniform sampler2D baseImageTexture;
uniform sampler2D normalMap;

void main() {
    // Normal from normal map
	vec3 normal = texture(normalMap, ovTexCoord).rgb;

	normal = normalize(normal * 2.0 - 1.0);

    // Tangent space -> Eye space
	normal = normalize(TBN * normal);

	vec3 lightDir = normalize(LightPos - FragPos);

	vec3 viewDir = normalize(ViewPos - FragPos);

	vec3 reflectDir = reflect(-lightDir, normal);

	vec3 ambient = u_la * u_ka;

	vec3 diffuse = u_ld * u_kd * max(dot(normal, lightDir), 0.0);

	vec3 specular = u_ls * u_ks * pow(max(dot(reflectDir, viewDir), 0.0), u_kshiny);

	vec3 lighting = ambient + diffuse + specular;

	vec3 albedo = texture(baseImageTexture, ovTexCoord).rgb;

	Fragcolor = vec4(albedo * lighting, 1.0);
}
