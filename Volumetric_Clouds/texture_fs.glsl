#version 450 core                             

in vec2 ovTexcoord;

uniform sampler3D u_TextureSampler;

out vec4 Fragcolor;

uniform float zSlice = 0.5;

void main(void) {

        vec3 uvw = vec3(ovTexcoord, zSlice);

        vec3 texColor = texture(u_TextureSampler, uvw).rgb;

        float r = texColor.r;

        Fragcolor = vec4(vec3(r), 1.0);
}
