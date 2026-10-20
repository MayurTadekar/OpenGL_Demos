cls

cl /EHsc /c /DNDEBUG=1 Integration.c

link Integration.obj user32.lib gdi32.lib winmm.lib

Integration.exe