// header guard
#pragma once

//////////////////////////////// Scene related Variable declaration ////////////////////////////////
struct Curve
{
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
};

//////////////////////////////// Function declarations ////////////////////////////////

void Sky(float x_pos, float y_pos, float percentX, float percentY);
void Land(float x_pos, float y_pos, float percentX, float percentY);
void Mountains(float x_pos, float y_pos, float percentX, float percentY);
void Tree(float x_pos, float y_pos, float percentX, float percentY);
void Treeleaves(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue);
void TreeStem(float x_pos, float y_pos, float percentX, float percentY);
void Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue);
void Fence(float x_pos, float y_pos, float percentX, float percentY);
void PushpakViman(float x_pos, float y_pos, float percentX, float percentY);
void RoofForViman(float x_pos, float y_pos, float percentX, float percentY);
void KalashForViman(float x_pos, float y_pos, float percentX, float percentY);
void WingsForViman(float x_pos, float y_pos, float percentX, float percentY, float AnimateY);
void BaseForViman(float x_pos, float y_pos, float percentX, float percentY);
void Necklace(float x_pos, float y_pos, float percentX, float percentY);
void NecklaceMove(void);
void Bangles(float x_pos, float y_pos, float percentX, float percentY);
void BanglesMove(void);
void Atharv_Sita_Apaharan(void);


//////////////////////////////// Macros ////////////////////////////////

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100)
#define TIMER_ID_FOR_PUSHPAK_VIMAN 1234
#define TIMER_ID_FOR_NECKLACE 2345
#define TIMER_ID_FOR_BANGLES 3456

