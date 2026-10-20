cls
cl.exe /c /EHsc OGL.c Shashwat_Omkar.c
rc.exe OGL.rc
link.exe OGL.obj Shashwat_Omkar.obj OGL.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS 