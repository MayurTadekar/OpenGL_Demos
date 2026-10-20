#version 450 core  

out vec4 Fragcolor;

in  vec3 ovNormal;
in  vec4 ovColor;

void main(void)
{   
        vec3 N = normalize(ovNormal);

        float lighting = max(dot(N, normalize(vec3(1.0, 1.0, 1.0))), 0.2);

        Fragcolor = vec4(vec3(lighting), 1.0) * ovColor;
}
