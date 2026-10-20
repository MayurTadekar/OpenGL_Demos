// header guard
#pragma once

//////////////////////////////// Scene related Variable declaration ////////////////////////////////
struct Curve
{
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
};

//////////////////////////////// Function declarations ////////////////////////////////

void Atharv_Sky(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Land(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Mountains(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Tree(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Treeleaves(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue);
void Atharv_TreeStem(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue);
void Atharv_Fence(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_PushpakViman(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_RoofForViman(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_KalashForViman(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_WingsForViman(float x_pos, float y_pos, float percentX, float percentY, float AnimateY);
void Atharv_BaseForViman(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_Necklace(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_NecklaceMove(void);
void Atharv_Bangles(float x_pos, float y_pos, float percentX, float percentY);
void Atharv_BanglesMove(void);
void Atharv_Sita_Apaharan(void);
void Atharv_PushpakVimanUpdate(void);


//////////////////////////////// Macros ////////////////////////////////
#ifndef VALUE_FROM_PERCENT
#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100)
#endif
#define TIMER_ID_FOR_PUSHPAK_VIMAN 1234
#define TIMER_ID_FOR_NECKLACE 2345
#define TIMER_ID_FOR_BANGLES 3456