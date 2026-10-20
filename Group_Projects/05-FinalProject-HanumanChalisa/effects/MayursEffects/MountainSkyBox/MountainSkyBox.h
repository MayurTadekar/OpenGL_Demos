
#include <Windows.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>

#include "MountainTextureProgram.h"
#include "common.h"
#include "SkyBox.h"

#include "../Common/Shader.h"
#include "../Common/Program.h"

#include "../../../include/common.h"
#include "../../../modules/Texture/Texture.h"

class MountainSkyBox
{
private:
	MountainTextureProgram *tProgram = nullptr;
	GLuint skyMap = 0;
	SkyBox *skybox = NULL;

public:
	MountainSkyBox()
	{
		// Code
		tProgram = new MountainTextureProgram("./effects/MayursEffects/MountainSkyBox/texture_vs.glsl",
											  "./effects/MayursEffects/MountainSkyBox/texture_fs.glsl",
											  "log.txt");

		if (!LoadTextureFromFile("./resources/Texture/skymap.png", &skyMap))
		{
			LOG_ENTRY("log.txt", "Loaded UN-Successfully");
		}
		else
		{
			LOG_ENTRY("log.txt", "Loaded Successfully");
		}

		skybox = new SkyBox();
		skybox->Initialize();
	}

	void Display(vmath::mat4 &projectionMatrix,
				 vmath::mat4 &viewMatrix,
				 vmath::mat4 &modelMatrix)
	{

		tProgram->StartProgram();
		{

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, skyMap);

			tProgram->SetUniforms(projectionMatrix,
								  viewMatrix,
								  modelMatrix,
								  0);

			// square->Display();
			skybox->Display();
		}
		tProgram->StopProgram();
	}

	void Uninitialize()
	{
		// Code
		if (skybox)
		{
			skybox->Uninitialize();
			delete skybox;
			skybox = NULL;
		}
	}
};
