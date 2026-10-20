
#ifndef FLOCK_CUDA_H
#define FLOCK_CUDA_H

#include <cuda_runtime.h>
#include <stdint.h>
#include <glm/glm.hpp>

// -----------------------------------------------------------------------------
// CUDA BOIDS data structure
// Must match the memory layout of the OpenGL SSBO.
// -----------------------------------------------------------------------------

struct FlockMember
{
    glm::vec4 position;
    glm::vec4 velocity;
};

struct Obstacle
{
    glm::vec4 centerRadius;
};

struct DirectionPoint
{
    glm::vec4 direction;
};

struct CudaFlockMember
{
    float4 position;
    float4 velocity;
};

static_assert(sizeof(CudaFlockMember) == 32,
              "Unexpected CudaFlockMember size");

// -----------------------------------------------------------------------------
// CUDA BOIDS kernel declaration
// -----------------------------------------------------------------------------

cudaError_t BoidsKernelInterface(
    const FlockMember *inputData,
    FlockMember *outputData,
    uint32_t birdCount,
    uint32_t directionCount,
    const DirectionPoint *directionPoints,
    uint32_t obstacleCount,
    const Obstacle *obstacles,
    uint32_t goalCount,
    const float3 *goals,
    float timestep,
    float closest_allowed_dist,
    float rule1_weight,
    float rule2_weight,
    float rule3_weight,
    float rule4_weight,
    float boundaryAvoidanceWeight,
    float obstacleAvoidanceWeight,
    float worldRadius,
    float boundaryMargin,
    float lookAheadDistance,
    float boidRadius,
    float avoidancePaddingFactor,
    float minSpeed,
    float maxSpeed
);

#endif // FLOCK_CUDA_H
