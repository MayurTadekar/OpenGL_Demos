#pragma once

#define VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0)

// Function Declarations
void SitaHanumanBhet(void);

void drawFace(void);
void drawNose(void);
void drawEyeBrows(void);
void drawEye(void);
void drawHair(void);
void drawCloth(void);
void drawNeck(void);
void drawDress(void);
void drawLowerDress(void);
void drawHandStart(void);
void drawForearm(void);
void drawFoot(void);
void drawBindi(void);
void drawRingStone(float innerRadius, float outerRadius, int segments);
void drawSita(void);
void drawSitaUpper(float innerRadius, float outerRadius, int segments);
void drawHanumanMouthFront(float innerRadius, float outerRadius, int segments);
void drawHanumanMouthBack(float innerRadius, float outerRadius, int segments);
void drawHanumanCrown(void);
void drawHanumanCrownTop(void);
void drawHanumanNewBody(void);

void drawHanuman(void);
void drawHanumanGada(void);
void drawHanumanNewFace(void);

void drawHanumanHand(void);
void drawHanumanForearm(void);
void drawHanumanBody(void);
void drawHanumanNeck(void);
void drawHanumanTail(void);
void drawHanumanEye(void);
void drawHanumanMouth(void);


struct curve_shivkumar
{
    float x0, x1, x2, x3;
    float y0, y1, y2, y3;
};

float Sheput_xt[100];
float Sheput_yt[100];

float SheputTura_xt[100];
float SheputTura_yt[100];

void Sheput(void);
void Sheput_Calculation(void);
void SheputTura_Calculate(void);
void SheputTura(float x_pos, float y_pos, float percentX, float percentY);


struct BigTreeCurve_shivkumar
{
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
};

// For Tree Stem
float BigTxt1[100], BigTxt2[100], BigTxt3[100], BigTxt4[100];
float BigTyt1[100], BigTyt2[100], BigTyt3[100], BigTyt4[100];

//////////////////////////////// Function declaration ////////////////////////////////
void BigTree_shivkumar(float x_pos, float y_pos, float percentX, float percentY);
void BigTreeleaves_shivkumar(float x_pos, float y_pos, float percentX, float percentY, float red, float green, float blue);
void BigTreeCircle_shivkumar(float x_pos, float y_pos, float percentX, float percentY, float radius, float red, float green, float blue);
void BigTreeStem_shivkumar(float x_pos, float y_pos, float percentX, float percentY);


void drawRing(float innerRadius, float outerRadius, int segments);