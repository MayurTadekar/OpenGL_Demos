// header files
#include<GL/freeglut.h>

void Hill_Gauri(float x_pos,float y_pos)
{	
	//////////1st hill

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.9999f + x_pos, 0.49f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.97f + x_pos, 0.61f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.18f + x_pos, 0.61f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.08f + x_pos, 0.49f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.97f + x_pos, 0.61f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.85f + x_pos, 0.76 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.30f + x_pos, 0.75f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.18f + x_pos, 0.57f + y_pos, 0.0f);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.85f + x_pos, 0.76f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.76f + x_pos, 0.85 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.34f + x_pos, 0.84f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.30f + x_pos, 0.75f + y_pos, 0.0f);


	glEnd();



	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.76f + x_pos, 0.85f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.68f + x_pos, 0.90 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.45f + x_pos, 0.91f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.34f + x_pos, 0.84f + y_pos, 0.0f);


	glEnd();



	glBegin(GL_QUADS);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.68f + x_pos, 0.90 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(-0.59f + x_pos,0.95 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(-0.57f + x_pos, 0.95 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.45f + x_pos, 0.91f + y_pos, 0.0f);

	glEnd();

	////////////////////////2ed hill

	glBegin(GL_QUADS);
	//2 ed 
	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.12f + x_pos, 0.53f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.22f + x_pos, 0.62f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.24f + x_pos, 0.61f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.34f + x_pos, 0.53f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.22f + x_pos, 0.62f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.26f + x_pos, 0.68 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.16f + x_pos, 0.68f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.24f + x_pos, 0.61f + y_pos, 0.0f);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.26f + x_pos, 0.68 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.29f + x_pos, 0.73 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.16f + x_pos, 0.68f + y_pos, 0.0f);

	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.29f + x_pos, 0.73 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(-0.15f + x_pos, 0.79 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.05f + x_pos, 0.78 + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(-0.15f + x_pos, 0.79 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(-0.08f + x_pos, 0.83 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(-0.06f + x_pos, 0.83f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.05f + x_pos, 0.78 + y_pos, 0.0f);


	glEnd();
	

	////////////3rd hill
	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.25f + x_pos, 0.59f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.16f + x_pos, 0.66f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.66f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.59f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.16f + x_pos, 0.66f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.40f + x_pos, 0.72f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.66f + y_pos, 0.0f);


	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.10f + x_pos, 0.72 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.20f + x_pos, 0.76 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.21f + x_pos, 0.76 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.40f + x_pos, 0.72f + y_pos, 0.0f);

	glEnd();

	


	//////////////////4th  hill

	glBegin(GL_QUADS);
	//4 last ed 
	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.39f + x_pos, 0.57f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.45f + x_pos, 0.68f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.9999f + x_pos, 0.69f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.9999f + x_pos, 0.57f + y_pos, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.45f + x_pos, 0.68f + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.49f + x_pos, 0.74 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.96f + x_pos, 0.75f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.9999f + x_pos, 0.69f + y_pos, 0.0f);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.49f + x_pos, 0.74 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.54f + x_pos, 0.80 + y_pos, 0.0f);

	glColor3f(0.991157f, 0.466667f, 0.329412f);
	glVertex3f(0.90f + x_pos, 0.81 + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.96f + x_pos, 0.75f + y_pos, 0.0f);

	glEnd();



	glBegin(GL_QUADS);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.54f + x_pos, 0.80 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.68f + x_pos, 0.86 + y_pos, 0.0f);

	glColor3f(0.600000, 0.600000, 0.600000);
	glVertex3f(0.73f + x_pos, 0.87f + y_pos, 0.0f);

	glColor3f(0.498039, 0.333333, 0.278431);
	glVertex3f(0.90f + x_pos, 0.81 + y_pos, 0.0f);


	glEnd();
	
 
}
