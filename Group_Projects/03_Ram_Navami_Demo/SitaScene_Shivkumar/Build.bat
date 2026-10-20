cl.exe /c /EHsc OGL.c hanumansita_bhet.c
rc.exe OGL.rc   
link.exe OGL.obj hanumansita_bhet.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
