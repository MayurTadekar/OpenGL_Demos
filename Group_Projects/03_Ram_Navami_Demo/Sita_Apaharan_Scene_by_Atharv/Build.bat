cls

cl.exe /c /EHsc OGL.c SitaApaharan_func.c

rc.exe OGL.rc

link.exe OGL.obj SitaApaharan_func.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
