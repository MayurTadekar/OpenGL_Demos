#ifndef _METEOR_FIRE_ON_SQUARE
#define _METEOR_FIRE_ON_SQUARE

#include "../CommonFire/FrameBufferObject.h"

#include "../CommonFire/TextureProgram.h"
#include "../CommonFire/square.h"

#include "meteorfire.h"

// #include "common.h"

class MeteorFireOnSquare
{

public:
	MeteorFireOnSquare();

	int Initialize(int winWidth, int winHeight);

	void Resize(int winWidth, int winHeight);

	void GenerateFireTexture(vmath::mat4 &projectionMatrix);
	void Draw(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix);

	void Uninitialize();

	void setColor(vmath::vec3 c) { meteorfire->setColor(c); }
	void setFireSize(float size) { meteorfire->setFireSize(size); }
	void setRadius(float radius) { meteorfire->setRadius(radius); }
	void setIntensity(float intensity) { meteorfire->setIntensity(intensity); }

private:
	MeteorFire *meteorfire = nullptr;
	FrameBufferObject *firefbo = nullptr;
	TextureProgram *tProgram = nullptr;
	Square *square = nullptr;
};

MeteorFireOnSquare::MeteorFireOnSquare()
{
	// Code
}

int MeteorFireOnSquare::Initialize(int winWidth, int winHeight)
{
	// Code

	meteorfire = new MeteorFire();
	if (NULL == meteorfire)
	{
		LOG_ENTRY("log.txt", "MeteorFire Object Creation Failed\n");
		return (-1);
	}
	meteorfire->Initialize();

	// LOG_ENTRY("log.txt", "Creating Sphere Framebuffer...");
	firefbo = new FrameBufferObject(winWidth / 2, winHeight / 2, GL_RGBA16F, GL_DEPTH_COMPONENT32F);
	firefbo->Initialize();

	tProgram = new TextureProgram("./effects/MayursEffects/CommonFire/texture_vs.glsl",
								  "./effects/MayursEffects/CommonFire/texture_fs.glsl", "log.txt");

	square = new Square();
	square->Initialize();

	return (0);
}

void MeteorFireOnSquare::Resize(int winWidth, int winHeight)
{
	// Code
	firefbo->Resize(winWidth, winHeight);
}

void MeteorFireOnSquare::GenerateFireTexture(vmath::mat4 &projectionMatrix)
{
	// Code
	mat4 vMatrix;
	mat4 mMatrix;

	vMatrix = lookat(vec3(0.0f, 0.0f, 10.0f),
					 vec3(0.0f, 0.0f, 0.0f),
					 vec3(0.0f, 1.0f, 0.0f));

	mMatrix = vmath::mat4::identity();

	if (firefbo)
	{
		firefbo->Clear(0.4f, 0.4f, 0.4f, 0.0f);
		firefbo->Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	if (meteorfire)
	{
		meteorfire->Display(projectionMatrix, mMatrix, vMatrix);
	}

	if (firefbo)
	{
		firefbo->Unbind();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MeteorFireOnSquare::Draw(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix)
{
	if (tProgram)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		tProgram->StartProgram();

		tProgram->SetUniforms(projectionMatrix, viewMatrix, modelMatrix, 0);

		firefbo->BindColorTexture(0);

		square->Draw(projectionMatrix, modelMatrix, viewMatrix);

		tProgram->StopProgram();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}

void MeteorFireOnSquare::Uninitialize()
{
	// Code

	if (square)
	{
		square->Uninitialize();
		delete square;
		square = NULL;
	}

	if (meteorfire)
	{
		meteorfire->Uninitialize();
		delete meteorfire;
		meteorfire = NULL;
	}

	if (firefbo)
	{
		firefbo->Uninitialize();
		delete (firefbo);
		firefbo = nullptr;
	}
}

#endif /* _METEOR_FIRE_ON_SQUARE */
