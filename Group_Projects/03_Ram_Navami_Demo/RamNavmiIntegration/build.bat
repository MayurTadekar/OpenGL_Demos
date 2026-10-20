del *.exe
del *.obj
cls

cl.exe /c /EHsc Integration.c GuruShishya_Adesh_func.c SitaApaharan_func.c Ram_Janm.c vanvas.c Ganpati_Text.c Astromedicomp_Text.c Omkar_Texture_Text.c Shashwat_Omkar.c GauriRamMandirFunc.c 

link.exe Integration.obj GuruShishya_Adesh_func.obj SitaApaharan_func.obj Ram_Janm.obj vanvas.obj Ganpati_Text.obj Astromedicomp_Text.obj Omkar_Texture_Text.obj Shashwat_Omkar.obj GauriRamMandirFunc.obj user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

