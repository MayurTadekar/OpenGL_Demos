#ifndef _FLOCK_H
#define _FLOCK_H

#include <GL/glew.h>
#include <GL/GL.h>

#include <complex>
#include <vector>

#include "Shader.h"
#include "Program.h"
#include "macros.h"
#include "common.h"

#include <glm/glm.hpp>

#include <cuda_gl_interop.h>
#include <cuda_runtime.h>

#include "flock_cuda.h"

class FlockCompute;

class FlockCompute
{
public:
	FlockCompute(
		const char *computeShaderPath,
		GLuint birdCount,
		int _goalCount);

	void Resize(GLuint width, GLuint height);

	~FlockCompute();

	void CreateBuffers(GLuint birdCount);

	void RenderUsingComputeShader(float time,
								  std::vector<glm::vec3> goals,
								  float closestAllowedDistance,
								  float rule1Weight,
								  float rule2Weight,
								  float rule3Weight,
								  float rule4Weight,
								  float boundaryAvoidanceWeight,
								  float obstacleAvoidanceWeight,
								  float worldRadius,
								  float boidRadius,
								  float boundaryMargin,
								  float lookAheadDistance,
								  float avoidancePaddingFactor,
								  float minSpeed,
								  float maxSpeed,
								  GLuint birdCount);

	void RenderUsingCUDA(float time,
						 std::vector<glm::vec3> goals,
						 float closestAllowedDistance,
						 float rule1Weight,
						 float rule2Weight,
						 float rule3Weight,
						 float rule4Weight,
						 float boundaryAvoidanceWeight,
						 float obstacleAvoidanceWeight,
						 float worldRadius,
						 float boidRadius,
						 float boundaryMargin,
						 float lookAheadDistance,
						 float avoidancePaddingFactor,
						 float minSpeed,
						 float maxSpeed,
						 GLuint birdCount);

	GLuint GetCurrentSSBO() const
	{
		return ssbo[readBuffer];
	}

	void SetDirectionData(std::vector<glm::vec4> directionPoints);
	void SetObstaclesData(std::vector<glm::vec4> obstacles);

private:
	Shader *shader = nullptr;
	Program *program = nullptr;

	GLuint ssbo[2];
	GLuint directionsSSBO;
	GLuint obstacleSSBO;

	GLuint readBuffer;
	GLuint writeBuffer;

	GLuint birdCount;
	int goalCount;
	int directionCount;
	int obstacleCount;

	cudaError_t cudaResult;
	struct cudaGraphicsResource *cudaGraphicsResource[2] = {nullptr, nullptr};
	struct cudaGraphicsResource *cudaGraphicsResourceForDirections = nullptr;
	struct cudaGraphicsResource *cudaGraphicsResourceForObstacles = nullptr;

	float3 *d_goals = nullptr;

