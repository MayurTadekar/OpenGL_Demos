cl.exe /c /EHsc OGL.c Astromedicomp_Text.c
rc.exe OGL.rc
link.exe OGL.obj Astromedicomp_Text.obj OGL.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS 