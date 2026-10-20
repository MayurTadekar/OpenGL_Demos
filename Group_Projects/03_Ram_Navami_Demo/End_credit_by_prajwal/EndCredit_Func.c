// Win32 headers
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <math.h>

// OpenGL related Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Custom Header File
#include "OGL.h"
#include "EndCredit.h"

BOOL GroupMemNameAnimation = TRUE;
BOOL SpecialThanksAnimation = TRUE;
BOOL TechnologyUsedAnimation = TRUE;
BOOL IgnitedByAnimation = TRUE;


float GroupMemberFadeFactor = 0.0f;
float SpecialThanksFadeFactor = 0.0f;
float TechnologyUsedFadefactor = 0.0f;
float IgnitedByFadeFactor = 0.0f;

int NameNumber = 0;

extern FILE *AAA_gpFile;

// Functions

void Lakhota(float x_pos, float y_pos, float percent, float FadeFactor)
{   

    //////////////////////////////////////////////////////////////////////
    // Center Golden Roll
    //////////////////////////////////////////////////////////////////////
    glBegin(GL_QUADS);
    {
        glColor4f(20.0f/255.0f, 8.0f/255.0f, 0.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos);
        
        glColor4f(144.0f/255.0f, 116.0f/255.0f, 74.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor4f(144.0f/255.0f, 116.0f/255.0f, 74.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos);
        
        glColor4f(20.0f/255.0f, 8.0f/255.0f, 0.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.715f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.715f, percent) + y_pos);
    }
    glEnd();

    //////////////////////////////////////////////////////////////////////
    // Center Red Roll
    //////////////////////////////////////////////////////////////////////
    glBegin(GL_QUADS);
    {
        glColor4f(156.0f/255.0f, 125.0f/255.0f, 82.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos);
        
        glColor4f(210.0f/255.0f, 171.0f/255.0f, 103.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor4f(210.0f/255.0f, 171.0f/255.0f, 103.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos);
        
        glColor4f(156.0f/255.0f, 125.0f/255.0f, 82.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.70f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.70f, percent) + y_pos);
    }
    glEnd();

    //////////////////////////////////////////////////////////////////////
    // Center Red Cloth
    //////////////////////////////////////////////////////////////////////
    glBegin(GL_QUADS);
    {
        glColor4f(172.0f/255.0f, 130.0f/255.0f, 78.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.7f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.7f, percent) + y_pos);
        
        glColor4f(204.0f/255.0f, 164.0f/255.0f, 102.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.50f, percent) + y_pos);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT(-0.50f, percent) + y_pos);
    }
    glEnd();

    //////////////////////////////////////////////////////////////////////
    // Golden_Triangle
    //////////////////////////////////////////////////////////////////////
    Lakhota_Gattu(-0.46f, 0.75f, 100.0f);

    Lakhota_Gattu_Right(0.46f, 0.75f, 100.0f);


    /////////////////////////////////////////////////////////////////////
    // Center Golden Roll
    //////////////////////////////////////////////////////////////////////
    glBegin(GL_QUADS);
    {
        glColor4f(20.0f/255.0f, 8.0f/255.0f, 0.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos - 1.25f);
        
        glColor4f(144.0f/255.0f, 116.0f/255.0f, 74.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos - 1.25f);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor4f(144.0f/255.0f, 116.0f/255.0f, 74.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.785f, percent) + y_pos - 1.25f);
        
        glColor4f(20.0f/255.0f, 8.0f/255.0f, 0.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.715f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT(-0.42f, percent) + x_pos, VALUE_FROM_PERCENT( 0.715f, percent) + y_pos - 1.25f);
    }
    glEnd();

    //////////////////////////////////////////////////////////////////////
    // Center Red Roll
    //////////////////////////////////////////////////////////////////////
    glBegin(GL_QUADS);
    {
        glColor4f(156.0f/255.0f, 125.0f/255.0f, 82.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos - 1.25f);
        
        glColor4f(210.0f/255.0f, 171.0f/255.0f, 103.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos - 1.25f);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor4f(210.0f/255.0f, 171.0f/255.0f, 103.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.75f, percent) + y_pos - 1.25f);
        
        glColor4f(156.0f/255.0f, 125.0f/255.0f, 82.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.70f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.70f, percent) + y_pos - 1.25f);
    }
    glEnd();

    //////////////////////////////////////////////////////////////////////
    // Golden_Triangle
    //////////////////////////////////////////////////////////////////////
    Lakhota_Gattu(-0.46f, -0.5f, 100.0f);

    Lakhota_Gattu_Right(0.46f, -0.5f, 100.0f);

}


