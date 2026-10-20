/*
 *************************************************
 * @file	: GuruShishya_Adesh.h
 * @brief	: Variable and Function declarations
 * @author	: Adesh Mohanrao Pathare 
 * 			  <adeshpathare8495@gmail.com>
 * @Date    : 31 March 2025
 *************************************************
 */

#pragma once

#define AMP_MYICON 101

#ifndef	VALUE_FROM_PERCENT
#define VALUE_FROM_PERCENT(complete, percent)	(complete * percent / 100.0)
#endif

// Global variable declarations
int i;

// Global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int initialize(void);
void resize(int width, int height);
void display(void);
void update(void);
void uninitialize(void);
void leave(GLfloat x_pos, GLfloat y_pos, GLfloat percent);
void tree_circle(GLfloat x_pos, GLfloat y_pos);
void tree_base(GLfloat x_pos, GLfloat y_pos);
void tree_base_line_loop(GLfloat, GLfloat);
void teaching_guru(GLfloat x_pos, GLfloat y_pos);
void guru_face(GLfloat x_pos, GLfloat y_pos);
void guru_upper_body(GLfloat x_pos, GLfloat y_pos);
void guru_legs(GLfloat x_pos, GLfloat y_pos);
void shishya(GLfloat x_pos, GLfloat y_pos);
void shishya_body(GLfloat x_pos, GLfloat y_pos);
void shishya_legs(GLfloat x_pos, GLfloat y_pos);
void shishya_face(GLfloat x_pos, GLfloat y_pos);
void kutiya_all(GLfloat x_pos, GLfloat y_pos);
void river(GLfloat x_pos, GLfloat y_pos);
void drawSineWave(GLfloat x_pos, 
                    GLfloat y_pos, 
                    GLfloat startX, 
                    GLfloat endX,
                    GLfloat startY,
                    GLfloat amplitude, 
                    GLfloat frequency);
void adesh_land(GLfloat x_pos, GLfloat y_pos);
void adesh_sky(GLfloat x_pos, GLfloat y_pos);
void adesh_mountain_river(GLfloat x_pos, GLfloat y_pos);
void adesh_tree_wood(GLfloat x_pos, GLfloat y_pos);
void adesh_guru_shishya(void);
void adesh_curve_calculations(void);

//EOF
