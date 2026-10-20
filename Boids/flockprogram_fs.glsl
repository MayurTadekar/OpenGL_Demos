#version 450 core

in vec3 Normal;

out vec4 FragColor;

void main() {
        vec3 N = normalize(Normal);

        float lighting = max(dot(N, normalize(vec3(1.0, 1.0, 1.0))), 0.2);

        FragColor = vec4(vec3(lighting), 1.0);
}