	inline float RandomFloat(float minValue, float maxValue)
	{
		return minValue + (maxValue - minValue) *
							  (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	}
};

FlockCompute::FlockCompute(
	const char *computeShaderPath,
	GLuint _birdCount,
	int _goalCount)
{

	shader = new Shader(
		computeShaderPath,
		GL_COMPUTE_SHADER,
		"log.txt");

	program = new Program(
		1,
		shader->GetObject());

	program->LinkProgram("log.txt");

	ssbo[0] = 0;
	ssbo[1] = 0;

	directionsSSBO = 0;
	obstacleSSBO = 0;

	readBuffer = 0;
	writeBuffer = 1;

	birdCount = _birdCount;
	goalCount = _goalCount;

	CreateBuffers(birdCount);
}

FlockCompute::~FlockCompute()
{
	// Code

	if (d_goals)
	{
		cudaError_t freeResult = cudaFree(d_goals);

		if (cudaResult == cudaSuccess)
			cudaResult = freeResult;
	}

	if (cudaGraphicsResourceForDirections)
	{
		cudaGraphicsUnregisterResource(cudaGraphicsResourceForDirections);
		cudaGraphicsResourceForDirections = nullptr;
	}

	if (cudaGraphicsResourceForObstacles)
	{
		cudaGraphicsUnregisterResource(cudaGraphicsResourceForObstacles);
		cudaGraphicsResourceForObstacles = nullptr;
	}

	for (int le = 0; le < 2; ++le)
	{
		if (cudaGraphicsResource[le])
		{
			cudaGraphicsUnregisterResource(cudaGraphicsResource[le]);
			cudaGraphicsResource[le] = nullptr;
		}
	}

	if (shader)
	{
		// shader->Uninitialize();
		delete shader;
		shader = NULL;
	}

	if (program)
	{
		// shader->Uninitialize();
		delete program;
		program = NULL;
	}

	if (ssbo[0])
	{
		glDeleteBuffers(2, ssbo);
	}
}
// void FlockCompute::Render(float time, float oceanSize, float windSpeed, float fetch, float gamma, glm::vec2 windDirection, float meshWidth, float meshHeight)

void FlockCompute::RenderUsingComputeShader(float time,
											std::vector<glm::vec3> goals,
											float closestAllowedDistance,
											float rule1Weight,
											float rule2Weight,
											float rule3Weight,
											float rule4Weight,
											float boundaryAvoidanceWeight,
											float obstacleAvoidanceWeight,
											float worldRadius,
											float boidRadius,
											float boundaryMargin,
											float lookAheadDistance,
											float avoidancePaddingFactor,
											float minSpeed,
											float maxSpeed,
											GLuint birdCount)
{

	// Code
	glUseProgram(program->GetObject());

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo[readBuffer]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo[writeBuffer]);

	// --------------------------------------------------------
	// Uniforms
	// --------------------------------------------------------

	glUniform1f(glGetUniformLocation(program->GetObject(), "timestep"), time);

	// glUniform3fv(glGetUniformLocation(program->GetObject(), "goal"),
	// 			 1,
	// 			 &goal.x);

	glUniform1ui(
		glGetUniformLocation(program->GetObject(),
							 "goalCount"),
		goals.size());

	glUniform3fv(
		glGetUniformLocation(program->GetObject(),
							 "goals"),
		goals.size(),
		&goals[0].x);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "closest_allowed_dist"),
				closestAllowedDistance);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "rule1_weight"),
				rule1Weight);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "rule2_weight"),
				rule2Weight);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "rule3_weight"),
				rule3Weight);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "rule4_weight"),
				rule4Weight);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "boundaryAvoidanceWeight"),
				boundaryAvoidanceWeight);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "obstacleAvoidanceWeight"),
				obstacleAvoidanceWeight);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "worldRadius"),
				worldRadius);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "boundaryMargin"),
				boundaryMargin);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "lookAheadDistance"),
				lookAheadDistance);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "AvoidancePaddingFactor"),
				avoidancePaddingFactor);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "minSpeed"),
				minSpeed);

	glUniform1f(glGetUniformLocation(program->GetObject(),
									 "maxSpeed"),
				maxSpeed);

	glUniform1ui(
		glGetUniformLocation(program->GetObject(),
							 "birdCount"),
		birdCount);

	glUniform1ui(
		glGetUniformLocation(program->GetObject(),
							 "directionCount"),
		VFP(directionCount, 70));

	glUniform1ui(
		glGetUniformLocation(program->GetObject(),
							 "obstacleCount"),
		obstacleCount);

	glUniform1ui(
		glGetUniformLocation(program->GetObject(),
							 "goalCount"),
		goalCount);

	glUniform1f(
		glGetUniformLocation(
			program->GetObject(),
			"boidRadius"),
		boidRadius);

	glBindBufferBase(
		GL_SHADER_STORAGE_BUFFER,
		2,
		directionsSSBO);

	glBindBufferBase(
		GL_SHADER_STORAGE_BUFFER,
		3,
		obstacleSSBO);

	// GLuint p = program->GetObject();

	// glUniform1ui(
	// 	glGetUniformLocation(p, "obstacleCount"),
	// 	obstacleCount);

	// glUniform1f(
	// 	glGetUniformLocation(p, "avoidanceLookAhead"),
	// 	35.0f);

	// glUniform1f(
	// 	glGetUniformLocation(p, "boidRadius"),
	// 	1.0f);

	// glUniform1f(
	// 	glGetUniformLocation(p, "avoidanceWeight"),
	// 	0.85f);

	// --------------------------------------------------------
	// Run Compute Shader
	// --------------------------------------------------------

	glDispatchCompute((birdCount + 255) / 256, 1, 1);

	// --------------------------------------------------------
	// Ensure writes complete
	// --------------------------------------------------------
	// glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glMemoryBarrier(
		GL_SHADER_STORAGE_BARRIER_BIT |
		GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	std::swap(readBuffer, writeBuffer);

	glUseProgram(0);
}

void FlockCompute::RenderUsingCUDA(
	float time,
	std::vector<glm::vec3> goals,
	float closestAllowedDistance,
	float rule1Weight,
	float rule2Weight,
	float rule3Weight,
	float rule4Weight,
	float boundaryAvoidanceWeight,
	float obstacleAvoidanceWeight,
	float worldRadius,
	float boidRadius,
	float boundaryMargin,
	float lookAheadDistance,
	float avoidancePaddingFactor,
	float minSpeed,
	float maxSpeed,
	GLuint birdCount)
{
	if (birdCount == 0)
		return;

	if (birdCount > this->birdCount)
		return; // Buffers were allocated for this->birdCount.

	if (goals.size() > 16)
		return; // Matches MAX_GOALS in the CUDA kernel.

	if (goals.empty())
	{
		// The CUDA kernel safely handles goalCount == 0.
	}

	// --------------------------------------------------------
	// Prepare goal data
	// --------------------------------------------------------

	std::vector<float3> cudaGoals;
	cudaGoals.reserve(goals.size());

	for (const glm::vec3 &goal : goals)
	{
		cudaGoals.push_back(
			make_float3(goal.x, goal.y, goal.z));
	}

	if (!cudaGoals.empty())
	{
		cudaResult = cudaMemcpy(
			d_goals,
			cudaGoals.data(),
			cudaGoals.size() * sizeof(float3),
			cudaMemcpyHostToDevice);

		if (cudaResult != cudaSuccess)
		{
			cudaFree(d_goals);
			// Log cudaGetErrorString(cudaResult).
			return;
		}
	}

	// --------------------------------------------------------
	// Map OpenGL SSBOs for CUDA access
	// --------------------------------------------------------

	cudaResult = cudaGraphicsMapResources(
		2,
		cudaGraphicsResource,
		0);

	if (cudaResult != cudaSuccess)
	{
		if (d_goals)
			cudaFree(d_goals);

		// Log cudaGetErrorString(cudaResult).
		return;
	}

	FlockMember *d_membersIn = nullptr;
	FlockMember *d_membersOut = nullptr;

	size_t inputBytes = 0;
	size_t outputBytes = 0;

	cudaResult = cudaGraphicsResourceGetMappedPointer(
		reinterpret_cast<void **>(&d_membersIn),
		&inputBytes,
		cudaGraphicsResource[readBuffer]);

	if (cudaResult == cudaSuccess)
	{
		cudaResult = cudaGraphicsResourceGetMappedPointer(
			reinterpret_cast<void **>(&d_membersOut),
			&outputBytes,
			cudaGraphicsResource[writeBuffer]);
	}

	if (cudaResult != cudaSuccess)
	{
		cudaGraphicsUnmapResources(2, cudaGraphicsResource, 0);

		if (d_goals)
			cudaFree(d_goals);

		// Log cudaGetErrorString(cudaResult).
		return;
	}
	
	Obstacle *d_obstacle = nullptr;
	size_t obstacleBytes = 0;

	if( 0 !=  obstacleCount )
	{
		cudaResult = cudaGraphicsMapResources(
			1,
			&cudaGraphicsResourceForObstacles,
			0);

		if (cudaResult != cudaSuccess)
		{
			if (d_goals)
				cudaFree(d_goals);

			// Log cudaGetErrorString(cudaResult).
			return;
		}

		cudaResult = cudaGraphicsResourceGetMappedPointer(
			reinterpret_cast<void **>(&d_obstacle),
			&obstacleBytes,
			cudaGraphicsResourceForObstacles);

		if (cudaResult != cudaSuccess)
		{
			if (d_goals)
				cudaFree(d_goals);

			// Log cudaGetErrorString(cudaResult).
			return;
		}
	}

	
	DirectionPoint *d_directions = nullptr;
	size_t directionBytes = 0;

	cudaResult = cudaGraphicsMapResources(
		1,
		&cudaGraphicsResourceForDirections,
		0);

	if (cudaResult != cudaSuccess)
	{
		if (d_goals)
			cudaFree(d_goals);

		// Log cudaGetErrorString(cudaResult).
		return;
	}

	cudaResult = cudaGraphicsResourceGetMappedPointer(
		reinterpret_cast<void **>(&d_directions),
		&directionBytes,
		cudaGraphicsResourceForDirections);

	if (cudaResult != cudaSuccess)
	{
		if (d_goals)
			cudaFree(d_goals);

		// Log cudaGetErrorString(cudaResult).
		return;
	}

	// --------------------------------------------------------
	// Validate mapped buffer sizes
	// --------------------------------------------------------

	const size_t requiredBytes =
		static_cast<size_t>(birdCount) * sizeof(FlockMember);

	if (inputBytes < requiredBytes ||
		outputBytes < requiredBytes)
	{
		cudaGraphicsUnmapResources(2, cudaGraphicsResource, 0);

		if (d_goals)
			cudaFree(d_goals);

		return;
	}

	// --------------------------------------------------------
	// Launch CUDA BOIDS kernel
	// --------------------------------------------------------

	BoidsKernelInterface(
		d_membersIn,
		d_membersOut,
		birdCount,
		directionCount,
		d_directions,
		obstacleCount,
		d_obstacle,
		static_cast<uint32_t>(cudaGoals.size()),
		d_goals,
		time,
		closestAllowedDistance,
		rule1Weight,
		rule2Weight,
		rule3Weight,
		rule4Weight,
		boundaryAvoidanceWeight,
		obstacleAvoidanceWeight,
		worldRadius,
		boundaryMargin,
		lookAheadDistance,
		boidRadius,
		avoidancePaddingFactor,
		minSpeed,
		maxSpeed);

	// Check launch configuration and execution errors.
	cudaResult = cudaGetLastError();

	if (cudaResult == cudaSuccess)
	{
		cudaResult = cudaDeviceSynchronize();
	}

	// --------------------------------------------------------
	// Unmap OpenGL resources
	// --------------------------------------------------------

	cudaError_t unmapResult = cudaGraphicsUnmapResources(2, cudaGraphicsResource, 0);

	if (cudaResult != cudaSuccess)
	{
		// Log cudaGetErrorString(cudaResult).
		return;
	}

	if (unmapResult != cudaSuccess)
	{
		// Log cudaGetErrorString(unmapResult).
		return;
	}

	unmapResult = cudaGraphicsUnmapResources(1, &cudaGraphicsResourceForDirections, 0);

	if (cudaResult != cudaSuccess)
	{
		// Log cudaGetErrorString(cudaResult).
		return;
	}

	if (unmapResult != cudaSuccess)
	{
		// Log cudaGetErrorString(unmapResult).
		return;
	}

	if( 0 !=  obstacleCount )
	{

		unmapResult = cudaGraphicsUnmapResources(1, &cudaGraphicsResourceForObstacles, 0);

		if (cudaResult != cudaSuccess)
		{
			// Log cudaGetErrorString(cudaResult).
			return;
		}

		if (unmapResult != cudaSuccess)
		{
			// Log cudaGetErrorString(unmapResult).
			return;
		}
	}

	// --------------------------------------------------------
	// Swap buffers
	// --------------------------------------------------------

	std::swap(readBuffer, writeBuffer);
}

void FlockCompute::SetDirectionData(std::vector<glm::vec4> directionPoints)
{
	// Code

	directionCount = directionPoints.size();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, directionsSSBO);

	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		directionPoints.size() * sizeof(glm::vec4),
		directionPoints.data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	cudaResult = cudaGraphicsGLRegisterBuffer(&cudaGraphicsResourceForDirections, directionsSSBO, cudaGraphicsRegisterFlagsNone);
	if (cudaSuccess != cudaResult)
	{
		LOG_ENTRY("log.txt", "Cuda Graphics map resource pointer unsuccessful for directionsSSBO\n");
		exit(1);
	}

	LOG_ENTRY("log.txt", "Setting Directions : %d", directionCount);
}

void FlockCompute::SetObstaclesData(std::vector<glm::vec4> obstacles)
{
	// Code

	obstacleCount = static_cast<int>(obstacles.size());

	if ( 0 == obstacleCount )
		return;

	glBindBuffer(
		GL_SHADER_STORAGE_BUFFER,
		obstacleSSBO);

	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		obstacles.size() * sizeof(glm::vec4),
		obstacles.data(),
		GL_STATIC_DRAW);

	glBindBufferBase(
		GL_SHADER_STORAGE_BUFFER,
		3,
		obstacleSSBO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	cudaResult = cudaGraphicsGLRegisterBuffer(&cudaGraphicsResourceForObstacles, obstacleSSBO, cudaGraphicsRegisterFlagsNone);
	if (cudaSuccess != cudaResult)
	{
		LOG_ENTRY("log.txt", "Cuda Graphics map resource pointer unsuccessful for obstacleSSBO\n");
		exit(1);
	}

	LOG_ENTRY("log.txt", "Setting Obstacles : %d", obstacleCount);
}

