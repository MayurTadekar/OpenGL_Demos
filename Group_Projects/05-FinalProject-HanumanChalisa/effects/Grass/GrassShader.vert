#version 460 core

in vec4 aPosition;
in float aAnimationTime;
out float oAnimationTime;
                                                            
void main(void)                                                             
{
    gl_Position = aPosition;
    oAnimationTime = aAnimationTime;
}
