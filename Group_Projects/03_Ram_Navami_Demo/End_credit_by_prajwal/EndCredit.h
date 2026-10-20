// header guard
#pragma once

/////////////////////// Macro ///////////////////////

#define VALUE_FROM_PERCENT(complete, percent) (complete * percent / 100)

/////////////////////// Variable Declarations ///////////////////////

int baseFont;

struct curve
{
    float x0, x1, x2, x3;
    float y0, y1, y2, y3;
};

float Nod_xt[100];
float Nod_yt[100];

float NodTura_xt[100];
float NodTura_yt[100];

void Nod(void);
void Nod_Calculation(void);
void NodTura_Calculate(void);
void NodTura(float x_pos, float y_pos, float percentX, float percentY);


/////////////////////// Function Declarations ///////////////////////

void Lakhota(float x_pos, float y_pos, float percent, float FadeFactor);
void RenderText(const char* text);
void Lakhota_Gattu(float x_pos, float y_pos, float percentX);
void Lakhota_Gattu_Right(float x_pos, float y_pos, float percentX);
void Prajwal_EndCredit(void);
void GroupMembersNames(void);
void SpecialThanksNames(void);
void TechnologyUsedNames(void);
void IgnitedByNames(void);
void NameAnimation(void);