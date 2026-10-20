del *.exe
del *.obj
cls

cl.exe /c /EHsc OGL.c GauriRamMandirFunc.c

rc.exe OGL.rc

link.exe OGL.obj GauriRamMandirFunc.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

OGL.exe