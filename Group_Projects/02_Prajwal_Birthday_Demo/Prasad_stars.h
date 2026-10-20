#include <GL/freeglut.h>

extern void Prasad_Stars(float x_pos, float y_pos, float Shining_Factor);
extern void StarsShineFunc(int value);

void Prasad_Stars(float x_pos, float y_pos, float Shining_Factor)
{
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glColor4f(0.8f, 1.0f, 1.0f, Shining_Factor);
	glPointSize(2.0f);

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, 0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.3f + x_pos, 0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.5f + x_pos, 0.2f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.1f + x_pos, 0.3f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.3f + x_pos, 0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.2f + x_pos, 0.2f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.0f + x_pos, 0.0f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, 0.4f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.5f + x_pos, 0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, 0.5f + y_pos, 0.0f);
	glEnd();

	glPointSize(5.0f);

	glBegin(GL_POINTS);
	glVertex3f(-0.3f + x_pos, 0.3f + y_pos, 0.0f);
	glEnd();

	glPointSize(1.3f);

	glBegin(GL_POINTS);
	glVertex3f(-0.5f + x_pos, 0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, 0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.5f + x_pos, 0.4f + y_pos, 0.0f);
	glEnd();

	glPointSize(2.0f);

	glBegin(GL_POINTS);
	glVertex3f(-0.45f + x_pos, 0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.45f + x_pos, 0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.55f + x_pos, 0.6f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.25f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.25f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.0f + x_pos, 0.3f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.45f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.1f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.15f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.5f + x_pos, 0.6f + y_pos, 0.0f);
	glEnd();

	glPointSize(1.0f);

	glBegin(GL_POINTS);
	glVertex3f(-0.55f + x_pos, 0.65f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.1f + x_pos, 0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.75f + x_pos, 0.65f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, 0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.75f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.18f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glPointSize(2.2f);

	glBegin(GL_POINTS);
	glVertex3f(0.65f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, 0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.78f + x_pos, 0.15f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.7f + x_pos, 0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.75f + x_pos, 0.25f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, 0.25f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, 0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.75f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glPointSize(0.5f);

	glBegin(GL_POINTS);
	glVertex3f(-0.18f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.6f + x_pos, 0.25f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, 0.65f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.65f + x_pos, 0.05f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.75f + x_pos, 0.15f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.55f + x_pos, 0.45f + y_pos, 0.0f);
	glEnd();

	glPointSize(1.2f);

	glBegin(GL_POINTS);
	glVertex3f(0.45f + x_pos, 0.15f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.18f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.7f + x_pos, 0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.4f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.65f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.45f + x_pos, 0.8f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.35f + x_pos, 0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.8f + x_pos, 0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.9f + x_pos, 0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.9f + x_pos, 0.45f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.95f + x_pos, 0.36f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.97f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.65f + x_pos, 0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.95f + x_pos, 0.16f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.97f + x_pos, 0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.85f + x_pos, 0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.15f + x_pos, 0.95f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.76f + x_pos, 0.16f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.27f + x_pos, 0.96f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.3f + x_pos, 0.91f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.85f + x_pos, 0.89f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.86f + x_pos, 0.93f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.07f + x_pos, 0.91f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.0f + x_pos, 0.87f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.35f + x_pos, 0.87f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.02f + x_pos, 0.89f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.56f + x_pos, 0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.43f + x_pos, 0.94f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, -0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.3f + x_pos, -0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.5f + x_pos, -0.2f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.1f + x_pos, -0.3f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.3f + x_pos, -0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.2f + x_pos, -0.2f + y_pos, 0.0f);
	glEnd();

	glPointSize(5.0f);

	glBegin(GL_POINTS);
	glVertex3f(0.0f + x_pos, 0.0f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, -0.4f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.5f + x_pos, -0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, -0.5f + y_pos, 0.0f);
	glEnd();


	glBegin(GL_POINTS);
	glVertex3f(-0.3f + x_pos, -0.3f + y_pos, 0.0f);
	glEnd();

	glPointSize(1.3f);

	glBegin(GL_POINTS);
	glVertex3f(-0.5f + x_pos, -0.1f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, -0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.5f + x_pos, -0.4f + y_pos, 0.0f);
	glEnd();

	glPointSize(2.0f);

	glBegin(GL_POINTS);
	glVertex3f(-0.45f + x_pos, -0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.45f + x_pos, -0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.55f + x_pos, -0.6f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.25f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.25f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.0f + x_pos, -0.3f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.45f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.1f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.15f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.5f + x_pos, -0.6f + y_pos, 0.0f);
	glEnd();

	glPointSize(1.0f);

	glBegin(GL_POINTS);
	glVertex3f(-0.55f + x_pos, -0.65f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.1f + x_pos, -0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.75f + x_pos, -0.65f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, -0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.75f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.18f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glPointSize(2.2f);

	glBegin(GL_POINTS);
	glVertex3f(0.65f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, -0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.78f + x_pos, -0.15f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.7f + x_pos, -0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.75f + x_pos, -0.25f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.2f + x_pos, -0.25f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, -0.7f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.75f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glPointSize(0.5f);

	glBegin(GL_POINTS);
	glVertex3f(-0.18f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.6f + x_pos, -0.25f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.1f + x_pos, -0.65f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.65f + x_pos, -0.05f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.75f + x_pos, -0.15f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.55f + x_pos, -0.45f + y_pos, 0.0f);
	glEnd();

	glPointSize(1.2f);

	glBegin(GL_POINTS);
	glVertex3f(0.45f + x_pos, -0.15f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.18f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.7f + x_pos, -0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.4f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.65f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.45f + x_pos, -0.8f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.35f + x_pos, -0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.8f + x_pos, -0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.9f + x_pos, -0.55f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.9f + x_pos, -0.45f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.95f + x_pos, -0.36f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.97f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.65f + x_pos, -0.35f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.95f + x_pos, -0.16f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.97f + x_pos, -0.75f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.85f + x_pos, -0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.15f + x_pos, -0.95f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.76f + x_pos, -0.16f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.27f + x_pos, -0.96f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.3f + x_pos, -0.91f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.85f + x_pos, -0.89f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.86f + x_pos, -0.93f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.07f + x_pos, -0.91f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.0f + x_pos, -0.87f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.35f + x_pos, -0.87f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.02f + x_pos, -0.89f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(-0.56f + x_pos, -0.85f + y_pos, 0.0f);
	glEnd();

	glBegin(GL_POINTS);
	glVertex3f(0.43f + x_pos, -0.94f + y_pos, 0.0f);
	glEnd();
	glPointSize(2.6f);

	glBegin(GL_POINTS);
	glVertex3f(0.85f + x_pos, -0.85f + y_pos, 0.0f);
	glEnd();


	//
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);
}