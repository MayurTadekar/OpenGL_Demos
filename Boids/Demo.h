
#ifndef _DEMO_H
#define _DEMO_H

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "Cube.h"
#include "Flock.h"
#include "FlockProgram.h"
#include "LineProgram.h"
#include "NormalShaderProgram.h"
#include "ModelRenderingProgram.h"

#include "sphere.h"

class Demo
{
public:
	Demo();
	~Demo();

	void Update(float deltaTime);
	void Draw(	glm::mat4 &projection,
			  	glm::mat4 &view,
			  	glm::mat4 &model,
			  	glm::vec3 cameraPos);
	void Uninitialize();

	void DisplayIMGUI();

	void SetOpenCLOn() { flock->setOpenCLON(); }
	void SetCudaOn() { flock->setCUDAOn(); }
	void Pause() { flock->Pause(); }

	void Increase() { flock->Increase(); }
	void Decrease() { flock->Decrease(); }

private:
	Flock *flock = nullptr;

	Cube *cube = nullptr;

	FlockProgram *flockProgram = nullptr;
	LineProgram *lineProgram = nullptr;
	NormalShaderProgram *nprogram = nullptr;
	ModelRenderingProgram *mrProgram = nullptr;

	float angle;

	Sphere *world = nullptr;
	Sphere *sphere01 = nullptr;
	Sphere *sphere02 = nullptr;
};

Demo::Demo()
{
	flock = new Flock();

	cube = new Cube(5.0f);
	cube->Initialize();

	world = new Sphere(300.0f);

	sphere01 = new Sphere(80.0f);
	// sphere02 = new Sphere(50.0f);

	angle = 0.0f;

	flockProgram = new FlockProgram(
		"flockprogram_vs.glsl",
		"flockprogram_fs.glsl",
		"log.txt");

	lineProgram = new LineProgram(
		"line_vs.glsl",
		"line_fs.glsl",
		"log.txt");

	nprogram = new NormalShaderProgram(
		"normal_vs.glsl",
		"normal_fs.glsl",
		"log.txt");

	mrProgram = new ModelRenderingProgram(
		"modelrender_vs.glsl",
		"modelrender_fs.glsl",
		"log.txt");
}

Demo::~Demo()
{
	if (flock)
	{
		delete flock;
		flock = nullptr;
	}

	if (cube)
	{
		cube->Uninitialize();
		delete cube;
		cube = nullptr;
	}

	if (nprogram)
	{
		delete (lineProgram);
		lineProgram = nullptr;
	}

	if (lineProgram)
	{
		delete (lineProgram);
		lineProgram = nullptr;
	}

	if (flockProgram)
	{
		delete flockProgram;
		flockProgram = nullptr;
	}

	if (mrProgram)
	{
		delete (mrProgram);
		mrProgram = nullptr;
	}
}

void Demo::DisplayIMGUI()
{
	// Code
	flock->DisplayIMGUI();
}

void Demo::Update(float deltaTime)
{

	// flock->SetGoal(goal);

	flock->Update(deltaTime);
}

void Demo::Draw(glm::mat4 &projection,
				glm::mat4 &view,
				glm::mat4 &model,
				glm::vec3 cameraPos)
{
	// Code

	// nprogram->StartProgram();
	// {

	// 	glEnable(GL_CULL_FACE);
	// 	glCullFace(GL_BACK);

	// 	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// 	nprogram->SetUniforms(projection, view, model);

	// 	world->Draw();
	// 	glDisable(GL_CULL_FACE);

	// }
	// nprogram->StopProgram();

	// flockProgram->StartProgram();
	// {
	// 	flockProgram->SetUniforms(projection, view, model);

	// 	// flock->Draw(projection, view);
	// 	flock->Draw(flockProgram->GetProgramID());
	// }
	// flockProgram->StopProgram();

	mrProgram->StartProgram();
	{
		mrProgram->SetUniforms(projection, view, cameraPos);

		// flock->Draw(projection, view);
		flock->Draw(mrProgram->GetProgramID());
	}
	mrProgram->StopProgram();

	// nprogram->StartProgram();
	// {

	// 	model = glm::translate(glm::mat4(1.0f), glm::vec3(90.0f, 0.0f, 0.0f));

	// 	nprogram->SetUniforms(projection, view, model);

	// 	sphere01->Draw();
	// }
	// nprogram->StopProgram();

	// lineProgram->StartProgram();
	// {

	// 	model = glm::translate(glm::mat4(1.0f), glm::vec3(-90.0f, 0.0f, 0.0f));

	// 	lineProgram->SetUniforms(projection, view, model);

	// 	sphere02->Draw();
	// }
	// lineProgram->StopProgram();

	// lineProgram->StartProgram();
	// {
	// 	lineProgram->SetUniforms(projection, view, model);

	// 	flock->DrawDirections();
	// }
	// lineProgram->StopProgram();
}

#endif /* _DEMO_H */