
// River Object Function Defination
void River_Nivrutti(float x_pos, float y_pos) 
{
    glColor3f(0.53f, 0.81f, 0.92f);

	// Draw wave like structue usng sine wave
    glBegin(GL_POINTS);
    float x, y, wave;
    for (x = -1.0; x <= 1.0; x += 0.005) 
	{
        wave = amp_first_wave * sin(x * 10) + amp_second_wave * sin(x * 20);

        for (y = -1.0; y <= (BASE_HEIGHT + wave); y += 0.005)
		{
            glVertex3f( x+x_pos, y+y_pos, 0.0f);
        }
    }
    glEnd();



	//************************* Quads for river lower Gradient ****************************** 
	glBegin(GL_QUADS);

	glColor3f(0.136f, 0.535f, 0.85f);
	glVertex3f(-1.0f+x_pos, -1.0f+y_pos, 0.0f);

	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(-1.0f+x_pos, -0.90f+y_pos, 0.0f);

	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(1.0f+x_pos, -0.90f+y_pos, 0.0f);
	
	glColor3f(0.136f, 0.535f, 0.85f);
	glVertex3f(1.0f+x_pos, -1.0f+y_pos, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(-1.0f+x_pos, -0.90f+y_pos, 0.0f);
	
	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(-1.0f+x_pos, -0.85f+y_pos, 0.0f);
	
	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(1.0f+x_pos, -0.85f+y_pos, 0.0f);
	
	glColor3f(0.109f, 0.636f, 0.921f);
	glVertex3f(1.0f+x_pos, -0.90f+y_pos, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(-1.0f+x_pos, -0.85f+y_pos, 0.0f);
	
	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(-1.0f+x_pos, -0.75f+y_pos, 0.0f);
	
	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(1.0f+x_pos, -0.75f+y_pos, 0.0f);

	glColor3f(0.351, 0.734, 0.843);
	glVertex3f(1.0f+x_pos, -0.85f+y_pos, 0.0f);
	glEnd();
	//**************************************************************************************** 


	// lower water flow starts here (waterfall like structure)
	glBegin(GL_QUADS);
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.20f+x_pos, 0.61f+y_pos, 0.0f);
	
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.40f+x_pos, 0.61f+y_pos, 0.0f);
	
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.41f+x_pos, 0.54f+y_pos, 0.0f);

	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.32f+x_pos, 0.54f+y_pos, 0.0f);
	glEnd();


	glBegin(GL_QUAD_STRIP);
	glColor3f(0.43, 0.79, 0.953);
	glVertex3f(0.31f+x_pos, 0.54f+y_pos, 0.0f);
	glVertex3f(0.41f+x_pos, 0.54f+y_pos, 0.0f);

	glVertex3f(0.32f+x_pos, 0.48f+y_pos, 0.0f);
	glVertex3f(0.41f+x_pos, 0.44f+y_pos, 0.0f);
	
	glVertex3f(0.30f+x_pos, 0.34f+y_pos, 0.0f);
	glVertex3f(0.40f+x_pos, 0.34f+y_pos, 0.0f);

	glVertex3f(0.30f+x_pos, 0.24f+y_pos, 0.0f);
	glVertex3f(0.41f+x_pos, 0.23f+y_pos, 0.0f);

	glVertex3f(0.28f+x_pos, 0.17f+y_pos, 0.0f);
	glVertex3f(0.42f+x_pos, 0.15f+y_pos, 0.0f);

	glVertex3f(0.26f+x_pos, 0.03f+y_pos, 0.0f);
	glVertex3f(0.43f+x_pos, 0.02f+y_pos, 0.0f);
	
	glVertex3f(0.24f+x_pos, -0.09f+y_pos, 0.0f);
	glVertex3f(0.435f+x_pos, -0.1f+y_pos, 0.0f);
	
	glVertex3f(0.23f+x_pos, -0.19f+y_pos, 0.0f);
	glVertex3f(0.43f+x_pos, -0.20f+y_pos, 0.0f);
	
	glVertex3f(0.21f+x_pos, -0.31f+y_pos, 0.0f);
	glVertex3f(0.44f+x_pos, -0.32f+y_pos, 0.0f);

	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(0.19f+x_pos, -0.47f+y_pos, 0.0f);
	glVertex3f(0.45f+x_pos, -0.58f+y_pos, 0.0f);

	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex3f(0.16f+x_pos, -0.60f+y_pos, 0.0f);
	glVertex3f(0.47f+x_pos, -0.73f+y_pos, 0.0f);
	
	glEnd();
}

