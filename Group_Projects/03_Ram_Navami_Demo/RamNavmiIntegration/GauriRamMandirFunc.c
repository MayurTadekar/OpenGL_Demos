//win32 headers
#include<Windows.h>
#include<stdio.h>//file input outut sathi 
#include<stdlib.h>//file madhe exit karayche asel tar
#include<math.h>

//open GL related header files
#include<gl/GL.h>

//custom header files
#include "RamMandir.h"

 HWND ghwnd; 

void GauriRamMandir(void)
{
	//set it to identitity matrics
	glLoadIdentity();
	//translate triangle backwords by z axis
	glTranslatef(0.0f, 0.0f, -8.0f);//for icmd show
	//scale
	glScalef(6.5f, 3.33f, 0.0f);//for icmd show
    
    //सगल्या विंडो चा रंग पहाट लाल अणि पिवला 
	if(colorFlagMorning==FALSE)
	{
		glBegin(GL_QUADS);
		glColor3f(VALUE_FROM_PERCENT(1.0,colorChageRed),VALUE_FROM_PERCENT(0.58823,colorChangeGreen),VALUE_FROM_PERCENT(0.39215,colorChangeBlue));
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glColor3f(VALUE_FROM_PERCENT(1.0,colorChageRed),VALUE_FROM_PERCENT(0.5,colorChangeGreen),VALUE_FROM_PERCENT(0.0,colorChangeBlue));
		glVertex3f(1.0f, 1.0f, 0.0f);
		glColor3f(VALUE_FROM_PERCENT(1.0,colorChageRed),VALUE_FROM_PERCENT(0.58823,colorChangeGreen),VALUE_FROM_PERCENT(0.39215,colorChangeBlue));
		glVertex3f(-1.0f, 1.0f, 0.0f);
	
		glEnd();
	}
	
    else
	{
		glBegin(GL_QUADS);
		glColor3f(VALUE_FROM_PERCENT(0.509804,colorChageRed),VALUE_FROM_PERCENT(0.839216,colorChangeGreen),VALUE_FROM_PERCENT(0.952941,colorChangeBlue));
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glColor3f(VALUE_FROM_PERCENT(0.913725,colorChageRed),VALUE_FROM_PERCENT(0.976471,colorChangeGreen),VALUE_FROM_PERCENT(0.992157,colorChangeBlue));
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glColor3f(VALUE_FROM_PERCENT(0.509804,colorChageRed),VALUE_FROM_PERCENT(0.839216,colorChangeGreen),VALUE_FROM_PERCENT(0.952941,colorChangeBlue));
		glVertex3f(-1.0f, 1.0f, 0.0f);
	
		glEnd();
	}
	///गर्भगृह  मागचा  चौकोन १ 
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.92f, -0.7f, 0.0f);
	glVertex3f(-0.65f, -0.7f, 0.0f);
	glVertex3f(-0.65f, -0.02f, 0.0f);
	glVertex3f(-0.92f, -0.02f, 0.0f);

	glEnd();
	/////गर्भगृह  पहिला मजला पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(-0.99f, -0.48f, 0.0f);
	glVertex3f(-0.65f, -0.48f, 0.0f);
	glVertex3f(-0.65f, -0.5f, 0.0f);
	glVertex3f(-0.99f, -0.5f, 0.0f);
	glEnd();

	/////गर्भगृह  पहिला मजला आतील पट्टा 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.99f, -0.5f, 0.0f);

	glVertex3f(-0.65f, -0.5f, 0.0f);
	glVertex3f(-0.65f, -0.51f, 0.0f);
	glVertex3f(-0.99f, -0.51f, 0.0f);

	glEnd();

	/////गर्भगृह  दूसरा  मजला आतील पट्टा 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.99f, -0.28f, 0.0f);
	glVertex3f(-0.65f, -0.28f, 0.0f);
	glVertex3f(-0.65f, -0.29f, 0.0f);
	glVertex3f(-0.99f, -0.29f, 0.0f);

	glEnd();


	Gauri_Khamb(-0.98, -0.33);
	Gauri_Khamb(-0.92, -0.33);
	Gauri_Khamb(-0.85, -0.33);
	Gauri_Khamb(-0.78, -0.33);
	Gauri_Khamb(-0.7, -0.33);
 
	/////गर्भगृह  पहिला मजला पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.98f, -0.48f, 0.0f);
	glVertex3f(-0.65f, -0.48f, 0.0f);
	glVertex3f(-0.65f, -0.4f, 0.0f);
	glVertex3f(-0.98f, -0.4f, 0.0f);

	glEnd();

	/////गर्भगृह  दूसरा  मजला पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(-0.99f, -0.26f, 0.0f);
	glVertex3f(-0.65f, -0.26f, 0.0f);
	glVertex3f(-0.65f, -0.28f, 0.0f);
	glVertex3f(-0.99f, -0.28f, 0.0f);

	glEnd();

	/////गर्भगृह  तिसरा मजला आतील पट्टा 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.99f, -0.06f, 0.0f);
	glVertex3f(-0.65f, -0.06f, 0.0f);
	glVertex3f(-0.65f, -0.1f, 0.0f);
	glVertex3f(-0.99f, -0.1f, 0.0f);

	glEnd();


	Gauri_Khamb(-0.98, -0.11);
	Gauri_Khamb(-0.92, -0.11);
	Gauri_Khamb(-0.85, -0.11);
	Gauri_Khamb(-0.78, -0.11);
	Gauri_Khamb(-0.7, -0.11);

	/////गर्भगृह दूसरा  मजला पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.98f, -0.26f, 0.0f);
	glVertex3f(-0.65f, -0.26f, 0.0f);
	glVertex3f(-0.65f, -0.18f, 0.0f);
	glVertex3f(-0.98f, -0.18f, 0.0f);

	glEnd();

	/////गर्भगृह तिसरा मजला पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(-0.99f, -0.04f, 0.0f);
	glVertex3f(-0.65f, -0.04f, 0.0f);
	glVertex3f(-0.65f, -0.06f, 0.0f);
	glVertex3f(-0.99f, -0.06f, 0.0f);

	glEnd();

	/////गर्भगृह तिसरा मजला पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.98f, -0.04f, 0.0f);
	glVertex3f(-0.65f, -0.04f, 0.0f);
	glVertex3f(-0.65f, -0.02f, 0.0f);
	glVertex3f(-0.98f, -0.02f, 0.0f);

	glEnd();

	/////गर्भगृह  पहिला मजला मंदिर 1 कलस पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(-0.75f, -0.46f, 0.0f);
	glVertex3f(-0.65f, -0.46f, 0.0f);
	glVertex3f(-0.65f, -0.49f, 0.0f);
	glVertex3f(-0.77f, -0.49f, 0.0f);

	glEnd();

	/////गर्भगृह  पहिला मजला मंदिर 1 कलस पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.75f, -0.45f, 0.0f);
	glVertex3f(-0.65f, -0.45f, 0.0f);
	glVertex3f(-0.65f, -0.46f, 0.0f);
	glVertex3f(-0.75f, -0.46f, 0.0f);

	glEnd();

	/////गर्भगृह  पहिला मजला मंदिर 1 कलस पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.74f, -0.44f, 0.0f);
	glVertex3f(-0.65f, -0.44f, 0.0f);
	glVertex3f(-0.65f, -0.45f, 0.0f);
	glVertex3f(-0.74f, -0.45f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 1 कलस पट्टा 4
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.73f, -0.43f, 0.0f);
	glVertex3f(-0.66f, -0.43f, 0.0f);
	glVertex3f(-0.66f, -0.44f, 0.0f);
	glVertex3f(-0.73f, -0.44f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 1 कलस  पट्टा 5
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.72f, -0.42f, 0.0f);
	glVertex3f(-0.67f, -0.42f, 0.0f);
	glVertex3f(-0.67f, -0.43f, 0.0f);
	glVertex3f(-0.72f, -0.43f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 1 कलस पट्टा 6
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.71f, -0.41f, 0.0f);
	glVertex3f(-0.68f, -0.41f, 0.0f);
	glVertex3f(-0.68f, -0.42f, 0.0f);
	glVertex3f(-0.71f, -0.42f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 1 कलस पट्टा  पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(-0.7f, -0.39f, 0.0f);
	glVertex3f(-0.69f, -0.39f, 0.0f);
	glVertex3f(-0.69f, -0.41f, 0.0f);
	glVertex3f(-0.7f, -0.41f, 0.0f);

	glEnd();

	///गर्भगृह मधला  चौकोन २ 
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.65f, -0.7f, 0.0f);
	glVertex3f(-0.35f, -0.7f, 0.0f);
	glVertex3f(-0.35f, -0.03f, 0.0f);
	glVertex3f(-0.65f, -0.03f, 0.0f);

	glEnd();

	///गर्भगृह ३d दाखवायला काढलेला चौकोन ३ 
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.35f, -0.7f, 0.0f);
	glVertex3f(-0.32f, -0.7f, 0.0f);
	glVertex3f(-0.32f, -0.05f, 0.0f);
	glVertex3f(-0.35f, -0.03f, 0.0f);

	glEnd();

	//गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस चौकोन 
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(-0.63f, -0.03f, 0.0f);
	glVertex3f(-0.22f, -0.03f, 0.0f);
	glVertex3f(-0.22f, 0.03f, 0.0f);
	glVertex3f(-0.63f, 0.03f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या सगळ्यात वरील मंदिर 2 कलस पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.61f, 0.03f, 0.0f);
	glVertex3f(-0.24f, 0.03f, 0.0f);
	glVertex3f(-0.24f, 0.05f, 0.0f);
	glVertex3f(-0.61f, 0.05f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस  पट्टा 4
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.59f, 0.07f, 0.0f);
	glVertex3f(-0.26f, 0.07f, 0.0f);
	glVertex3f(-0.26f, 0.05f, 0.0f);
	glVertex3f(-0.59f, 0.05f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस पट्टा 5
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.57f, 0.09f, 0.0f);
	glVertex3f(-0.28f, 0.09f, 0.0f);
	glVertex3f(-0.28f, 0.07f, 0.0f);
	glVertex3f(-0.57f, 0.07f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस  पट्टा 6
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.55f, 0.11f, 0.0f);
	glVertex3f(-0.3f, 0.11f, 0.0f);
	glVertex3f(-0.3f, 0.09f, 0.0f);
	glVertex3f(-0.55f, 0.09f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस पट्टा 7
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.53f, 0.13f, 0.0f);
	glVertex3f(-0.32f, 0.13f, 0.0f);
	glVertex3f(-0.32f, 0.11f, 0.0f);
	glVertex3f(-0.53f, 0.11f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस  पट्टा 8
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.51f, 0.15f, 0.0f);
	glVertex3f(-0.34f, 0.15f, 0.0f);
	glVertex3f(-0.34f, 0.13f, 0.0f);
	glVertex3f(-0.51f, 0.13f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस पट्टा 9
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.49f, 0.17f, 0.0f);
	glVertex3f(-0.36f, 0.17f, 0.0f);
	glVertex3f(-0.36f, 0.15f, 0.0f);
	glVertex3f(-0.49f, 0.15f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस  पट्टा 10
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.47f, 0.19f, 0.0f);
	glVertex3f(-0.38f, 0.19f, 0.0f);
	glVertex3f(-0.38f, 0.17f, 0.0f);
	glVertex3f(-0.47f, 0.17f, 0.0f);

	glEnd();

	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस पट्टा 11
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.45f, 0.21f, 0.0f);
	glVertex3f(-0.4f, 0.21f, 0.0f);
	glVertex3f(-0.4f, 0.19f, 0.0f);
	glVertex3f(-0.45f, 0.19f, 0.0f);

	glEnd();
	////गर्भगृह अणि गर्भगृह ३d दाखवायला काढलेला चौकोन यांच्या  सगळ्यात वरील मंदिर कलस पट्टा  पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(-0.43f, 0.23f, 0.0f);
	glVertex3f(-0.42f, 0.23f, 0.0f);
	glVertex3f(-0.42f, 0.21f, 0.0f);
	glVertex3f(-0.43f, 0.21f, 0.0f);

	glEnd();


	//गर्भगृह मधील खाम्ब 
	Gauri_Khamb(-0.65, -0.54);
	Gauri_Khamb(-0.67, -0.55);
	Gauri_Khamb(-0.58, -0.54);
	Gauri_Khamb(-0.60, -0.55);

	Gauri_Khamb(-0.49, -0.54);
	Gauri_Khamb(-0.46, -0.55);
	Gauri_Khamb(-0.4, -0.54);
	Gauri_Khamb(-0.37, -0.55);
	
	//गर्भगृह मधील पहिला मजला  खाम्ब 
	Gauri_Khamb(-0.65, -0.32);
	Gauri_Khamb(-0.58, -0.32);
	Gauri_Khamb(-0.5, -0.32);
	Gauri_Khamb(-0.4, -0.31);
	Gauri_Khamb(-0.37, -0.32);

	//गर्भगृह मधला  चौकोन पहिला मजला पट्टा १  
	glBegin(GL_QUADS);
	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.65f, -0.48f, 0.0f);
	glVertex3f(-0.35f, -0.48f, 0.0f);
	glVertex3f(-0.33f, -0.5f, 0.0f);
	glVertex3f(-0.67f, -0.5f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन पहिला मजला पट्टा 2 
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.65f, -0.48f, 0.0f);
	glVertex3f(-0.35f, -0.48f, 0.0f);
	glVertex3f(-0.35f, -0.46f, 0.0f);
	glVertex3f(-0.65f, -0.46f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन पहिला मजला पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.65f, -0.46f, 0.0f);
	glVertex3f(-0.34f, -0.46f, 0.0f);
	glVertex3f(-0.34f, -0.4f, 0.0f);
	glVertex3f(-0.65f, -0.4f, 0.0f);

	glEnd();

	/////गर्भगृह मधला  चौकोन मंदिर 2 कलस पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.63f, -0.49f, 0.0f);
	glVertex3f(-0.42f, -0.49f, 0.0f);
	glVertex3f(-0.4f, -0.51f, 0.0f);
	glVertex3f(-0.65f, -0.51f, 0.0f);

	glEnd();

	/////गर्भगृह मधला  चौकोन मंदिर 2 कलस पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.61f, -0.43f, 0.0f);
	glVertex3f(-0.45f, -0.43f, 0.0f);
	glVertex3f(-0.45f, -0.46f, 0.0f);
	glVertex3f(-0.61f, -0.46f, 0.0f);

	glEnd();

	/////गर्भगृह  मधला  चौकोन मंदिर 2 कलस पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.61f, -0.42f, 0.0f);
	glVertex3f(-0.45f, -0.42f, 0.0f);
	glVertex3f(-0.45f, -0.43f, 0.0f);
	glVertex3f(-0.61f, -0.43f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस पट्टा 4
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.6f, -0.41f, 0.0f);
	glVertex3f(-0.45f, -0.41f, 0.0f);
	glVertex3f(-0.45f, -0.42f, 0.0f);
	glVertex3f(-0.6f, -0.42f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस  पट्टा 5
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.59f, -0.4f, 0.0f);
	glVertex3f(-0.46f, -0.4f, 0.0f);
	glVertex3f(-0.46f, -0.41f, 0.0f);
	glVertex3f(-0.59f, -0.41f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस पट्टा 6
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.58f, -0.39f, 0.0f);
	glVertex3f(-0.47f, -0.39f, 0.0f);
	glVertex3f(-0.47f, -0.4f, 0.0f);
	glVertex3f(-0.58f, -0.4f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस  पट्टा 7
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.57f, -0.38f, 0.0f);
	glVertex3f(-0.48f, -0.38f, 0.0f);
	glVertex3f(-0.48f, -0.39f, 0.0f);
	glVertex3f(-0.57f, -0.39f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस पट्टा 8
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.56f, -0.37f, 0.0f);
	glVertex3f(-0.49f, -0.37f, 0.0f);
	glVertex3f(-0.49f, -0.38f, 0.0f);
	glVertex3f(-0.56f, -0.38f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस  पट्टा 9
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.55f, -0.36f, 0.0f);
	glVertex3f(-0.5f, -0.36f, 0.0f);
	glVertex3f(-0.5f, -0.37f, 0.0f);
	glVertex3f(-0.55f, -0.37f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस पट्टा 10
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.54f, -0.35f, 0.0f);
	glVertex3f(-0.51f, -0.35f, 0.0f);
	glVertex3f(-0.51f, -0.36f, 0.0f);
	glVertex3f(-0.54f, -0.36f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर 2 कलस पट्टा  पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(-0.53f, -0.33f, 0.0f);
	glVertex3f(-0.52f, -0.33f, 0.0f);
	glVertex3f(-0.52f, -0.35f, 0.0f);
	glVertex3f(-0.53f, -0.35f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन दूसरा  मजला पट्टा १  
	glBegin(GL_QUADS);


	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.65f, -0.25f, 0.0f);
	glVertex3f(-0.35f, -0.25f, 0.0f);
	glVertex3f(-0.33f, -0.27f, 0.0f);
	glVertex3f(-0.67f, -0.27f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन दूसरा मजला पट्टा 2 
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.65f, -0.23f, 0.0f);
	glVertex3f(-0.35f, -0.23f, 0.0f);
	glVertex3f(-0.35f, -0.25f, 0.0f);
	glVertex3f(-0.65f, -0.25f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 1
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.64f, -0.23f, 0.0f);
	glVertex3f(-0.36f, -0.23f, 0.0f);
	glVertex3f(-0.36f, -0.17f, 0.0f);
	glVertex3f(-0.64f, -0.17f, 0.0f);

	glEnd();

	////गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.62f, -0.15f, 0.0f);
	glVertex3f(-0.38f, -0.15f, 0.0f);
	glVertex3f(-0.38f, -0.17f, 0.0f);
	glVertex3f(-0.62f, -0.17f, 0.0f);

	glEnd();

	////गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.6f, -0.13f, 0.0f);
	glVertex3f(-0.4f, -0.13f, 0.0f);
	glVertex3f(-0.4f, -0.15f, 0.0f);
	glVertex3f(-0.6f, -0.15f, 0.0f);

	glEnd();

	////गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 4
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.58f, -0.11f, 0.0f);
	glVertex3f(-0.42f, -0.11f, 0.0f);
	glVertex3f(-0.42f, -0.13f, 0.0f);
	glVertex3f(-0.58f, -0.13f, 0.0f);

	glEnd();

	////गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 5
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.56f, -0.09f, 0.0f);
	glVertex3f(-0.44f, -0.09f, 0.0f);
	glVertex3f(-0.44f, -0.11f, 0.0f);
	glVertex3f(-0.56f, -0.11f, 0.0f);

	glEnd();

	////गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 6
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.54f, -0.07f, 0.0f);
	glVertex3f(-0.46f, -0.07f, 0.0f);
	glVertex3f(-0.46f, -0.09f, 0.0f);
	glVertex3f(-0.54f, -0.09f, 0.0f);

	glEnd();

	////गर्भगृह मधला  चौकोन दूसरा मजला मंदिर कलस  पट्टा 7
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.52f, -0.09f, 0.0f);
	glVertex3f(-0.48f, -0.09f, 0.0f);
	glVertex3f(-0.48f, -0.11f, 0.0f);
	glVertex3f(-0.52f, -0.11f, 0.0f);

	glEnd();

	////गर्भगृह  पहिला मजला मंदिर कलस पट्टा  पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(-0.51f, -0.05f, 0.0f);
	glVertex3f(-0.49f, -0.05f, 0.0f);
	glVertex3f(-0.49f, -0.07f, 0.0f);
	glVertex3f(-0.51f, -0.07f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन सगळ्यात  वरील पट्टे १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.6f, -0.03f, 0.0f);
	glVertex3f(-0.35f, -0.03f, 0.0f);
	glVertex3f(-0.35f, -0.01f, 0.0f);
	glVertex3f(-0.6f, -0.01f, 0.0f);

	glEnd();

	//गर्भगृह मधला  चौकोन सगळ्यात  वरील पट्टे 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.6f, -0.01f, 0.0f);
	glVertex3f(-0.35f, -0.01f, 0.0f);
	glVertex3f(-0.35f, 0.01f, 0.0f);
	glVertex3f(-0.6f, 0.01f, 0.0f);

	glEnd();

	///गर्भगृह तिसरा मजला वरील ३d दाखवायला काढलेला चौकोन वरील पट्टा 1
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.35f, -0.03f, 0.0f);
	glVertex3f(-0.32f, -0.05f, 0.0f);
	glVertex3f(-0.32f, -0.03f, 0.0f);
	glVertex3f(-0.35f, -0.01f, 0.0f);

	glEnd();

	///गर्भगृह तिसरा मजला वरील  ३d दाखवायला काढलेला चौकोन वरील पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.35f, -0.01f, 0.0f);
	glVertex3f(-0.32f, -0.03f, 0.0f);
	glVertex3f(-0.32f, -0.01f, 0.0f);
	glVertex3f(-0.35f, 0.01f, 0.0f);

	glEnd();

	///गर्भगृह दूसरा  मजला वरील ३d दाखवायला काढलेला चौकोन वरील पट्टा 1
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.35f, -0.27f, 0.0f);
	glVertex3f(-0.32f, -0.29f, 0.0f);
	glVertex3f(-0.32f, -0.27f, 0.0f);
	glVertex3f(-0.35f, -0.25f, 0.0f);

	glEnd();

	///गर्भगृह दूसरा  मजला वरील  ३d दाखवायला काढलेला चौकोन वरील पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.35f, -0.25f, 0.0f);
	glVertex3f(-0.32f, -0.27f, 0.0f);
	glVertex3f(-0.32f, -0.25f, 0.0f);
	glVertex3f(-0.35f, -0.23f, 0.0f);

	glEnd();

	///गर्भगृह पहिला  मजला वरील ३d दाखवायला काढलेला चौकोन वरील पट्टा 1
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.35f, -0.5f, 0.0f);
	glVertex3f(-0.32f, -0.52f, 0.0f);
	glVertex3f(-0.32f, -0.5f, 0.0f);
	glVertex3f(-0.35f, -0.48f, 0.0f);

	glEnd();

	///गर्भगृह पहिला मजला वरील  ३d दाखवायला काढलेला चौकोन वरील पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.35f, -0.48f, 0.0f);
	glVertex3f(-0.32f, -0.5f, 0.0f);
	glVertex3f(-0.32f, -0.48f, 0.0f);
	glVertex3f(-0.35f, -0.46f, 0.0f);

	glEnd();

	///गर्भगृह पुढचा काढलेला चौकोन 
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(-0.32f, -0.05f, 0.0f);
	glVertex3f(-0.15f, -0.05f, 0.0f);
	glVertex3f(-0.15f, -0.7f, 0.0f);
	glVertex3f(-0.32f, -0.7f, 0.0f);

	glEnd();

	
	Gauri_Khamb(-0.29, -0.56);
	Gauri_Khamb(-0.26, -0.56);

	///गर्भगृह पुढचा चौकोन वरील तिसरा मजला  पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.32f, -0.05f, 0.0f);
	glVertex3f(-0.15f, -0.05f, 0.0f);
	glVertex3f(-0.15f,-0.03f, 0.0f);
	glVertex3f(-0.32f,-0.03f, 0.0f);

	glEnd();

	///गर्भगृह पुढचा चौकोन वरील तिसरा मजला पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.32f, -0.03f, 0.0f);
	glVertex3f(-0.15f, -0.03f, 0.0f);
	glVertex3f(-0.15f, -0.01f, 0.0f);
	glVertex3f(-0.32f, -0.01f, 0.0f);

	glEnd();

	///गर्भगृह पुढचा चौकोन वरील दूसरा  मजला  पट्टा १  
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.32f, -0.29f, 0.0f);
	glVertex3f(-0.15f, -0.29f, 0.0f);
	glVertex3f(-0.15f, -0.27f, 0.0f);
	glVertex3f(-0.32f, -0.27f, 0.0f);

	glEnd();

	///गर्भगृह पुढचा चौकोन वरील दूसरा मजला पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.32f, -0.25f, 0.0f);
	glVertex3f(-0.15f, -0.25f, 0.0f);
	glVertex3f(-0.15f, -0.27f, 0.0f);
	glVertex3f(-0.32f, -0.27f, 0.0f);

	glEnd();

	///गर्भगृह पुढचा चौकोन वरील पहिला मजला  पट्टा १   
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.32f, -0.52f, 0.0f);
	glVertex3f(-0.15f, -0.52f, 0.0f);
	glVertex3f(-0.15f, -0.5f, 0.0f);
	glVertex3f(-0.32f, -0.5f, 0.0f);

	glEnd();

	///गर्भगृह पुढचा चौकोन वरील पहिला मजला पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.32f, -0.5f, 0.0f);
	glVertex3f(-0.15f, -0.5f, 0.0f);
	glVertex3f(-0.15f, -0.48f, 0.0f);
	glVertex3f(-0.32f, -0.48f, 0.0f);

	glEnd();

	/////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.38f, -0.52f, 0.0f);
	glVertex3f(-0.21f, -0.53, 0.0f);
	glVertex3f(-0.22f, -0.5f, 0.0f);
	glVertex3f(-0.36f, -0.5f, 0.0f);

	glEnd();

	/////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा 2
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.36f, -0.48f, 0.0f);
	glVertex3f(-0.22f, -0.48f, 0.0f);
	glVertex3f(-0.22f, -0.5f, 0.0f);
	glVertex3f(-0.36f, -0.5f, 0.0f);

	glEnd();

	/////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.36f, -0.46f, 0.0f);
	glVertex3f(-0.24f, -0.46f, 0.0f);
	glVertex3f(-0.24f, -0.48f, 0.0f);
	glVertex3f(-0.36f, -0.48f, 0.0f);

	glEnd();

	////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा 4
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.35f, -0.44f, 0.0f);
	glVertex3f(-0.25f, -0.44f, 0.0f);
	glVertex3f(-0.25f, -0.46f, 0.0f);
	glVertex3f(-0.35f, -0.46f, 0.0f);

	glEnd();

	////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा 5
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.34f, -0.42f, 0.0f);
	glVertex3f(-0.26f, -0.42f, 0.0f);
	glVertex3f(-0.26f, -0.44f, 0.0f);
	glVertex3f(-0.34f, -0.44f, 0.0f);

	glEnd();
	////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा 6
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.33f, -0.4f, 0.0f);
	glVertex3f(-0.27f, -0.4f, 0.0f);
	glVertex3f(-0.27f, -0.42f, 0.0f);
	glVertex3f(-0.33f, -0.42f, 0.0f);

	glEnd();

	////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा 7 
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-0.32f, -0.38f, 0.0f);
	glVertex3f(-0.28f, -0.38f, 0.0f);
	glVertex3f(-0.28f, -0.4f, 0.0f);
	glVertex3f(-0.32f, -0.4f, 0.0f);

	glEnd();

	////गर्भगृह  ३d दाखवायला काढलेला चौकोन पहिला मजला  मंदिर 3 कलस पट्टा पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(-0.31f, -0.36f, 0.0f);
	glVertex3f(-0.29f, -0.36f, 0.0f);
	glVertex3f(-0.29f, -0.38f, 0.0f);
	glVertex3f(-0.31f, -0.38f, 0.0f);

	glEnd();

	///गर्भगृहप्रवेशद्वारचा पुढचा चौकोन 3d दाखवायला   
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.15f, -0.05f, 0.0f);
	glVertex3f(-0.12f, -0.05f, 0.0f);
	glVertex3f(-0.12f, -0.67f, 0.0f);
	glVertex3f(-0.15f, -0.67f, 0.0f);

	glEnd();

	//सभामंड़प चौकोन पहिला 
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(-0.15f, -0.27f, 0.0f);
	glVertex3f(0.2f,-0.27f, 0.0f);
	glVertex3f(0.2f, -0.7f, 0.0f);
	glVertex3f(-0.15f, -0.7f, 0.0f);

	glEnd();

	//सभामंड़प 3d दाखवायचा छोटा चौकोन 

	glBegin(GL_QUADS);

	glColor3f(0.388235, 0.247059, 0.231373);
	glVertex3f(-0.15f, -0.4f, 0.0f);
	glVertex3f(-0.07f, -0.4f, 0.0f);
	glVertex3f(-0.07f, -0.7f, 0.0f);
	glVertex3f(-0.15f, -0.7f, 0.0f);

	glEnd();

    
	//सभामंड़प पहिला मजला खाम्ब 
	Gauri_Khamb(-0.09, -0.33);
	Gauri_Khamb(-0.04, -0.33);
	Gauri_Khamb(0.05, -0.33);
	Gauri_Khamb(0.1, -0.33);
	Gauri_Khamb(0.18, -0.33);

	
    //सभामंड़प पहिला चौकोन पहिला मजला पट्टा 2
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(-0.09f, -0.49f, 0.0f);
	  glVertex3f(0.22f, -0.49f, 0.0f);
	  glVertex3f(0.22f, -0.42f, 0.0f);
	  glVertex3f(-0.09f, -0.42f, 0.0f);

	  glEnd();

	  //सभामंड़प पहिला चौकोन  पहिला मजला पट्टा १  
	  glBegin(GL_QUADS);

	  glColor3f(0.894118, 0.756863, 0.729412);
	  glVertex3f(-0.15f, -0.25f, 0.0f);
	  glVertex3f(0.21f, -0.25f, 0.0f);
	  glVertex3f(0.23f, -0.29f, 0.0f);
	  glVertex3f(-0.17f, -0.29f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस पट्टा 3
	  glBegin(GL_QUADS);

	  glColor3f(0.341176, 0.188235, 0.184314);
	  glVertex3f(-0.13f, -0.23f, 0.0f);
	  glVertex3f(0.20f, -0.23f, 0.0f);
	  glVertex3f(0.20f, -0.25f, 0.0f);
	  glVertex3f(-0.13f, -0.25f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस  पट्टा 4
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(-0.11f, -0.21f, 0.0f);
	  glVertex3f(0.18f, -0.21f, 0.0f);
	  glVertex3f(0.18f, -0.23f, 0.0f);
	  glVertex3f(-0.11f, -0.23f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस पट्टा 5
	  glBegin(GL_QUADS);

	  glColor3f(0.341176, 0.188235, 0.184314);
	  glVertex3f(-0.09f, -0.19f, 0.0f);
	  glVertex3f(0.16f, -0.19f, 0.0f);
	  glVertex3f(0.16f, -0.21f, 0.0f);
	  glVertex3f(-0.09f, -0.21f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस  पट्टा 6
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(-0.07f, -0.17f, 0.0f);
	  glVertex3f(0.14f, -0.17f, 0.0f);
	  glVertex3f(0.14f, -0.19f, 0.0f);
	  glVertex3f(-0.07f, -0.19f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस पट्टा 7
	  glBegin(GL_QUADS);

	  glColor3f(0.341176, 0.188235, 0.184314);
	  glVertex3f(-0.05f, -0.15f, 0.0f);
	  glVertex3f(0.12f, -0.15f, 0.0f);
	  glVertex3f(0.12f, -0.17f, 0.0f);
	  glVertex3f(-0.05f, -0.17f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस  पट्टा 8
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(-0.03f, -0.13f, 0.0f);
	  glVertex3f(0.10f, -0.13f, 0.0f);
	  glVertex3f(0.10f, -0.15f, 0.0f);
	  glVertex3f(-0.03f, -0.15f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस पट्टा 9
	  glBegin(GL_QUADS);

	  glColor3f(0.341176, 0.188235, 0.184314);
	  glVertex3f(-0.01f, -0.11f, 0.0f);
	  glVertex3f(0.08f, -0.11f, 0.0f);
	  glVertex3f(0.08f, -0.13f, 0.0f);
	  glVertex3f(-0.01f, -0.13f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस  पट्टा 10
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(0.01f, -0.09f, 0.0f);
	  glVertex3f(0.06f, -0.09f, 0.0f);
	  glVertex3f(0.06f, -0.11f, 0.0f);
	  glVertex3f(0.01f, -0.11f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला मंदिर कलस पिवला
	  glBegin(GL_QUADS);

	  glColor3f(0.996078, 0.823529, 0.043137);
	  glVertex3f(0.02f, -0.07f, 0.0f);
	  glVertex3f(0.05f, -0.07f, 0.0f);
	  glVertex3f(0.05f, -0.09f, 0.0f);
	  glVertex3f(0.02f, -0.09f, 0.0f);

	  glEnd();

	  //////सभामंड़प पहिला चौकोन पहिला मजला पुढचे मंदिर कलस पट्टा 3
	  glBegin(GL_QUADS);

	  glColor3f(0.341176, 0.188235, 0.184314);
	  glVertex3f(-0.07f, -0.26f, 0.0f);
	  glVertex3f(0.13f, -0.26f, 0.0f);
	  glVertex3f(0.13f, -0.27f, 0.0f);
	  glVertex3f(-0.07f, -0.27f, 0.0f);

	  glEnd();

	  //////सभामंड़प पहिला चौकोन पहिला मजला पुढचे मंदिर कलस पट्टा 4
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(-0.05f, -0.24f, 0.0f);
	  glVertex3f(0.11f, -0.24f, 0.0f);
	  glVertex3f(0.11f, -0.26f, 0.0f);
	  glVertex3f(-0.05f, -0.26f, 0.0f);

	  glEnd();

	  //////सभामंड़प पहिला चौकोन पहिला मजला पुढचे मंदिर कलस पट्टा 5
	  glBegin(GL_QUADS);

	  glColor3f(0.639216, 0.392157, 0.388235);
	  glVertex3f(-0.03f, -0.22f, 0.0f);
	  glVertex3f(0.09f, -0.22f, 0.0f);
	  glVertex3f(0.09f, -0.24f, 0.0f);
	  glVertex3f(-0.03f, -0.24f, 0.0f);

	  glEnd();

	  //////सभामंड़प पहिला चौकोन पहिला मजला पुढचे मंदिर कलस पट्टा 6
	  glBegin(GL_QUADS);

	  glColor3f(0.643137, 0.494118, 0.478431);
	  glVertex3f(-0.01f, -0.2f, 0.0f);
	  glVertex3f(0.07f, -0.2f, 0.0f);
	  glVertex3f(0.07f, -0.22f, 0.0f);
	  glVertex3f(-0.01f, -0.22f, 0.0f);

	  glEnd();

	  //////सभामंड़प पहिला चौकोन पहिला मजला पुढचे मंदिर कलस पट्टा 7
	  glBegin(GL_QUADS);

	  glColor3f(0.639216, 0.392157, 0.388235);
	  glVertex3f(0.01f, -0.19f, 0.0f);
	  glVertex3f(0.05f, -0.19f, 0.0f);
	  glVertex3f(0.05f, -0.2f, 0.0f);
	  glVertex3f(0.01f, -0.2f, 0.0f);

	  glEnd();

	  ////सभामंड़प पहिला चौकोन पहिला मजला पुढचे मंदिर कलस पिवला
	  glBegin(GL_QUADS);

	  glColor3f(0.996078, 0.823529, 0.043137);
	  glVertex3f(0.02f, -0.17f, 0.0f);
	  glVertex3f(0.04f, -0.17f, 0.0f);
	  glVertex3f(0.04f, -0.19f, 0.0f);
	  glVertex3f(0.02f, -0.19f, 0.0f);

	  glEnd();

	//सभामंड़प सगळ्यात खालचे खाम्ब 
	Gauri_Khamb(-0.09, -0.55);
	Gauri_Khamb(-0.04, -0.55);
	Gauri_Khamb(0.05, -0.55);
	Gauri_Khamb(0.1, -0.55);
	
		//सभामंड़प चौकोन 2
		glBegin(GL_QUADS);

		glColor3f(0.254902, 0.129412, 0.145098);
		glVertex3f(0.2f, -0.5f, 0.0f);
		glVertex3f(0.6f, -0.5f, 0.0f);
		glVertex3f(0.6f, -0.7f, 0.0f);
		glVertex3f(0.2f, -0.7f, 0.0f);
	
		glEnd();
	
		//सभामंड़प चौकोन 2 वरील पहिला मजला चौकोन 
		glBegin(GL_QUADS);
	
		glColor3f(0.643137, 0.494118, 0.478431);
		glVertex3f(0.23f, -0.5f, 0.0f);
		glVertex3f(0.45f, -0.5f, 0.0f);
		glVertex3f(0.45f, -0.39f, 0.0f);
		glVertex3f(0.23f, -0.39f, 0.0f);
	
		glEnd();
	
		/////सभामंड़प चौकोन 2 वरील पहिला मजला चौकोन  मंदिर कलस पट्टा १ 
		glBegin(GL_QUADS);
	
		glColor3f(0.894118, 0.756863, 0.729412);
		glVertex3f(0.21f, -0.39f, 0.0f);
		glVertex3f(0.48f, -0.39, 0.0f);
		glVertex3f(0.46f, -0.37f, 0.0f);
		glVertex3f(0.23f, -0.37f, 0.0f);
	
		glEnd();
	
		////सभामंड़प चौकोन 2 वरील पहिला मजला र्चौकोन मंदिर कलस पट्टा 2
		glBegin(GL_QUADS);
	
		glColor3f(0.341176, 0.188235, 0.184314);
		glVertex3f(0.23f, -0.36f, 0.0f);
		glVertex3f(0.45f, -0.36f, 0.0f);
		glVertex3f(0.45f, -0.37f, 0.0f);
		glVertex3f(0.23f, -0.37f, 0.0f);
	
		glEnd();
	
		////सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा 3
		glBegin(GL_QUADS);
	
		glColor3f(0.643137, 0.494118, 0.478431);
		glVertex3f(0.24f, -0.35f, 0.0f);
		glVertex3f(0.44f, -0.35f, 0.0f);
		glVertex3f(0.44f, -0.36f, 0.0f);
		glVertex3f(0.24f, -0.36f, 0.0f);
	
		glEnd();
	
		///सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा  4
		glBegin(GL_QUADS);
	
		glColor3f(0.341176, 0.188235, 0.184314);
		glVertex3f(0.25f, -0.34f, 0.0f);
		glVertex3f(0.43f, -0.34f, 0.0f);
		glVertex3f(0.43f, -0.35f, 0.0f);
		glVertex3f(0.25f, -0.35f, 0.0f);
	
		glEnd();
	
		////सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा 5
		glBegin(GL_QUADS);
	
		glColor3f(0.643137, 0.494118, 0.478431);
		glVertex3f(0.26f, -0.33f, 0.0f);
		glVertex3f(0.42f, -0.33f, 0.0f);
		glVertex3f(0.42f, -0.34f, 0.0f);
		glVertex3f(0.26f, -0.34f, 0.0f);
	
		glEnd();
	
		///सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा  6
		glBegin(GL_QUADS);
	
		glColor3f(0.341176, 0.188235, 0.184314);
		glVertex3f(0.27f, -0.32f, 0.0f);
		glVertex3f(0.41f, -0.32f, 0.0f);
		glVertex3f(0.41f, -0.33f, 0.0f);
		glVertex3f(0.27f, -0.33f, 0.0f);
	
		glEnd();
	
		////सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा 7
		glBegin(GL_QUADS);
	
		glColor3f(0.643137, 0.494118, 0.478431);
		glVertex3f(0.28f, -0.31f, 0.0f);
		glVertex3f(0.41f, -0.31f, 0.0f);
		glVertex3f(0.41f, -0.32f, 0.0f);
		glVertex3f(0.28f, -0.32f, 0.0f);
	
		glEnd();
	
		///सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा  8
		glBegin(GL_QUADS);
	
		glColor3f(0.341176, 0.188235, 0.184314);
		glVertex3f(0.29f, -0.3f, 0.0f);
		glVertex3f(0.4f, -0.3f, 0.0f);
		glVertex3f(0.4f, -0.31f, 0.0f);
		glVertex3f(0.29f, -0.31f, 0.0f);
	
		glEnd();
	
		////सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा 9
		glBegin(GL_QUADS);
	
		glColor3f(0.643137, 0.494118, 0.478431);
		glVertex3f(0.30f, -0.29f, 0.0f);
		glVertex3f(0.39f, -0.29f, 0.0f);
		glVertex3f(0.39f, -0.3f, 0.0f);
		glVertex3f(0.30f, -0.3f, 0.0f);
	
		glEnd();
	
		///सभामंड़प चौकोन 2 पहिला मजला र्चौकोन मंदिर कलस पट्टा  10
		glBegin(GL_QUADS);
	
		glColor3f(0.341176, 0.188235, 0.184314);
		glVertex3f(0.31f, -0.28f, 0.0f);
		glVertex3f(0.38f, -0.28f, 0.0f);
		glVertex3f(0.38f, -0.29f, 0.0f);
		glVertex3f(0.31f, -0.29f, 0.0f);
	
		glEnd();
	
		////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पिवला 
		glBegin(GL_QUADS);
	
		glColor3f(0.996078, 0.823529, 0.043137);
		glVertex3f(0.33f, -0.26f, 0.0f);
		glVertex3f(0.36f, -0.26f, 0.0f);
		glVertex3f(0.36f, -0.28f, 0.0f);
		glVertex3f(0.33f, -0.28f, 0.0f);
	
		glEnd();
	
	//सभामंड़प चौकोन 2 सगळ्यात खालचे खाम्ब 
	Gauri_Khamb(0.2, -0.56);
	Gauri_Khamb(0.27, -0.56);
	Gauri_Khamb(0.34, -0.56);
	Gauri_Khamb(0.41, -0.56);
	Gauri_Khamb(0.45, -0.58);
	Gauri_Khamb(0.51, -0.58);
	Gauri_Khamb(0.57, -0.58);
	
    // सभामंड़प चौकोन  1 सगळ्यात खालचे  पट्टा १  
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(-0.08f, -0.48f, 0.0f);
	glVertex3f(0.2f, -0.48f, 0.0f);
	glVertex3f(0.22f, -0.51f, 0.0f);
	glVertex3f(-0.1f, -0.51f, 0.0f);

	glEnd();

	//सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर १ पट्टा १  
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(0.15f, -0.5f, 0.0f);
	glVertex3f(0.45f, -0.5f, 0.0f);
	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.48f, -0.53f, 0.0f);
	glVertex3f(0.13f, -0.53f, 0.0f);

	glEnd();

	//सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर १ पट्टा 2 
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.45f, -0.48f, 0.0f);
	glVertex3f(0.14f, -0.48f, 0.0f);
	glVertex3f(0.16f, -0.5f, 0.0f);
	glVertex3f(0.45f, -0.5f, 0.0f);

	glEnd();

	/////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर १ कलस पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.28f, -0.46f, 0.0f);
	glVertex3f(0.43, -0.46, 0.0f);
	glVertex3f(0.44f, -0.48f, 0.0f);
	glVertex3f(0.27f, -0.48f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर १ कलस पट्टा  2
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.28f, -0.45f, 0.0f);
	glVertex3f(0.43f, -0.45f, 0.0f);
	glVertex3f(0.43f, -0.46f, 0.0f);
	glVertex3f(0.28f, -0.46f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 1 कलस पट्टा  3
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.29f, -0.44f, 0.0f);
	glVertex3f(0.42f, -0.44f, 0.0f);
	glVertex3f(0.42f, -0.45f, 0.0f);
	glVertex3f(0.29f, -0.45f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 1 कलस पट्टा  4
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.3f, -0.43f, 0.0f);
	glVertex3f(0.41f, -0.43f, 0.0f);
	glVertex3f(0.41f, -0.44f, 0.0f);
	glVertex3f(0.3f, -0.44f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 1 कलस पट्टा  5
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.31f, -0.42f, 0.0f);
	glVertex3f(0.4f, -0.42f, 0.0f);
	glVertex3f(0.4f, -0.43f, 0.0f);
	glVertex3f(0.31f, -0.43f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 1 कलस पट्टा  6
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.32f, -0.41f, 0.0f);
	glVertex3f(0.39f, -0.41f, 0.0f);
	glVertex3f(0.39f, -0.42f, 0.0f);
	glVertex3f(0.32f, -0.42f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 1 कलस पट्टा  7
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.33f, -0.4f, 0.0f);
	glVertex3f(0.38f, -0.4f, 0.0f);
	glVertex3f(0.38f, -0.41f, 0.0f);
	glVertex3f(0.33f, -0.41f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 1 कलस पट्टा  8
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.34f, -0.39f, 0.0f);
	glVertex3f(0.37f, -0.39f, 0.0f);
	glVertex3f(0.37f, -0.4f, 0.0f);
	glVertex3f(0.34f, -0.4f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(0.35f, -0.37f, 0.0f);
	glVertex3f(0.36f, -0.37f, 0.0f);
	glVertex3f(0.36f, -0.39f, 0.0f);
	glVertex3f(0.35f, -0.39f, 0.0f);

	glEnd();

	//सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 पट्टा १  
	glBegin(GL_QUADS);

	glColor3f(0.745098, 0.619608, 0.619608);
	glVertex3f(0.45f, -0.52f, 0.0f);
	glVertex3f(0.62f, -0.52f, 0.0f);
	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.64f, -0.55f, 0.0f);
	glVertex3f(0.43f, -0.55f, 0.0f);

	glEnd();

	//सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 पट्टा 2 
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.45f, -0.52f, 0.0f);
	glVertex3f(0.62f, -0.52f, 0.0f);
	glVertex3f(0.62f, -0.5f, 0.0f);
	glVertex3f(0.43f, -0.5f, 0.0f);

	glEnd();

	/////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.49f, -0.49f, 0.0f);
	glVertex3f(0.62, -0.49, 0.0f);
	glVertex3f(0.62f, -0.5f, 0.0f);
	glVertex3f(0.49f, -0.5f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पट्टा  2
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.5f, -0.48f, 0.0f);
	glVertex3f(0.61f, -0.48f, 0.0f);
	glVertex3f(0.61f, -0.49f, 0.0f);
	glVertex3f(0.5f, -0.49f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पट्टा  3
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(0.51f, -0.47f, 0.0f);
	glVertex3f(0.6f, -0.47f, 0.0f);
	glVertex3f(0.6f, -0.48f, 0.0f);
	glVertex3f(0.51f, -0.48f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पट्टा  4
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.52f, -0.46f, 0.0f);
	glVertex3f(0.59f, -0.46f, 0.0f);
	glVertex3f(0.59f, -0.47f, 0.0f);
	glVertex3f(0.52f, -0.47f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पट्टा  5
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(0.53f, -0.45f, 0.0f);
	glVertex3f(0.58f, -0.45f, 0.0f);
	glVertex3f(0.58f, -0.46f, 0.0f);
	glVertex3f(0.53f, -0.46f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पट्टा  6
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.54f, -0.44f, 0.0f);
	glVertex3f(0.57f, -0.44f, 0.0f);
	glVertex3f(0.57f, -0.45f, 0.0f);
	glVertex3f(0.54f, -0.45f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर 2 कलस पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(0.55f, -0.42f, 0.0f);
	glVertex3f(0.56f, -0.42f, 0.0f);
	glVertex3f(0.56f, -0.44f, 0.0f);
	glVertex3f(0.55f, -0.44f, 0.0f);

	glEnd();

	/////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.43f, -0.49f, 0.0f);
	glVertex3f(0.54, -0.49, 0.0f);
	glVertex3f(0.54f, -0.51f, 0.0f);
	glVertex3f(0.43f, -0.51f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पट्टा  2
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.44f, -0.48f, 0.0f);
	glVertex3f(0.53f, -0.48f, 0.0f);
	glVertex3f(0.53f, -0.49f, 0.0f);
	glVertex3f(0.44f, -0.49f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पट्टा  3
	glBegin(GL_QUADS);


	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.45f, -0.47f, 0.0f);
	glVertex3f(0.54f, -0.47f, 0.0f);
	glVertex3f(0.54f, -0.48f, 0.0f);
	glVertex3f(0.45f, -0.48f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पट्टा  4
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.46f, -0.46f, 0.0f);
	glVertex3f(0.53f, -0.46f, 0.0f);
	glVertex3f(0.53f, -0.47f, 0.0f);
	glVertex3f(0.46f, -0.47f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पट्टा  5
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(0.47f, -0.45f, 0.0f);
	glVertex3f(0.52f, -0.45f, 0.0f);
	glVertex3f(0.52f, -0.46f, 0.0f);
	glVertex3f(0.47f, -0.46f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पट्टा  6
	glBegin(GL_QUADS);

	glColor3f(0.341176, 0.188235, 0.184314);
	glVertex3f(0.48f, -0.44f, 0.0f);
	glVertex3f(0.51f, -0.44f, 0.0f);
	glVertex3f(0.51f, -0.45f, 0.0f);
	glVertex3f(0.48f, -0.45f, 0.0f);

	glEnd();

	////सभामंड़प चौकोन 2 सगळ्यात खालचे मंदिर मधील  कलस पिवला 
	glBegin(GL_QUADS);

	glColor3f(0.996078, 0.823529, 0.043137);
	glVertex3f(0.49f, -0.42f, 0.0f);
	glVertex3f(0.5f, -0.42f, 0.0f);
	glVertex3f(0.5f, -0.44f, 0.0f);
	glVertex3f(0.49f, -0.44f, 0.0f);

	glEnd();

	//सभागृह पुढची पायरी पट्टा १ 
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(0.6f, -0.73f, 0.0f);
	glVertex3f(0.65f, -0.73f, 0.0f);
	glVertex3f(0.65f, -0.75f, 0.0f);
	glVertex3f(0.6f, -0.75f, 0.0f);

	glEnd();

	//सभागृह पुढची पायरी पट्टा २  
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(0.6f, -0.73f, 0.0f);
	glVertex3f(0.65f, -0.73f, 0.0f);
	glVertex3f(0.65f, -0.71f, 0.0f);
	glVertex3f(0.6f, -0.71f, 0.0f);

	glEnd();

	//सभागृह पुढची पायरी पट्टा 3
	glBegin(GL_QUADS);

	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(0.65f, -0.75f, 0.0f);
	glVertex3f(1.0f, -0.75f, 0.0f);
	glVertex3f(1.0f, -0.74f, 0.0f);
	glVertex3f(0.65f, -0.74f, 0.0f);

	glEnd();

	///जमीन 
	glBegin(GL_QUADS);

	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(-1.0f, -0.75f, 0.0f);
	glVertex3f(1.0f, -0.75f, 0.0f);
	glVertex3f(1.0f, -0.85f, 0.0f);
	glVertex3f(-1.0f, -0.85f, 0.0f);

	glEnd();

	//गवत 

	glBegin(GL_QUADS);

	glColor3f(0.231373, 0.709804, 0.298039);
	glVertex3f(-1.0f, -0.85f, 0.0f);
	glVertex3f(1.0f, -0.85f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glEnd();

	float x, y, wave, amp_first_wave = 0.03f;

	///first wave
	glBegin(GL_TRIANGLE_STRIP);
	for (float x = -1.0; x <= 1.0; x += 0.005)
	{
		wave = amp_first_wave * sin(x * 60);

		glColor3f(0.541176, 0.764706, 0.219608);
		glVertex3f(x, (-0.82 + wave), 0.0f);
		glColor3f(0.231373, 0.709804, 0.298039);
		glVertex3f(x, (-0.9 + wave), 0.0f);//grass chi width sathi

	}

	glEnd();

	Gauri_Khamb(-0.98,-0.55);
	Gauri_Khamb(-0.92, -0.55);
	Gauri_Khamb(-0.85, -0.55);
	
	Gauri_Khamb(-0.76, -0.54);
	Gauri_Khamb(-0.78, -0.55);
	Gauri_Khamb(-0.7, -0.55);

    ///र्चौकोन बेस  1
	glBegin(GL_QUADS);

	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(-0.98f, -0.69f, 0.0f);
	glVertex3f(0.6f, -0.69f, 0.0f);
	glVertex3f(0.6f, -0.72f, 0.0f);
	glVertex3f(-0.98f, -0.72f, 0.0f);

	glEnd();

	///र्चौकोन बेस  2
	glBegin(GL_QUADS);

	glColor3f(0.639216, 0.392157, 0.388235);
	glVertex3f(-0.98f, -0.72f, 0.0f);
	glVertex3f(0.6f, -0.72f, 0.0f);
	glVertex3f(0.6f, -0.75f, 0.0f);
	glVertex3f(-0.98f, -0.75f, 0.0f);

	glEnd();
	
	Gauri_Mandir_Kalas(0.0f, 0.0f);
	//Gauri_Mandir_Kalas(0.1f, 0.8f);
	Gauri_Mandir_Kalas_paya(0.0f, 0.0f);

}

	
void Gauri_Mandir_Kalas(float x_pos, float y_pos)
{

	float x6[4], y6[4], xt6[200], yt6[200];
	float x7[4], y7[4], xt7[200], yt7[200];
	
	float t;
	int i;

	x6[0] = -0.8; y6[0] = 0.63;
	x6[1] = -0.83; y6[1] = 0.65;
	x6[2] = -0.82; y6[2] = 0.67;
	x6[3] = -0.81; y6[3] = 0.7;

	x7[0] = -0.81; y7[0] = 0.63;
	x7[1] = -0.79; y7[1] = 0.65;
	x7[2] = -0.8; y7[2] = 0.67;
	x7[3] = -0.81; y7[3] = 0.7;

	for (i = 0, t = 0; t < 1; i++, t = t + 0.01)
	{
		xt6[i] = pow(1 - t, 3) * x6[0]+ 3 * t * pow(1 - t, 2) * x6[1] + 3 * pow(t, 2) * (1 - t) * x6[2] + pow(t, 3) * x6[3] ;
		yt6[i] = pow(1 - t, 3) * y6[0] + 3 * t * pow(1 - t, 2) * y6[1] + 3 * pow(t, 2) * (1 - t) * y6[2] + pow(t, 3) * y6[3] ;

		xt7[i] = pow(1 - t, 3) * x7[0] + 3 * t * pow(1 - t, 2) * x7[1] + 3 * pow(t, 2) * (1 - t) * x7[2] + pow(t, 3) * x7[3] ;
		yt7[i] = pow(1 - t, 3) * y7[0] + 3 * t * pow(1 - t, 2) * y7[1] + 3 * pow(t, 2) * (1 - t) * y7[2] + pow(t, 3) * y7[3] ;

	}
	
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		glColor3f(0.996078, 0.823529, 0.043137);
		glVertex2f(xt6[i]+x_pos, yt6[i] + y_pos);
		glColor3f(0.996078, 0.823529, 0.043137);
		glVertex2f(xt7[i] + x_pos, yt7[i] + y_pos);

	}
	glEnd();
}

void Gauri_Mandir_Kalas_paya(float x_pos, float y_pos) 
{
	float x[10], y[10], t, xt[200], yt[200];
	float x1[4], y1[4], xt1[200], yt1[200];
	float x2[4], y2[4], xt2[200], yt2[200];
	float x3[4], y3[4], xt3[200], yt3[200];
	float x4[4], y4[4], xt4[200], yt4[200];
	float x5[4], y5[4], xt5[200], yt5[200];
	float x8[4], y8[4], xt8[200], yt8[200];
	float x9[4], y9[4], xt9[200], yt9[200];

   int i;

   //zenda
   
   glBegin(GL_QUADS);

   glColor3f(0.996078, 0.823529, 0.043137);
   glVertex3f(-0.83, 0.58, 0.0);//76
   glVertex3f(-0.83, 0.85, 0.0);
   glVertex3f(-0.84, 0.85, 0.0);//77
   glVertex3f(-0.84, 0.58, 0.0);

   glEnd();

	x[0] = -0.97; y[0] = -0.02;
	x[1] = -0.95; y[1] = 0.1;
	x[2] = -0.93; y[2] = 0.3;
	x[3] = -0.87; y[3] = 0.5;

	x1[0] = -0.65; y1[0] = -0.02;
	x1[1] = -0.67; y1[1] = 0.1;
	x1[2] = -0.69; y1[2] = 0.3;
	x1[3] = -0.75; y1[3] = 0.5;

	x2[0] = -0.87; y2[0] = 0.49;
	x2[1] = -0.89; y2[1] = 0.53;
	x2[2] = -0.91; y2[2] = 0.56;
	x2[3] = -0.87; y2[3] = 0.59;
	
	x3[0] = -0.75; y3[0] = 0.49;
	x3[1] = -0.73; y3[1] = 0.53;
	x3[2] = -0.71; y3[2] = 0.56;
	x3[3] = -0.75; y3[3] = 0.59;

	x4[0] = -0.83; y4[0] = 0.58;
	x4[1] = -0.85; y4[1] = 0.6;
	x4[2] = -0.87; y4[2] = 0.62;
	x4[3] = -0.83; y4[3] = 0.64;

	x5[0] = -0.79; y5[0] = 0.58;
	x5[1] = -0.77; y5[1] = 0.6;
	x5[2] = -0.75; y5[2] = 0.62;
	x5[3] = -0.79; y5[3] = 0.64;

	x8[0] = -0.68; y8[0] = 0.9;
	x8[1] = -0.72; y8[1] = 0.7;
	x8[2] = -0.74; y8[2] = 0.95;
	x8[3] = -0.84; y8[3] = 0.85;

	x9[0] = -0.68; y9[0] = 0.9;
	x9[1] = -0.72; y9[1] = 0.6;
	x9[2] = -0.74; y9[2] = 0.85;
	x9[3] = -0.84; y9[3] = 0.75;
	
	for (i = 0, t = 0; t < 1; i++, t = t + 0.01)
	{

		xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
		yt[i] = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];

		xt1[i] = pow(1 - t, 3) * x1[0] + 3 * t * pow(1 - t, 2) * x1[1] + 3 * pow(t, 2) * (1 - t) * x1[2] + pow(t, 3) * x1[3];
		yt1[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];

		xt2[i] = pow(1 - t, 3) * x2[0] + 3 * t * pow(1 - t, 2) * x2[1] + 3 * pow(t, 2) * (1 - t) * x2[2] + pow(t, 3) * x2[3];
		yt2[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];

		xt3[i] = pow(1 - t, 3) * x3[0] + 3 * t * pow(1 - t, 2) * x3[1] + 3 * pow(t, 2) * (1 - t) * x3[2] + pow(t, 3) * x3[3];
		yt3[i] = pow(1 - t, 3) * y3[0] + 3 * t * pow(1 - t, 2) * y3[1] + 3 * pow(t, 2) * (1 - t) * y3[2] + pow(t, 3) * y3[3];

		xt4[i] = pow(1 - t, 3) * x4[0] + 3 * t * pow(1 - t, 2) * x4[1] + 3 * pow(t, 2) * (1 - t) * x4[2] + pow(t, 3) * x4[3];
		yt4[i] = pow(1 - t, 3) * y4[0] + 3 * t * pow(1 - t, 2) * y4[1] + 3 * pow(t, 2) * (1 - t) * y4[2] + pow(t, 3) * y4[3];

		xt5[i] = pow(1 - t, 3) * x5[0] + 3 * t * pow(1 - t, 2) * x5[1] + 3 * pow(t, 2) * (1 - t) * x5[2] + pow(t, 3) * x5[3];
		yt5[i] = pow(1 - t, 3) * y5[0] + 3 * t * pow(1 - t, 2) * y5[1] + 3 * pow(t, 2) * (1 - t) * y5[2] + pow(t, 3) * y5[3];
	
		xt8[i] = pow(1 - t, 3) * x8[0] + 3 * t * pow(1 - t, 2) * x8[1] + 3 * pow(t, 2) * (1 - t) * x8[2] + pow(t, 3) * x8[3];
		yt8[i] = pow(1 - t, 3) * y8[0] + 3 * t * pow(1 - t, 2) * y8[1] + 3 * pow(t, 2) * (1 - t) * y8[2] + pow(t, 3) * y8[3];

		xt9[i] = pow(1 - t, 3) * x9[0] + 3 * t * pow(1 - t, 2) * x9[1] + 3 * pow(t, 2) * (1 - t) * x9[2] + pow(t, 3) * x9[3];
		yt9[i] = pow(1 - t, 3) * y9[0] + 3 * t * pow(1 - t, 2) * y9[1] + 3 * pow(t, 2) * (1 - t) * y9[2] + pow(t, 3) * y9[3];

	}
	
	
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		glColor3f(0.513726, 0.329412, 0.313726);
		glVertex2f(xt[i], yt[i]);
		glVertex2f(xt1[i], yt1[i]);

	}
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		glVertex2f(xt2[i], yt2[i]);
		glVertex2f(xt3[i], yt3[i]);

	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		glVertex2f(xt4[i], yt4[i]);
		glVertex2f(xt5[i], yt5[i]);

	}
	glEnd();

//zenda
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < 100; i++)
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(xt8[i], yt8[i], 0.0f); 
		glColor3f(1.0, 0.3, 0.0);
		glVertex3f(xt9[i], yt9[i], 0.0f); 
	}
	glEnd();

}



void Gauri_Khamb(float x_pos, float y_pos)
{
	//सगळ्यात वरचा चौकोन १ 
	glBegin(GL_QUADS);
	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(0.0f + x_pos, 0.05f + y_pos, 0.0f);
	glVertex3f(0.04f + x_pos, 0.05f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, 0.02f + y_pos, 0.0f);
	glVertex3f(0.01f + x_pos, 0.02f + y_pos, 0.0f);

	glEnd();

	//वरचा चौकोन २ 
	glBegin(GL_QUADS);
	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(0.01f + x_pos, 0.02f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, 0.02f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, 0.01f + y_pos, 0.0f);
	glVertex3f(0.01f + x_pos, 0.01f + y_pos, 0.0f);

	glEnd();

	//वरचा चौकोन 3
	glBegin(GL_QUADS);
	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.01f + x_pos, 0.01f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, 0.01f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, 0.0f + y_pos, 0.0f);
	glVertex3f(0.01f + x_pos, 0.0f + y_pos, 0.0f);

	glEnd();

	//उभा  चौकोन 
	glBegin(GL_QUADS);
	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(0.015f + x_pos, 0.0f + y_pos, 0.0f);
	glVertex3f(0.025f + x_pos, 0.0f + y_pos, 0.0f);
	glVertex3f(0.025f + x_pos, -0.1f + y_pos, 0.0f);
	glVertex3f(0.015f + x_pos, -0.1f + y_pos, 0.0f);

	glEnd();

	//खालचा चौकोन 1
	glBegin(GL_QUADS);
	glColor3f(0.894118, 0.756863, 0.729412);
	glVertex3f(0.01f + x_pos, -0.1f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, -0.1f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, -0.11f + y_pos, 0.0f);
	glVertex3f(0.01f + x_pos, -0.11f + y_pos, 0.0f);

	glEnd();

	//खालचा चौकोन २ 
	glBegin(GL_QUADS);
	glColor3f(0.254902, 0.129412, 0.145098);
	glVertex3f(0.01f + x_pos, -0.11f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, -0.11f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, -0.12f + y_pos, 0.0f);
	glVertex3f(0.01f + x_pos, -0.12f + y_pos, 0.0f);

	glEnd();

	//सगळ्यात खालचा  चौकोन 3
	glBegin(GL_QUADS);
	glColor3f(0.643137, 0.494118, 0.478431);
	glVertex3f(0.01f + x_pos, -0.12f + y_pos, 0.0f);
	glVertex3f(0.03f + x_pos, -0.12f + y_pos, 0.0f);
	glVertex3f(0.04f + x_pos, -0.15f + y_pos, 0.0f);
	glVertex3f(0.0f + x_pos, -0.15f + y_pos, 0.0f);

	glEnd();
}


////animation fuction
void dayUpdate(void)
{
	    
    
	  if(100.0f >=colorChageRed)
	  {
		colorChageRed=colorChageRed + 0.2;
		
	  }
	  if(100.0f >=colorChangeGreen)
	  {
	   colorChangeGreen=colorChangeGreen+0.2;
	  }
	  if(100.0f >=colorChangeBlue)
	  {
		colorChangeBlue=colorChangeBlue+0.2;
	  }

	  if(100.0f<=colorChangeBlue && 100.0f <=colorChangeGreen && 100.0f <=colorChageRed )
	  {
		colorFlagMorning=TRUE;
		/*
		colorChageRed=colorChageRed - 0.2;
        colorChangeGreen=colorChangeGreen+0.2;
		colorChangeBlue=colorChangeBlue+0.2;
		
		SetTimer(GRN_ghwnd,DAY_CHANGE_TIMER_AFTERNOON,0, NULL); 
		colorChageRedOne=colorChageRed;   
	    colorChangeGreenOne= colorChangeGreen;
	    colorChangeBlueOne=colorChangeBlue;
		*/
	  }

	SetTimer(ghwnd,DAY_CHANGE_TIMER,10, NULL); 
}
/*
void dayUpdateAfternoon(void)
{
    if(100.0f >=colorChageRed)
	  {
		colorChageRed=colorChageRed - 0.005;
		
	  }
	  if(100.0f >=colorChangeGreen)
	  {
	   colorChangeGreen=colorChangeGreen+0.005;
	  }
	  if(100.0f >=colorChangeBlue)
	  {
		colorChangeBlue=colorChangeBlue+0.005;
	  }

	SetTimer(GRN_ghwnd,DAY_CHANGE_TIMER_AFTERNOON,10, NULL); 
}
	*/