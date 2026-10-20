// header guard
#pragma once

////////////////////////////////// Macro //////////////////////////////////

#ifndef VALUE_FROM_PERCENT
#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)
#endif
////////////////////////////////// Function declarations //////////////////////////////////


void Atharv_NightSky(void);
void Atharv_Different_Tree(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Different_Treeleaves(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue);
void Atharv_Different_Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue);
void Atharv_Different_Mountains(float red, float green, float blue);
void Atharv_Different_Land(void);
void Atharv_Grass(void);
void Atharv_RandomGrassGeneration(void);
void Atharv_GrassBlade(float x_pos, float y_pos, float z_pos);
void Atharv_Different_Necklace(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_draw_branch(float x_pos, float y_pos, float percent);
void Atharv_draw_stem(float x_pos, float y_pos, float percent);
void Atharv_Stars(void);
void Atharv_update(void);
void Atharv_Sita_Jewellary_Scene(void);


