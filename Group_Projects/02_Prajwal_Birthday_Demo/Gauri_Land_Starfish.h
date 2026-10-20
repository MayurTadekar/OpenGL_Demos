#include <GL/freeglut.h>

extern void Gauri_water(float x_pos,float y_pos,float  percent);
extern void Gauri_land(float x_pos, float y_pos, float  percent);
extern void Gauri_Shankh(float x_pos, float y_pos, float percent);
extern void Gauri_Grass_one(float x_pos, float y_pos, float percent, float delta_wave_factor,float wave_factor);
extern void Gauri_Grass_two(float x_pos, float y_pos, float percent, float delta_wave_factor, float wave_factor);
extern void Gauri_Grass_four(float x_pos, float y_pos, float percent, float delta_wave_factor, float wave_factor);
extern void Gauri_Grass_three(float x_pos, float y_pos, float percent, float delta_wave_factor, float wave_factor);
extern void Gauri_Kasav(float x_pos,float y_pos,float  percent, float Ypercent);
extern void Gauri_Starfish( float x_pos, float y_pos, float percent);

void Gauri_water(float x_pos,float y_pos,float  percent)
{
	glBegin(GL_QUADS);

	//1.0, 0.99999, 0.964706
	glColor3f(0.054902, 0.207843, 0.478431);//
	glVertex3f(VALUE_FROM_PERCENT(-0.9999f, percent)+ x_pos, VALUE_FROM_PERCENT(-0.9999f,  percent) + y_pos, 0.0f);

	glColor3f(0.054902, 0.207843, 0.478431);//
	glVertex3f(VALUE_FROM_PERCENT(0.9999f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.9999f,  percent) + y_pos, 0.0f);

	glColor3f(0.019608, 0.501961, 0.662745);//
	glVertex3f(VALUE_FROM_PERCENT(0.9999f,  percent) + x_pos, VALUE_FROM_PERCENT(0.9999f,  percent) + y_pos, 0.0f);

	glColor3f(0.019608, 0.501961, 0.662745);//
	glVertex3f(VALUE_FROM_PERCENT(-0.9999f,  percent) + x_pos, VALUE_FROM_PERCENT(0.9999f,  percent) + y_pos, 0.0f);

	glEnd();

	
	
}

void Gauri_land(float x_pos, float y_pos, float  percent)
{
	float amp_first_wave = 0.035f, amp_second_wave = 0.035f, BASE_HIGHT_1 = -0.75f, BASE_HIGHT_2=-0.9f;
	float x, y, wave;
	glPointSize(4.5);
	glColor3f(0.980392, 0.807843, 0.400000);
	glBegin(GL_POINTS);

	for (float x = -1.0; x <= 1.0; x += 0.005)
	{
		wave = amp_first_wave * sin(VALUE_FROM_PERCENT(x * 10,  percent) + x_pos)+amp_second_wave * sin(VALUE_FROM_PERCENT(x * 20,  percent) + x_pos);
		for (y = -1.0; y <= (BASE_HIGHT_1 + wave); y += 0.005)
		{   
			
			glVertex3f(VALUE_FROM_PERCENT(x,  percent) + x_pos, VALUE_FROM_PERCENT(y,  percent) + y_pos, 0.0f);
		}

	}

	glEnd();

	glPointSize(4.5);
	//glColor3f(1.0, 0.50196078, 0.0);
	glColor3f(0.949020, 0.717647, 0.231373);
	glBegin(GL_POINTS);
	for (float x = -1.0; x <= 1.0; x += 0.005)
	{
		wave = amp_first_wave * sin(VALUE_FROM_PERCENT(x * 10,  percent) + x_pos) + amp_second_wave * sin(VALUE_FROM_PERCENT(x * 20,  percent) + x_pos);
		for (y = -0.9999; y <= (BASE_HIGHT_2 + wave); y += 0.005)
		{

			glVertex3f(VALUE_FROM_PERCENT(x,  percent) + x_pos, VALUE_FROM_PERCENT(y,  percent) + y_pos, 0.0f);
		}

	}
	glEnd();
	
}