void RenderText(const char* text) 
{
    glPushAttrib(GL_LIST_BIT);
    glListBase(baseFont - 32); 
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

void Lakhota_Gattu(float x_pos, float y_pos, float percentX)
{
    
    glBegin(GL_LINE_LOOP);
    {    
            for(int i = 50; i < 310; i++)
            {
                float angle = i * M_PI/180.0f;
                float x_coordinate = 0.0725f * cos(angle);
                float y_coordinate = 0.0725f * sin(angle); 

                glColor4f(156.0f/255.0f, 125.0f/255.0f, 82.0f/255.0f, 1.0f);
                glVertex3f(0.04f + x_pos, 0.0f + y_pos, 0.0f);

                glColor3f(79.0f/255.0f, 55.0f/255.0f, 34.0f/255.0f);
                glVertex3f(VALUE_FROM_PERCENT( x_coordinate, percentX) + x_pos, y_coordinate + y_pos, 0.0f);
            }
    }
    glEnd();
}

void Lakhota_Gattu_Right(float x_pos, float y_pos, float percentX)
{
    
    glBegin(GL_LINE_LOOP);
    {    
            for(int i = 130; i > -130; i--)
            {
                float angle = i * M_PI/180.0f;
                float x_coordinate = 0.0725f * cos(angle);
                float y_coordinate = 0.0725f * sin(angle); 

                glColor4f(156.0f/255.0f, 125.0f/255.0f, 82.0f/255.0f, 1.0f);
                glVertex3f(-0.04f + x_pos, 0.0f + y_pos, 0.0f);

                glColor3f(79.0f/255.0f, 55.0f/255.0f, 34.0f/255.0f);
                glVertex3f(VALUE_FROM_PERCENT( x_coordinate, percentX) + x_pos, y_coordinate + y_pos, 0.0f);
            }
    }
    glEnd();
}


void Prajwal_EndCredit(void)
{
    
    // Set it to Identity Matrix
	glLoadIdentity();

	// Translate Lakhota backward by z
	glTranslatef(0.0f, -0.15f, -2.0f);

	// code
	Lakhota(0.0f, 0.0f, 100, 1.0);

	// Set it to Identity Matrix
	glLoadIdentity();

	// Translate Names backward by z
	glTranslatef(0.0f, -0.30f, -1.0f);

	GroupMembersNames();
    TechnologyUsedNames();
    SpecialThanksNames();
    IgnitedByNames();

}

void GroupMembersNames(void)
{
    glColor4f( 88.0f/255.0f, 17.0f/255.0f, 24.0f/255.0f, GroupMemberFadeFactor);

	// Credit Role
	glRasterPos2f(-0.17f, 0.55f);
    RenderText("------------------------------ Group Members ------------------------------");

	glRasterPos2f(-0.06f, 0.52f);
    RenderText("Mayur S. Tadekar");

	glRasterPos2f(-0.06f, 0.485f);
    RenderText("Atharv A. Ambekar");

	glRasterPos2f(-0.06f, 0.45f);
    RenderText("Prajwal C. Warade");

	glRasterPos2f(-0.06f, 0.415f);
    RenderText("Adesh M. Pathare");

	glRasterPos2f(-0.06f, 0.38f);
    RenderText("Omkar U. Jadhav");

    glRasterPos2f(-0.06f, 0.345f);
    RenderText("Pankaj C. Hiwrale");

	glRasterPos2f(-0.06f, 0.31f);
    RenderText("Gauri S. Dudhande");

    glRasterPos2f(-0.06f, 0.275f);
    RenderText("Prashant D. Mankar");

	glRasterPos2f(-0.06f, 0.24f);
    RenderText("Nivrutti R. Damdhar");

	glRasterPos2f(-0.06f, 0.205f);
    RenderText("Shivkumar A. Ople");

	glRasterPos2f(-0.06f, 0.165f);
    RenderText("Amol S. Nandkar");

    glRasterPos2f(-0.06f, 0.125f);
    RenderText("Dr.Prasad R. Joshi");

	glRasterPos2f(-0.095f, 0.085f);
    RenderText("Swati A. Ladkat (Project Leader)");
    
	glRasterPos2f(-0.12f, 0.045f);
    RenderText("Shraddha G. Deshmukh (Group Leader)");
}

void SpecialThanksNames(void)
{
    glColor4f( 88.0f/255.0f, 17.0f/255.0f, 24.0f/255.0f, SpecialThanksFadeFactor);

	// Credit Role
	glRasterPos2f(-0.17f, 0.415f);
    RenderText("------------------------------ Special Thanks ------------------------------");

	glRasterPos2f(-0.08f, 0.38f);
    RenderText("Dr. Rama Gokhale Ma'am");

    glRasterPos2f(-0.08f, 0.345f);
    RenderText("Pradnya Gokhale Ma'am");

	glRasterPos2f(-0.08f, 0.31f);
    RenderText("Radhika Shukla Ma'am");

}

void TechnologyUsedNames(void)
{
    glColor4f( 88.0f/255.0f, 17.0f/255.0f, 24.0f/255.0f, TechnologyUsedFadefactor);

	// Credit Role
	glRasterPos2f(-0.17f, 0.415f);
    RenderText("------------------------------ Technology used ------------------------------");

	glRasterPos2f(-0.08f, 0.38f);
    RenderText("C Programming Language");

    glRasterPos2f(-0.043f, 0.345f);
    RenderText("Win32SDK");

	glRasterPos2f(-0.047f, 0.31f);
    RenderText("OpenGL FFP");
}

void IgnitedByNames(void)
{
    glColor4f( 88.0f/255.0f, 17.0f/255.0f, 24.0f/255.0f, IgnitedByFadeFactor);

	// Credit Role
	glRasterPos2f(-0.15f, 0.38f);
    RenderText("------------------------------ Ignited by ------------------------------");

    glRasterPos2f(-0.07f, 0.345f);
    RenderText("Dr Vijay D. Gokhale Sir");

}

void NameAnimation(void)
{
    switch(NameNumber)
    {
        case 0:
            if(GroupMemNameAnimation)
            {
                GroupMemberFadeFactor = GroupMemberFadeFactor + 0.001f;
                if (GroupMemberFadeFactor >= 1.0f)
                {
                    GroupMemNameAnimation = FALSE;
                }
            }
            else
            {
                GroupMemberFadeFactor = GroupMemberFadeFactor - 0.001f;
                if (GroupMemberFadeFactor <= 0.0f)
                {
                    NameNumber = 1;
                }
            }
            break;

        case 1:
            if(SpecialThanksAnimation)
            {
                SpecialThanksFadeFactor = SpecialThanksFadeFactor + 0.001f;
                if (SpecialThanksFadeFactor >= 1.0f)
                {
                    SpecialThanksAnimation = FALSE;
                }
            }
            else
            {
                SpecialThanksFadeFactor = SpecialThanksFadeFactor - 0.001f;
                if (SpecialThanksFadeFactor <= 0.0f)
                {
                    NameNumber = 2;
                }
            }
            break;

        case 2:
            if(TechnologyUsedAnimation)
            {
                TechnologyUsedFadefactor = TechnologyUsedFadefactor + 0.001f;
                if ( TechnologyUsedFadefactor >= 1.0f)
                {
                    TechnologyUsedAnimation = FALSE;
                }
            }
            else
            {
                TechnologyUsedFadefactor = TechnologyUsedFadefactor - 0.001f;
                if (TechnologyUsedFadefactor <= 0.0f)
                {
                    NameNumber = 3;
                }
            }
            break;

        case 3:
            if(IgnitedByAnimation)
            {
                IgnitedByFadeFactor = IgnitedByFadeFactor + 0.001f;
                if (IgnitedByFadeFactor >= 1.0f)
                {
                    IgnitedByAnimation = FALSE;
                }
            }
            else
            {
                IgnitedByFadeFactor = IgnitedByFadeFactor - 0.001f;
                if (IgnitedByFadeFactor <= 0.0f)
                {
                    NameNumber = 5;
                }
            }
            break;

        default :
            break;
    }
}