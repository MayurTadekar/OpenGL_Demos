#pragma once


#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <time.h>
#include "mayur_common.h"

#define SQR(x) (x * x)
#define NUM_PARTICLES SQR(512)

#define MV_POINT_SIZE 5

int mst_particle_count = 0;

typedef struct
{
    float x, y;
    float deltaX, deltaY;
    float dirX, dirY;
    float life;
    float decay;
    float start_r, start_g, start_b;
    float end_r, end_g, end_b;
} Particle;

Particle mst_particles[NUM_PARTICLES];

float mst_fire_bottomXRadius = 0.1;
float mst_fire_bottomYRadius = 0.02;
float mst_fire_topXRadius = 0.02;
float mst_fire_topYRadius = 0.2;

void mst_initParticle(int index)
{
    // Code

    float le = rand() % 181 + 90;

    float rand_radius_factor = 1 + rand() % 100;
    rand_radius_factor /= 100.0f;
    rand_radius_factor = sinf(rand_radius_factor);

    le /= 10;

    float angle = M_PI * 2.0f * le / 36.0f;

    mst_particles[index].x = (mst_fire_bottomXRadius * rand_radius_factor) * sinf(angle);
    mst_particles[index].y = (mst_fire_bottomYRadius * rand_radius_factor) * cosf(angle);

    le = rand() % 181;
    le /= 10;
    angle = M_PI * 2.0f * le / 36.0f;
    mst_particles[index].dirX = mst_fire_topXRadius * cosf(angle);
    mst_particles[index].dirY = mst_fire_topYRadius * sinf(angle);

    mst_particles[index].deltaX = (mst_particles[index].dirX - mst_particles[index].x) / (float)(rand() % 120 + 60);
    mst_particles[index].deltaY = (mst_particles[index].dirY - mst_particles[index].y) / (float)(rand() % 120 + 60);

    mst_particles[index].decay = ((rand() % 50) + 1) / 200.0f;
    // mst_particles[index].decay = 0.01;

    mst_particles[index].life = 1.0f;

    mst_particles[index].start_r = VALUE_FROM_PERCENT(255.0f / 255.0f, 100.0f);
    mst_particles[index].start_g = VALUE_FROM_PERCENT(150.0f / 255.0f, 100.0f);
    mst_particles[index].start_b = VALUE_FROM_PERCENT(0.0f / 255.0f, 100.0f);

    mst_particles[index].end_r = VALUE_FROM_PERCENT(255.0f / 255.0f, 100.0f);
    mst_particles[index].end_g = VALUE_FROM_PERCENT(10.0f / 255.0f, 100.0f);
    mst_particles[index].end_b = VALUE_FROM_PERCENT(0.0f / 255.0f, 100.0f);
}

void mst_initParticles()
{
    // Code
    glEnable(GL_POINT_SIZE);
    glPointSize(2.0f);

    glEnable(GL_POINT_SMOOTH);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    srand(time(0));

    for (int i = 0; i < mst_particle_count; i++)
    {
        mst_initParticle(i);
    }
}

void mst_updateParticles()
{

    for (int i = 0; i < mst_particle_count; i++)
    {
        mst_particles[i].x += mst_particles[i].deltaX;
        mst_particles[i].y += mst_particles[i].deltaY;
        mst_particles[i].life -= mst_particles[i].decay;

        // Bounding mst_particles within a triangular shape
        if (mst_particles[i].life <= 0)
        {
            mst_initParticle(i);
        }
    }
}

void mst_incrementParticleCount()
{
    // Code
    if (mst_particle_count < NUM_PARTICLES)
    {
        mst_particle_count += 256;
    }
}

void mst_decrementParticleCount()
{
    // Code
    if (mst_particle_count > 0)
    {
        mst_particle_count -= 256;
    }
}

void  mst_drawFire(GLfloat x_pos, GLfloat y_pos, GLfloat percent)
{
    // Code
    glEnable(GL_POINT_SMOOTH);
    // glEnable(GL_BLEND);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < mst_particle_count; i++)
        {
            float fade = mst_particles[i].life;

            glColor4f( VALUE_FROM_PERCENT(mst_particles[i].start_r, fade * 100.0f) + VALUE_FROM_PERCENT(mst_particles[i].end_r, (1.0f - fade) * 200.0f),
                       VALUE_FROM_PERCENT(mst_particles[i].start_g, fade * 100.0f) + VALUE_FROM_PERCENT(mst_particles[i].end_g, (1.0f - fade) * 200.0f),
                       VALUE_FROM_PERCENT(mst_particles[i].start_b, fade * 100.0f) + VALUE_FROM_PERCENT(mst_particles[i].end_b, (1.0f - fade) * 200.0f),
                       100.0f);

            glVertex2f(VALUE_FROM_PERCENT(mst_particles[i].x, percent) + x_pos,
                       VALUE_FROM_PERCENT(mst_particles[i].y, percent) + y_pos);
        }
    }
    glEnd();

    // glDisable(GL_BLEND);
    glDisable(GL_POINT_SMOOTH);
}
