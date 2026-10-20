#version 450 core

in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec2 vTexCoord;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform vec4 u_LightPosition;

// out vec3 transformed_normal;
// out vec3 light_direction;
// out vec3 view_vector;
// out vec2 ovTexCoord;

// void main(void) {

// 	vec4 eye_coord = u_viewMatrix * u_modelMatrix * vPosition;
// 	transformed_normal = mat3(u_viewMatrix * u_modelMatrix) * vNormal;
// 	light_direction = vec3(u_LightPosition - eye_coord);
// 	view_vector = -eye_coord.xyz;
// 	gl_Position = u_ProjectionMatrix * u_viewMatrix * u_modelMatrix * vPosition;
// 	ovTexCoord = vTexCoord;
// }

out mat3 TBN;
out vec2 ovTexCoord;
out vec3 FragPos;
out vec3 LightPos;
out vec3 ViewPos;

void main() {
	mat3 normalMatrix = transpose(inverse(mat3(u_viewMatrix * u_modelMatrix)));

	vec3 T = normalize(normalMatrix * vTangent);

	vec3 N = normalize(normalMatrix * vNormal);

	T = normalize(T - dot(T, N) * N);

	vec3 B = cross(N, T);

	TBN = mat3(T, B, N);

	vec4 eyePos = u_viewMatrix * u_modelMatrix * vPosition;

	FragPos = eyePos.xyz;
	LightPos = vec3(u_viewMatrix * u_modelMatrix * u_LightPosition);
	ViewPos = vec3(0.0);

	ovTexCoord = vTexCoord;

	gl_Position = u_ProjectionMatrix * eyePos;
}
