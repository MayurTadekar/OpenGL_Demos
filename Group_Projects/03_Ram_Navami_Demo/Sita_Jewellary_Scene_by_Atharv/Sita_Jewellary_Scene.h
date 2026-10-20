// header guard
#pragma once

////////////////////////////////// Macro //////////////////////////////////

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent/100.0f)

////////////////////////////////// Function declarations //////////////////////////////////

void NightSky(void);
void Tree(float x_pos, float y_pos, float percentX, float percentY);
void Treeleaves(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue);
void Circle(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue);
void Mountains(float red, float green, float blue);
void Land(void);
void Grass(void);
void RandomGrassGeneration(void);
void GrassBlade(float x_pos, float y_pos, float z_pos);
void Necklace(float x_pos, float y_pos, float percentX, float percentY);
void draw_branch(float x_pos, float y_pos, float percent);
void draw_stem(float x_pos, float y_pos, float percent);
void Stars(void);
void update(void);
void Atharv_Sita_Jewellary_Scene(void);

////////////////////////////////// Variable declarations //////////////////////////////////

struct Curve
{
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
};
float Mxt1[100], Mxt2[100], Mxt3[100], Mxt4[100];
float Myt1[100], Myt2[100], Myt3[100], Myt4[100];
#define NUMBEROFGRASSBLADE 7500
float x_postion[NUMBEROFGRASSBLADE];
float y_postion[NUMBEROFGRASSBLADE];
float z_postion[NUMBEROFGRASSBLADE];
