// Flock Vertex Shader
#version 450 core

in vec3 vPosition;
in vec3 vNormal;

uniform mat4 u_pMatrix;
uniform mat4 u_vMatrix;

struct FlockMember {
        vec4 position;
        vec4 velocity;
};

layout(std430, binding = 0) readonly buffer Birds {
        FlockMember member[];
};

out vec3 Normal;

void main() {
        
        FlockMember bird = member[gl_InstanceID];

        vec3 forward = normalize(bird.velocity.xyz);

        vec3 worldUp = vec3(0.0, 1.0, 0.0);

        if(abs(dot(worldUp, forward)) > 0.99) worldUp = vec3(1.0, 0.0, 0.0);

        vec3 right = normalize(cross(worldUp, forward));
        vec3 up = cross(forward, right);

        mat3 rotation = mat3(right, up, forward);

        vec3 worldPosition = bird.position.xyz + rotation * vPosition;

        gl_Position = u_pMatrix *
                u_vMatrix *
                vec4(worldPosition, 1.0);

        Normal = rotation * vNormal;
}