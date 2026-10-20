cl.exe /c /EHsc OGL.c Ram_Janm_func.c
rc.exe OGL.rc
link.exe OGL.obj Ram_Janm_func.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
