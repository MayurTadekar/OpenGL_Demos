#version 450 core                         

in vec4 vPosition;                        
in vec4 vColor;                           
in vec3 vNormal;

uniform mat4 u_mMatrix;                 
uniform mat4 u_vMatrix;                 
uniform mat4 u_pMatrix;                 

out vec4 ovColor;
out vec3 ovNormal;

void main(void)                           
{                

        ovNormal = vNormal;

        gl_Position = u_pMatrix * u_vMatrix * u_mMatrix * vPosition;    
        ovColor = vColor;                       
}
