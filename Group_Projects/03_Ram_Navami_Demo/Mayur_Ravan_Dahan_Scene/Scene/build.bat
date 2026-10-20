cls

cl /EHsc /c OGL.c animation.c ravan.c hand.c arrow.c bow.c animation.c

rc OGL.rc

link OGL.obj ravan.obj hand.obj arrow.obj bow.obj animation.obj OGL.res opengl32.lib user32.lib gdi32.lib glu32.lib /SUBSYSTEM:WINDOWS

OGL.exe