void Gauri_Grass_one(float x_pos, float y_pos, float percent, float delta_wave_factor,float wave_factor)
{
	float amp_first_wave = 0.035f;
	float wave_intensity = 0.0f;

	float x, y, wave;

	glColor3f(0.564706, 0.780392, 0.235294);

	glBegin(GL_TRIANGLE_STRIP);
	for (float y = -1.0; y <= -0.3; y += 0.005, wave_intensity += 1.4)//गवताची ऊँची आहे 
	{

		//wave = amp_first_wave *sin(VALUE_FROM_PERCENT(y * 10- VALUE_FROM_PERCENT(wave_factor * delta_wave_factor, wave_intensity), percent) + y_pos) ;

		wave = amp_first_wave * sin(VALUE_FROM_PERCENT(y * 10 - (wave_factor * delta_wave_factor), percent) + y_pos);
		glVertex3f(VALUE_FROM_PERCENT(wave, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(wave + 0.02, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);//grass chi width sathi


	}

	glEnd();

}

void Gauri_Grass_two(float x_pos, float y_pos, float percent, float delta_wave_factor, float wave_factor)
{
	float amp_first_wave = 0.04f;
	float wave_intensity = 0.0f;

	float x, y, wave;

	glColor3f(0.360784, 0.647059, 0.282353);

	glBegin(GL_TRIANGLE_STRIP);
	for (float y = -1.0; y <= -0.7; y += 0.005, wave_intensity += 1.4)//गवताची ऊँची आहे 
	{

		//wave = amp_first_wave *sin(VALUE_FROM_PERCENT(y * 10- VALUE_FROM_PERCENT(wave_factor * delta_wave_factor, wave_intensity), percent) + y_pos) ;

		wave = amp_first_wave * sin(VALUE_FROM_PERCENT(y * 10 - (wave_factor * delta_wave_factor), percent) + y_pos);
		glVertex3f(VALUE_FROM_PERCENT(wave, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(wave + 0.02, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);//grass chi width sathi


	}

	glEnd();

}

void Gauri_Grass_three(float x_pos, float y_pos, float percent, float delta_wave_factor, float wave_factor)
{
	float amp_first_wave = 0.05f;
	float wave_intensity = 0.0f;

	float x, y, wave;

	glColor3f(0.360784, 0.647059, 0.282353);

	glBegin(GL_TRIANGLE_STRIP);
	for (float y = -1.0; y <= -0.62; y += 0.005, wave_intensity += 1.4)//गवताची ऊँची आहे 
	{

		//wave = amp_first_wave *sin(VALUE_FROM_PERCENT(y * 10- VALUE_FROM_PERCENT(wave_factor * delta_wave_factor, wave_intensity), percent) + y_pos) ;

		wave = amp_first_wave * sin(VALUE_FROM_PERCENT(y * 10 - (wave_factor * delta_wave_factor), percent) + y_pos);
		glVertex3f(VALUE_FROM_PERCENT(wave, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(wave + 0.02, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);//grass chi width sathi


	}

	glEnd();

}

void Gauri_Grass_four(float x_pos, float y_pos, float percent, float delta_wave_factor, float wave_factor)
{
	float amp_first_wave = 0.045f;
	float wave_intensity = 0.0f;

	float x, y, wave;

	glColor3f(0.564706, 0.780392, 0.235294);

	glBegin(GL_TRIANGLE_STRIP);
	for (float y = -1.0; y <= -0.5; y += 0.005, wave_intensity += 1.4)//गवताची ऊँची आहे 
	{

		//wave = amp_first_wave *sin(VALUE_FROM_PERCENT(y * 10- VALUE_FROM_PERCENT(wave_factor * delta_wave_factor, wave_intensity), percent) + y_pos) ;

		wave = amp_first_wave * sin(VALUE_FROM_PERCENT(y * 10 - (wave_factor * delta_wave_factor), percent) + y_pos);
		glVertex3f(VALUE_FROM_PERCENT(wave, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);
		glVertex3f(VALUE_FROM_PERCENT(wave + 0.02, percent) + x_pos, VALUE_FROM_PERCENT(y, percent) + y_pos, 0.0f);//grass chi width sathi


	}

	glEnd();

}

void Gauri_Starfish( float x_pos, float y_pos, float percent)
{
	//star fish
	glBegin(GL_POLYGON);
	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.06f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.84f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.06f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.90f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.11f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.90f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.06f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.93f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.08f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.97f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.03f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.93f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(-0.01f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.95f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.02f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.91f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(-0.01f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.88f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.04f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.89f,  percent) + y_pos, 0.0f);

	glColor3f(0.901961, 0.117647, 0.145098);//red 
	glVertex3f(VALUE_FROM_PERCENT(0.06f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.84f,  percent) + y_pos, 0.0f);

	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.87f, percent) + y_pos, 0.0f);
	glEnd();
}


void Gauri_Shankh(float x_pos, float y_pos, float percent)
{
	//shankha
	glBegin(GL_POLYGON);
	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.85f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.80f,  percent) + y_pos,0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.79f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.54f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.80f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.52f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.78f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.51f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.77f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.49f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.77f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.50f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.76f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.51f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.76f,  percent) + y_pos, 0.0f);


	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.54f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.78f,  percent) + y_pos, 0.0f);


	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.54f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.77f,  percent) + y_pos, 0.0f);


	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.53f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.77f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.51f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.75f,  percent) + y_pos, 0.0f);


	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.51f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.72f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.52f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.73f,  percent) + y_pos, 0.0f);


	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.52f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.75f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.54f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.76f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.53f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.69f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.54f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.70f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.54f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.75f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.75f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.56f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.70f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.57f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.70f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.56f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.74f,  percent) + y_pos, 0.0f);


	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.57f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.74f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.59f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.71f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.60f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.72f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.57f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.75f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.57f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.76f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.80f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.61f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.73f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.62f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.74f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.56f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.78f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.56f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.80f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.80f,  percent) + y_pos, 0.0f);

	glColor3f(0.639216, 0.478431, 0.584314);//voilt
	glVertex3f(VALUE_FROM_PERCENT(0.55f,  percent) + x_pos, VALUE_FROM_PERCENT(-0.85f,  percent) + y_pos, 0.0f);




	glEnd();
}

