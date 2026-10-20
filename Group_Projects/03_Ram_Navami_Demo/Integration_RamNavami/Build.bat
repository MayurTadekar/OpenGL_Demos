cls

cl.exe /c /EHsc OGL.c Ganpati_Text.c Astromedicomp_Text.c Omkar_Texture_Text.c Shashwat_Omkar.c Ram_Janm_func.c GuruShishya_Adesh_func.c Atharv_Ram_Sita_Vivah_func.c vanvas.c SitaApaharan_func.c Sita_Jewellary_Scene_func.c hanumansita_bhet.c animation.c arrow.c bow.c hand.c ravan.c GauriRamMandirFunc.c EndCredit_Func.c

rc.exe OGL.rc

link.exe OGL.obj Ganpati_Text.obj Astromedicomp_Text.obj Omkar_Texture_Text.obj Ram_Janm_func.obj GuruShishya_Adesh_func.obj Atharv_Ram_Sita_Vivah_func.obj Shashwat_Omkar.obj vanvas.obj SitaApaharan_func.obj Sita_Jewellary_Scene_func.obj hanumansita_bhet.obj animation.obj arrow.obj bow.obj hand.obj ravan.obj GauriRamMandirFunc.obj EndCredit_Func.obj OGL.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS
