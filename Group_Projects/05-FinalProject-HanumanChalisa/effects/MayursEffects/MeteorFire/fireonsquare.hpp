#ifndef _FIRE_ON_SQUARE
#define _FIRE_ON_SQUARE

#include "FrameBufferObject.h"

#include "TextureProgram.h"

#include "fire.h"
#include "square.h"

#include "common.h"

class FireOnSquare
{

public:
	FireOnSquare();

	int Initialize(int winWidth, int winHeight);

	void Resize(int winWidth, int winHeight);

	void GenerateFireTexture(vmath::mat4 &projectionMatrix);
	void Draw(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix);

	void Uninitialize();

private:
	Fire *fire = nullptr;
	FrameBufferObject *firefbo = nullptr;
	TextureProgram *tProgram = nullptr;
	Square *square = nullptr;
};

FireOnSquare::FireOnSquare()
{
	// Code
}

int FireOnSquare::Initialize(int winWidth, int winHeight)
{
	// Code

	fire = new Fire();
	if (NULL == fire)
	{
		LOG_ENTRY("log.txt", "Fire Object Creation Failed\n");
		return (-1);
	}
	fire->Initialize();

	// LOG_ENTRY("log.txt", "Creating Sphere Framebuffer...");
	firefbo = new FrameBufferObject(winWidth / 2, winHeight / 2, GL_RGBA16F, GL_DEPTH_COMPONENT32F);
	firefbo->Initialize();

	tProgram = new TextureProgram("./effects/MayursEffects/Fire/texture_vs.glsl", "./effects/MayursEffects/Fire/texture_fs.glsl", "log.txt");

	square = new Square();
	square->Initialize();

	return (0);
}

void FireOnSquare::Resize(int winWidth, int winHeight)
{
	// Code
	firefbo->Resize(winWidth, winHeight);
}

void FireOnSquare::GenerateFireTexture(vmath::mat4 &projectionMatrix)
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

	if (fire)
	{
		fire->Display(projectionMatrix, mMatrix, vMatrix);
	}

	if (firefbo)
	{
		firefbo->Unbind();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FireOnSquare::Draw(vmath::mat4 &projectionMatrix, vmath::mat4 &modelMatrix, vmath::mat4 &viewMatrix)
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

void FireOnSquare::Uninitialize()
{
	// Code

	if (square)
	{
		square->Uninitialize();
		delete square;
		square = NULL;
	}

	if (fire)
	{
		fire->Uninitialize();
		delete fire;
		fire = NULL;
	}

	if (firefbo)
	{
		firefbo->Uninitialize();
		delete (firefbo);
		firefbo = nullptr;
	}
}

#endif
