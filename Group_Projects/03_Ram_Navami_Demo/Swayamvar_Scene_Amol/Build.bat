cl.exe /c /EHsc OGL.c Atharv_Ram_Sita_Vivah_func.c
rc.exe OGL.rc
link.exe OGL.obj Atharv_Ram_Sita_Vivah_func.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
