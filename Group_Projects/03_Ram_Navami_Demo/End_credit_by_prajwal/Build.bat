cls

cl.exe /c /EHsc OGL.c EndCredit_Func.c

rc.exe OGL.rc

link.exe OGL.obj EndCredit_Func.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
