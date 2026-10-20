
cls

cl /EHsc /c window.cpp camera.cpp imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_opengl3.cpp imgui_impl_win32.cpp

link window.obj camera.obj imgui.obj imgui_demo.obj imgui_draw.obj imgui_tables.obj imgui_widgets.obj imgui_impl_opengl3.obj imgui_impl_win32.obj user32.lib gdi32.lib opengl32.lib glew32.lib /SUBSYSTEM:WINDOWS

window.exe
