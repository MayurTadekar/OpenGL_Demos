#pragma once
#define GRN_Icon 101
#define DAY_CHANGE_TIMER 102
#define DAY_CHANGE_TIMER_AFTERNOON 103

#define	VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0f)

void GauriRamMandir(void);
void garbhgruhFirstFloor(void);
void garbhgruhSecondFloor(void);
void garbhgruhThirdFloor(void);
void garbhgruhMiddleSquare(void);
void garbhgruhFrontSqure(void);
void sabhMandapFirstSqure(void);
void sabhaMandapSecondSqare(void);
void sabhMandapTalMajala(void);
void land(void);
void baseSquare(void);

void Gauri_Mandir_Kalas(float x_pos, float y_pos);
void Gauri_Mandir_Kalas_paya(float x_pos, float y_pos);
void Gauri_Khamb(float x_pos, float y_pos);

void dayUpdate(void);
void dayUpdateAfternoon(void);

BOOL colorFlagMorning;
float colorChageRed,colorChageRedOne,colorChangeGreen,colorChangeGreenOne,colorChangeBlue,colorChangeBlueOne;

