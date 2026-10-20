


#include <windows.h>
#include <gl/gl.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <time.h>
#include "mayur_common.h"

#define SQR(x) (x * x)
#define NUM_PARTICLES SQR(512)

#define MV_POINT_SIZE 5

int particle_count = 0;

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

Particle particles[NUM_PARTICLES];

float fire_bottomXRadius = 0.1;
float fire_bottomYRadius = 0.02;
float fire_topXRadius = 0.02;
float fire_topYRadius = 0.2;

void initParticle(int index)
{
    // Code

    float le = rand() % 181 + 90;

    float rand_radius_factor = 1 + rand() % 100;
    rand_radius_factor /= 100.0f;
    rand_radius_factor = sinf(rand_radius_factor);

    le /= 10;

    float angle = M_PI * 2.0f * le / 36.0f;

    particles[index].x = (fire_bottomXRadius * rand_radius_factor) * sinf(angle);
    particles[index].y = (fire_bottomYRadius * rand_radius_factor) * cosf(angle);

    le = rand() % 181;
    le /= 10;
    angle = M_PI * 2.0f * le / 36.0f;
    particles[index].dirX = fire_topXRadius * cosf(angle);
    particles[index].dirY = fire_topYRadius * sinf(angle);

    particles[index].deltaX = (particles[index].dirX - particles[index].x) / (float)(rand() % 120 + 60);
    particles[index].deltaY = (particles[index].dirY - particles[index].y) / (float)(rand() % 120 + 60);

    particles[index].decay = ((rand() % 50) + 1) / 200.0f;
    // particles[index].decay = 0.01;

    particles[index].life = 1.0f;

    particles[index].start_r = VALUE_FROM_PERCENT(255.0f / 255.0f, 100.0f);
    particles[index].start_g = VALUE_FROM_PERCENT(150.0f / 255.0f, 100.0f);
    particles[index].start_b = VALUE_FROM_PERCENT(0.0f / 255.0f, 100.0f);

    particles[index].end_r = VALUE_FROM_PERCENT(255.0f / 255.0f, 100.0f);
    particles[index].end_g = VALUE_FROM_PERCENT(10.0f / 255.0f, 100.0f);
    particles[index].end_b = VALUE_FROM_PERCENT(0.0f / 255.0f, 100.0f);
}

void initParticles()
{
    // Code
    glEnable(GL_POINT_SIZE);
    glPointSize(2.0f);

    glEnable(GL_POINT_SMOOTH);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    srand(time(0));

    for (int i = 0; i < particle_count; i++)
    {
        initParticle(i);
    }
}

void updateParticles()
{

    for (int i = 0; i < particle_count; i++)
    {
        particles[i].x += particles[i].deltaX;
        particles[i].y += particles[i].deltaY;
        particles[i].life -= particles[i].decay;

        // Bounding particles within a triangular shape
        if (particles[i].life <= 0)
        {
            initParticle(i);
        }
    }
}

void incrementParticleCount()
{
    // Code
    if (particle_count < NUM_PARTICLES)
    {
        particle_count += 256;
    }
}

void decrementParticleCount()
{
    // Code
    if (particle_count > 0)
    {
        particle_count -= 256;
    }
}

void drawFire(GLfloat x_pos, GLfloat y_pos, GLfloat percent)
{
    // Code
    glEnable(GL_POINT_SMOOTH);
    // glEnable(GL_BLEND);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < particle_count; i++)
        {
            float fade = particles[i].life;

            glColor4f( VALUE_FROM_PERCENT(particles[i].start_r, fade * 100.0f) + VALUE_FROM_PERCENT(particles[i].end_r, (1.0f - fade) * 200.0f),
                       VALUE_FROM_PERCENT(particles[i].start_g, fade * 100.0f) + VALUE_FROM_PERCENT(particles[i].end_g, (1.0f - fade) * 200.0f),
                       VALUE_FROM_PERCENT(particles[i].start_b, fade * 100.0f) + VALUE_FROM_PERCENT(particles[i].end_b, (1.0f - fade) * 200.0f),
                       100.0f);

            glVertex2f(VALUE_FROM_PERCENT(particles[i].x, percent) + x_pos,
                       VALUE_FROM_PERCENT(particles[i].y, percent) + y_pos);
        }
    }
    glEnd();

    // glDisable(GL_BLEND);
    glDisable(GL_POINT_SMOOTH);
}
