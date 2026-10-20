cls

cl /EHsc /c /DNDEBUG=1 code.c

link code.obj user32.lib gdi32.lib 

code.exe
