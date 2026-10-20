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
       glColor4f(210.0f/255.0f, 171.0f/255.0f, 103.0f/255.0f, FadeFactor);
        glVertex2f(VALUE_FROM_PERCENT(-0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos - 1.25f);
        glVertex2f(VALUE_FROM_PERCENT( 0.40f, percent) + x_pos, VALUE_FROM_PERCENT( 0.80f, percent) + y_pos - 1.25f);
        
        
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
	glTranslatef(0.0f, 0.0f, -1.0f);

	GroupMembersNames();
    TechnologyUsedNames();
    SpecialThanksNames();
    IgnitedByNames();

}

void GroupMembersNames(void)
{
    glPushMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, GroupMemberFadeFactor);

    glScalef(0.2f, 0.29f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture_GroupMemNames);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

void SpecialThanksNames(void)
{
    glPushMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, SpecialThanksFadeFactor);

   glScalef(0.2f, 0.29f, 1.0f);


    glBindTexture(GL_TEXTURE_2D, texture_SpecialThanks);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

void TechnologyUsedNames(void)
{
    glPushMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, TechnologyUsedFadefactor);

    glScalef(0.2f, 0.29f, 1.0f);

   glBindTexture(GL_TEXTURE_2D, texture_TechnologyUsed);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

void IgnitedByNames(void)
{
    glPushMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, IgnitedByFadeFactor);

    glScalef(0.2f, 0.29f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture_IgnitedBy);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

void NameAnimation(void)
{
    switch(NameNumber)
    {
        case 0:
            if(GroupMemNameAnimation)
            {
                GroupMemberFadeFactor = GroupMemberFadeFactor + 0.0002f;
                if (GroupMemberFadeFactor >= 1.0f)
                {
                    GroupMemNameAnimation = FALSE;
                }
            }
            else
            {
                GroupMemberFadeFactor = GroupMemberFadeFactor - 0.0002f;
                if (GroupMemberFadeFactor <= 0.0f)
                {
                    NameNumber = 1;
                }
            }
            break;

        case 1:
            if(SpecialThanksAnimation)
            {
                SpecialThanksFadeFactor = SpecialThanksFadeFactor + 0.0002f;
                if (SpecialThanksFadeFactor >= 1.0f)
                {
                    SpecialThanksAnimation = FALSE;
                }
            }
            else
            {
                SpecialThanksFadeFactor = SpecialThanksFadeFactor - 0.0002f;
                if (SpecialThanksFadeFactor <= 0.0f)
                {
                    NameNumber = 2;
                }
            }
            break;

        case 2:
            if(TechnologyUsedAnimation)
            {
                TechnologyUsedFadefactor = TechnologyUsedFadefactor + 0.0002f;
                if ( TechnologyUsedFadefactor >= 1.0f)
                {
                    TechnologyUsedAnimation = FALSE;
                }
            }
            else
            {
                TechnologyUsedFadefactor = TechnologyUsedFadefactor - 0.0002f;
                if (TechnologyUsedFadefactor <= 0.0f)
                {
                    NameNumber = 3;
                }
            }
            break;

        case 3:
            if(IgnitedByAnimation)
            {
                IgnitedByFadeFactor = IgnitedByFadeFactor + 0.0002f;
                if (IgnitedByFadeFactor >= 1.0f)
                {
                    IgnitedByAnimation = FALSE;
                }
            }
            else
            {
                IgnitedByFadeFactor = IgnitedByFadeFactor - 0.0002f;
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