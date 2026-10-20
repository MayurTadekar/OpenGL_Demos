cls

cl.exe /c /DNDEBUG=1 /EHsc /I C:\freeglut\include Main.c

link.exe Main.obj /LIBPATH:C:\freeglut\lib\x64 /SUBSYSTEM:CONSOLE