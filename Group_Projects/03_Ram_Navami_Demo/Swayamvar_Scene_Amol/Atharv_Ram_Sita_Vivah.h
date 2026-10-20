// header guard
#pragma once


/////////////////////////////// Scene Related Variable declaration ///////////////////////////////
struct Curve
{
    float x0, x1, x2, x3;
    float y0, y1, y2, y3;
};

float lowerCurveOfHandX[150];
float lowerCurveOfHandY[150];
float UpperCurveofHandX[150];
float UpperCurveofHandY[150];

// Texture Related variables
int texture_Raj_mahal;

/////////////////////////////// Scene Related Function declaration ///////////////////////////////

void Garland(void);
void HandCurveCalculation(void);
void Hand( float red1, float green1, float blue1, float red2, float green2, float blue2);
void GoldenBraclet(void);
void Atharv_HandsOfRamAndSita(void);
void HandsAnimation(void);
void GarlandAnimation(void);
void BracletAnimation(void);
void shivdhanushya(float x_pos, float y_pos, float percent);
void table(float x_pos, float y_pos, float percent);
void SwayamvarAnimation(void);
void RamSitaVivah(void);
