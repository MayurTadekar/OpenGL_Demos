cl.exe /c /EHsc OGL.c Omkar_Texture_Text.c
rc.exe OGL.rc
link.exe OGL.obj Omkar_Texture_Text.obj OGL.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS 