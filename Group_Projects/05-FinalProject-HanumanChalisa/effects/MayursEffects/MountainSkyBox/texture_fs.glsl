// Texture Program FS
#version 450 core                             

in vec2 ovTexcoord;

uniform sampler2D u_TextureSampler;

out vec4 Fragcolor;

void main(void) {

        vec4 col = texture(u_TextureSampler, ovTexcoord);

        if(col.a < 0.1)
                discard;

        Fragcolor = col;
}
