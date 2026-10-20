cls

del *.obj

del *.exe

del *.res


cl.exe /c /EHsc GuruShishya_Adesh.c GuruShishya_Adesh_func.c

rc.exe GuruShishya_Adesh.rc

link.exe GuruShishya_Adesh.obj GuruShishya_Adesh_func.obj GuruShishya_Adesh.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

