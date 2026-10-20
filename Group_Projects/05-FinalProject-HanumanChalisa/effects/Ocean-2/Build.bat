@echo off
if not exist bin mkdir bin

cl.exe /nologo /std:c++17 /MP /EHsc /c /Fo.\bin\ /I ".\include" /I ".\modules" /I ".\effects" Main.cpp modules\Camera\Camera.cpp effects\Skybox\Skybox.cpp effects\Ocean\Ocean.cpp

cl.exe /nologo /Fe:OceanShowcase.exe bin\*.obj /link /LIBPATH:".\lib" glew32.lib opengl32.lib user32.lib gdi32.lib shell32.lib winmm.lib

del /Q bin\*.obj
pause
