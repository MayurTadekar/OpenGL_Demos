cls
del *.obj
del *.exe
del *.res

cl.exe /c /EHsc OGL.c vanvas.c
rc.exe OGL.rc
link.exe OGL.obj vanvas.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

OGL.exe