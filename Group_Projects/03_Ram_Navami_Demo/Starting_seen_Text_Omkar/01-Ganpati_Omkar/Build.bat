cl.exe /c /EHsc OGL.c Ganpati_Text.c
rc.exe OGL.rc
link.exe OGL.obj Ganpati_Text.obj OGL.res User32.lib GDI32.LIB /SUBSYSTEM:WINDOWS 