void Gauri_Kasav(float x_pos,float y_pos,float  percent, float Ypercent)
{
	
	
	
	//pot
	glBegin(GL_POLYGON); 

	glColor3f(0.819608,0.741176,0.552941); 
	glVertex3f(VALUE_FROM_PERCENT(-0.41f, percent)+ x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos, 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos, 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.68f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.30f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.72f, percent) + y_pos , 0.0f);


	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.72f, percent) + y_pos, 0.0f);


	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos , 0.0f);


	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.39f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.41f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glEnd();


	glBegin(GL_POLYGON);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.72f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(-0.71f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.70f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + y_pos, 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos, 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos, 0.0f);

	glColor3f(0.819608,0.741176,0.552941);
	glVertex3f(VALUE_FROM_PERCENT(-0.11f, percent) + x_pos, VALUE_FROM_PERCENT(-0.72f, percent) + y_pos , 0.0f);


	glEnd();

//////////////////pot ani path middle
	glBegin(GL_POLYGON);


	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.39f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.19f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.39f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f);


	glEnd();

	//pot ani path middle
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.60f, percent) + y_pos , 0.0f);


	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.04f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + y_pos, 0.0f);

	glEnd();
	


	///////////////path
	glBegin(GL_POLYGON);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos, 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.49f, percent) + y_pos, 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(0.0f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos, 0.0f);

