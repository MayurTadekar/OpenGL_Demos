// LitSabhamandap Fragment Shader

#version 460 core
in vec2 oTexCoord;
in vec3 oNormal;
in vec3 oFragPos;

uniform sampler2D uTextureSampler;
uniform vec3 uCameraPos;
uniform int uEnableLighting;

uniform sampler2D hanumanShadowTexture;
uniform int hanumanShadowPower;
uniform int showHanumanShadow = 0;

uniform sampler2D vibhishanShadowTexture;
uniform int vibhishanShadowPower;
uniform int showVibhishanShadow = 0;

uniform sampler2D sabhamandapShadowTexture;
uniform int sabhamandapShadowPower;
uniform int showFirePotShadow = 0;

uniform sampler2D ministerChairShadowTexture;
uniform int ministerChairShadowPower;
uniform int showMinisterChairShadow = 0;

uniform sampler2D pillarShadowTexture;
uniform int pillarShadowPower;
uniform int showPillarShadow = 0;

in vec4 hanumanShadowLightSpacePos;
in vec4 vibhishanShadowLightSpacePos;
in vec4 sabhamandapShadowLightSpacePos;
in vec4 ministerChairLightSpacePos;
in vec4 pillarChairLightSpacePos;

struct Light {
	int bEnable;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
	float intensity;
	float constant;
	float linear;
	float quadratic;
};
uniform Light uLights[3];

out vec4 FragColor;

vec3 CalcLight(Light L, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 texCol) {
	if(L.bEnable == 0)
		return vec3(0.0);

	vec3 lightDir = normalize(L.position - fragPos);

	float dist = length(L.position - fragPos);
	float att = 1.0 / (L.constant + L.linear * dist + L.quadratic * dist * dist);

	vec3 ambient = L.ambient * texCol;

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = L.diffuse * diff * texCol;

	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfDir), 0.0), L.shininess);
	vec3 specular = L.specular * spec;

	return (ambient + diffuse + specular) * att * L.intensity;
}

vec3 CalcShadowCoords(vec4 pos) {
	vec3 ProjCoords = pos.xyz / pos.w;
	vec3 ShadowCoords = ProjCoords * 0.5 + vec3(0.5);
	return ShadowCoords;
}

void main(void) {
	vec4 texColor = texture(uTextureSampler, oTexCoord);

	if(uEnableLighting == 0) {
		FragColor = texColor;
		return;
	}

	vec3 norm = normalize(oNormal);
	vec3 viewDir = normalize(uCameraPos - oFragPos);
	vec3 texCol = texColor.rgb;

	vec3 result = vec3(0.0);
	result += CalcLight(uLights[0], norm, oFragPos, viewDir, texCol); // Key
	result += CalcLight(uLights[1], norm, oFragPos, viewDir, texCol); // Fill
	result += CalcLight(uLights[2], norm, oFragPos, viewDir, texCol); // Back

	result += texCol * 0.03;

	float hanumanDepth = texture(hanumanShadowTexture, CalcShadowCoords(hanumanShadowLightSpacePos).xy).r;
	float vibhishanDepth = texture(vibhishanShadowTexture, CalcShadowCoords(vibhishanShadowLightSpacePos).xy).r;
	float sabhamandapDepth = texture(sabhamandapShadowTexture, CalcShadowCoords(sabhamandapShadowLightSpacePos).xy).r;
	float ministerChairDepth = texture(ministerChairShadowTexture, CalcShadowCoords(ministerChairLightSpacePos).xy).r;
	float pillarChairDepth = texture(pillarShadowTexture, CalcShadowCoords(pillarChairLightSpacePos).xy).r;

	float compositeShadow = 1.0;

	if(showHanumanShadow == 1)
		compositeShadow = min(compositeShadow, pow(hanumanDepth, float(hanumanShadowPower)));

	if(showVibhishanShadow == 1)
		compositeShadow = min(compositeShadow, pow(vibhishanDepth, float(vibhishanShadowPower)));

	if(showFirePotShadow == 1)
		compositeShadow = min(compositeShadow, pow(sabhamandapDepth, float(sabhamandapShadowPower)));

	if(showMinisterChairShadow == 1)
		compositeShadow = min(compositeShadow, pow(ministerChairDepth, float(ministerChairShadowPower)));

	if(showPillarShadow == 1)
		compositeShadow = min(compositeShadow, pow(pillarChairDepth, float(pillarShadowPower)));

	// FragColor = vec4(result, texColor.a);
	FragColor = vec4(result * vec3(compositeShadow), texColor.a);

}