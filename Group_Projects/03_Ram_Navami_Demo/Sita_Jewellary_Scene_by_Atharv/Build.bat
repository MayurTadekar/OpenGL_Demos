cls

cl.exe /c /EHsc OGL.c Sita_Jewellary_Scene_func.c

rc.exe OGL.rc

link.exe OGL.obj Sita_Jewellary_Scene_func.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
