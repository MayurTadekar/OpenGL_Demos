#version 450 core                             

in vec2 ovTexcoord;

uniform sampler2D u_TextureSampler;

out vec4 Fragcolor;

void main(void) {
        vec4 texColor = texture(u_TextureSampler, ovTexcoord);

        Fragcolor = texColor;
}