void FlockCompute::CreateBuffers(GLuint birdCount)
{
	std::vector<FlockMember> birds(birdCount);

	srand(time(0));

	for (GLuint i = 0; i < birdCount; i++)
	{
		birds[i].position = glm::vec4(
			RandomFloat(-5.0f, 5.0f),
			RandomFloat(-5.0f, 5.0f),
			RandomFloat(-5.0f, 5.0f),
			1.0f);

		glm::vec3 dir = glm::normalize(glm::vec3(
			RandomFloat(-1.0f, 1.0f),
			RandomFloat(-1.0f, 1.0f),
			RandomFloat(-1.0f, 1.0f)));

		float speed = RandomFloat(5.0f, 20.f);

		birds[i].velocity = glm::vec4(dir * speed, 0.0f);
	}

	glGenBuffers(2, ssbo);

	for (int i = 0; i < 2; i++)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo[i]);

		glBufferData(GL_SHADER_STORAGE_BUFFER,
					 sizeof(FlockMember) * birdCount,
					 birds.data(),
					 GL_DYNAMIC_COPY);
	}

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	// // Each vec4 stores xyz = center, w = radius.
	// std::vector<glm::vec4> obstacles =
	// 	{
	// 		glm::vec4(20.0f, 0.0f, 0.0f, 5.0f),
	// 		glm::vec4(-15.0f, 8.0f, 10.0f, 3.0f),
	// 		glm::vec4(0.0f, -12.0f, -20.0f, 7.0f)};

	// obstacleCount = static_cast<GLuint>(obstacles.size());

	glGenBuffers(1, &directionsSSBO);
	glGenBuffers(1, &obstacleSSBO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, directionsSSBO);
	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		0,
		nullptr,
		GL_DYNAMIC_DRAW);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, obstacleSSBO);
	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		0,
		nullptr,
		GL_DYNAMIC_DRAW);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	cudaResult = cudaGraphicsGLRegisterBuffer(&cudaGraphicsResource[0], ssbo[0], cudaGraphicsRegisterFlagsNone);
	if (cudaSuccess != cudaResult)
	{
		LOG_ENTRY("log.txt", "Cuda Graphics map resource pointer unsuccessful for ssbo[0]\n");
		exit(1);
	}

	cudaResult = cudaGraphicsGLRegisterBuffer(&cudaGraphicsResource[1], ssbo[1], cudaGraphicsRegisterFlagsNone);
	if (cudaSuccess != cudaResult)
	{
		LOG_ENTRY("log.txt", "Cuda Graphics map resource pointer unsuccessful for ssbo[1]\n");
		exit(1);
	}

	cudaResult = cudaMalloc(reinterpret_cast<void **>(&d_goals), goalCount * sizeof(float3));
	if (cudaResult != cudaSuccess)
	{
		// Log cudaGetErrorString(cudaResult).
		return;
	}
}

void FlockCompute::Resize(GLuint width, GLuint height)
{
}

#endif
