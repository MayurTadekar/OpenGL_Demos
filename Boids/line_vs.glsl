#version 450 core                         

in vec4 vPosition;                        
in vec4 vColor;                           

uniform mat4 u_mMatrix;                 
uniform mat4 u_vMatrix;                 
uniform mat4 u_pMatrix;             

struct FlockMember {
        vec4 position;
        vec4 velocity;
};

layout(std430, binding = 0) readonly buffer Birds {
        FlockMember member[];
};

out vec4 ovColor;

void main(void)                           
{                                
        FlockMember bird = member[gl_InstanceID];
        
        vec3 forward = normalize(bird.velocity.xyz);

        vec3 worldUp = vec3(0.0, 1.0, 0.0);

        if(abs(dot(worldUp, forward)) > 0.99) worldUp = vec3(1.0, 0.0, 0.0);

        vec3 right = normalize(cross(worldUp, forward));
        vec3 up = cross(forward, right);

        mat3 rotation = mat3(right, up, forward);

        vec3 worldPosition = bird.position.xyz + rotation * vPosition.xyz;

        gl_Position = u_pMatrix * u_vMatrix * u_mMatrix * vec4(worldPosition, 1.0);    
        // gl_Position = u_pMatrix * u_vMatrix * u_mMatrix * vPosition;    
        // gl_Position = u_pMatrix * u_vMatrix * u_mMatrix * (bird.position + vec4(8.0, 0.0, 0.0, 0.0));    
  
        ovColor = vColor;                       
}