////////////////////path
	

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos , 0.0f);


	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.65f, percent) + y_pos, 0.0f);


	///////////////////path

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.603922, 0.737255, 0.345098);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	
	glEnd();


	//////////pathivarche polygon 1


	glBegin(GL_POLYGON);
	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.32f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.31f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos, 0.0f);


	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos , 0.0f);

	glColor3f(0.360784, 0.329412, 0.294118);
	glVertex3f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);


	glEnd();

	//////////pathivarche polygon 2
	glBegin(GL_POLYGON); 

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.24f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.3f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glEnd();

	//////////pathivarche polygon 3
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.17f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.1f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.64f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos , 0.0f);

	glEnd();

	//////////pathivarche polygon 4
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.13f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.61f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.09f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos, 0.0f);

	glEnd();

	//////////pathivarche polygon 5
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.07f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.05f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos , 0.0f);

	glEnd();

	//////////pathivarche polygon 6
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.08f, percent) + x_pos, VALUE_FROM_PERCENT(-0.53f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.12f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos , 0.0f);

	glEnd();


	//////////pathivarche polygon 7
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.13f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.14f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.17f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.2f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.13f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos , 0.0f);

	glEnd();

	

	//////////pathivarche polygon 8
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.20f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.15f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.16f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.21f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.25f, percent) + x_pos, VALUE_FROM_PERCENT(-0.45f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.26f, percent) + x_pos, VALUE_FROM_PERCENT(-0.49f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.23f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.22f, percent) + x_pos, VALUE_FROM_PERCENT(-0.52f, percent) + y_pos, 0.0f);


	glEnd();
	

	//////////pathivarche polygon 9
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.28f, percent) + x_pos, VALUE_FROM_PERCENT(-0.46f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.47f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.27f, percent) + x_pos, VALUE_FROM_PERCENT(-0.49f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.29f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.33f, percent) + x_pos, VALUE_FROM_PERCENT(-0.51f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.49f, percent) + y_pos , 0.0f);

	glEnd();

	//////////pathivarche polygon 10
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.34f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.35f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.36f, percent) + x_pos, VALUE_FROM_PERCENT(-0.5f, percent) + y_pos, 0.0f);

	glEnd();

	

	//////////head
	glBegin(GL_POLYGON); 

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.41f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) +x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.45f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.43f, percent) + x_pos, VALUE_FROM_PERCENT(-0.62f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.41f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.63f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.37f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(-0.38f, percent) + x_pos, VALUE_FROM_PERCENT(-0.55f, percent) + y_pos , 0.0f);

	

	glEnd();

	
	float radius = 0.005f, theta;
	//outer color of eye
	glBegin(GL_POLYGON);

	float radius1 = 0.015f;
	glColor3f(0.0,0.0,0.0);
	for (float i = 0; i < 360; i = i + 0.01f)
	{
		theta = i * 3.142 / 180;//convert into degree 
		glVertex2f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos + radius1 * cos(theta), VALUE_FROM_PERCENT(-0.58f, percent)+ y_pos + radius1 * sin(theta));
	}


	glEnd();

	//////////dole

	glBegin(GL_POLYGON);

	glColor3f(0.650980, 0.627451, 0.607843);
	for (float i = 0; i < 360; i = i + 0.01f)
	{
		theta = i * 3.142 / 180;//convert into degree 
		glVertex2f(VALUE_FROM_PERCENT(-0.4f, percent) + x_pos + radius * cos(theta), VALUE_FROM_PERCENT(-0.58f, percent) + y_pos + radius * sin(theta));
	}


	glEnd();



	//////////sheput
	glBegin(GL_POLYGON);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.56f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.58f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.59f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.02f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.6f, percent) + y_pos, 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.06f, percent) + x_pos, VALUE_FROM_PERCENT(-0.57f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.03f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glColor3f(0.192157,0.290196,0.113725);
	glVertex3f(VALUE_FROM_PERCENT(0.01f, percent) + x_pos, VALUE_FROM_PERCENT(-0.54f, percent) + y_pos , 0.0f);

	glEnd();

	// //////////पोट अणि पाय यामधील न हालनारा भाग पुढचा 
	// glBegin(GL_POLYGON);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.32f + x_pos, -0.65f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.31f + x_pos, -0.65f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.26f + x_pos, -0.67f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.25f + x_pos, -0.68f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.26f + x_pos, -0.69f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.28f + x_pos, -0.69f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.31f + x_pos, -0.68f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.33f + x_pos, -0.67f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.33f + x_pos, -0.66f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.32f + x_pos, -0.65f + y_pos, 0.0f);

	// glEnd();

	// //////////पोट अणि पाय यामधील न हालनारा भाग मागचा 
	// glBegin(GL_POLYGON);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.1f + x_pos, -0.68f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.05f + x_pos, -0.65f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.03f + x_pos, -0.65f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.03f + x_pos, -0.66f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.08f + x_pos, -0.7f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.09f + x_pos, -0.69f + y_pos, 0.0f);

	// glColor3f(0.192157, 0.290196, 0.113725);
	// glVertex3f(-0.1f + x_pos, -0.68f + y_pos, 0.0f);

	// glEnd();


	
	//////////पुढच्या पायाचा पंख 
	glBegin(GL_POLYGON);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.26f + x_pos, -0.69f + VALUE_FROM_PERCENT(0.5f, Ypercent / 2.0f) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.32f + x_pos, -0.66f + VALUE_FROM_PERCENT(0.5f, Ypercent / 2.0f) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.33f + x_pos, VALUE_FROM_PERCENT(-0.66f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.36f + x_pos, VALUE_FROM_PERCENT(-0.71f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.36f + x_pos, VALUE_FROM_PERCENT(-0.74f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f); //

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.35f + x_pos, VALUE_FROM_PERCENT(-0.78f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f); //

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.33f + x_pos, VALUE_FROM_PERCENT(-0.81f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f); //

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.32f + x_pos, VALUE_FROM_PERCENT(-0.77f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f); //

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.3f + x_pos, VALUE_FROM_PERCENT(-0.74f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f); //

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.28f + x_pos, VALUE_FROM_PERCENT(-0.72f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	
	glEnd();

	//////////मागच्या पायाचा पंख
	glBegin(GL_POLYGON);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.03f + x_pos, -0.65f+ y_pos, 0.0f); //

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.1f + x_pos, -0.68f+ y_pos, 0.0f);	//

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.06f + x_pos, VALUE_FROM_PERCENT(-0.72f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.03f + x_pos, VALUE_FROM_PERCENT(-0.73f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(0.03f + x_pos, VALUE_FROM_PERCENT(-0.74f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(0.08f + x_pos, VALUE_FROM_PERCENT(-0.73f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glColor3f(0.192157, 0.290196, 0.113725);
	glVertex3f(-0.01f + x_pos, VALUE_FROM_PERCENT(-0.67f, percent) + VALUE_FROM_PERCENT(0.5f, Ypercent) + y_pos, 0.0f);

	glEnd();
}