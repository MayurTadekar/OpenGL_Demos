
cls

cl /EHsc /c window.cpp camera.cpp TextureLoader.cpp /std:c++17 /I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.4\include"

nvcc -c flock_cuda.cu

link window.obj camera.obj flock_cuda.obj TextureLoader.obj imgui.obj imgui_demo.obj imgui_draw.obj imgui_tables.obj imgui_widgets.obj imgui_impl_opengl3.obj imgui_impl_win32.obj user32.lib gdi32.lib opengl32.lib glew32.lib ole32.lib windowscodecs.lib assimp.lib /LIBPATH:"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.4\lib\x64" cudart.lib /SUBSYSTEM:WINDOWS

@REM  window.exe
