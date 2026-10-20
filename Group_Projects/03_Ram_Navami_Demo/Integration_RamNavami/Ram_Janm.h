#pragma once

#define VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0)

// Global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Function declarations
void Background(float x_pos, float y_pos, float percent);
void Window_Amol(float x_pos, float y_pos, float percent);
void Pillar_Amol(float x_pos, float y_pos, float percent);
void Aai_Amol(float x_pos, float y_pos, float percent);
void Palna_Amol(float x_pos, float y_pos, float percent);
void Palna_SupportingBodyLeft_Amol(float x_pos, float y_pos, float percent);
void Palna_SupportingBodyRight_Amol(float x_pos, float y_pos, float percent);
void Ram_Janm_Display_call_Amol(void);

