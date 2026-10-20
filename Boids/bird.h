
#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "pyramid.h"
#include "Point.h"

#define NR_POINTS 300

class Bird
{
public:
	Bird();
	~Bird();

	void Initialize();
	void Draw(glm::mat4 &projectionMatrix, glm::mat4 &modelMatrix, glm::mat4 &viewMatrix);
	glm::mat4 GetModelMatrix() const;
	void Update();
	void Uninitialize();

	void SetFront(glm::vec3 newFront);

	glm::vec3 GetFront() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetVelocity() const;
	void SetOrientation(glm::quat newOrientation);
	void Rotate(glm::quat rotation);
	void RotateAroundAxis(glm::vec3 axis, float angleInRadians);
	void SetPosition(glm::vec3 newPosition);
	glm::vec3 GetPosition() const;

	// Sight and collision avoidance
	bool IsInSight(const Bird *otherBird) const;
	void AvoidCollision(glm::vec3 threatDirection, float avoidanceStrength = 0.1f);
	void Align(glm::vec3 desiredDirection, float alignmentStrength = 0.1f);
	void SeekPosition(glm::vec3 targetPosition, float cohesionStrength = 0.1f);

	void SetBoundary(float newBoundary) { boundary = newBoundary; }

	std::vector<Point *> GetPoints() const { return points; }

	void SetSpeed(float newSpeed) { this->speed = newSpeed; }

private:
	glm::vec3 position;
	float speed;
	Pyramid *pyr;

	glm::mat4 modelMatrix;

	glm::quat orientationFinal;
	glm::quat orientationNew;

	// Sight parameters
	float sightRadius = 0.0f;						// How far the bird can see
	float blindAngleRadians = glm::radians(120.0f); // 120 degree blindness angle behind

	float boundary;

	std::vector<Point *> points;
};

Bird::Bird()
	: position(0.0f, 0.0f, 0.0f), speed(0.0f), pyr(nullptr), modelMatrix(glm::mat4(1.0f)), orientationFinal(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), orientationNew(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), boundary(50.0f), sightRadius(10.0f)
{
	// Code
	pyr = new Pyramid();
}

Bird::~Bird()
{
	delete (pyr);
}

void Bird::Initialize()
{
	pyr->Initialize();

	speed = 0.5f;

	sightRadius = 20.0f;

	glPointSize(1.0f);

	float turnFraction = 0.618033f;

	for (int i = 0; i < NR_POINTS; i++)
	{
		Point *point = new Point();
		if (NULL == point)
		{
			return;
		}
		point->Initialize();

		float dst = i / (float)NR_POINTS;
		float inclination = acos(1.0f - 2.0f * dst);
		float azimuth = turnFraction * i;

		float x = sin(inclination) * cos(azimuth);
		float z = sin(inclination) * sin(azimuth);
		float y = cos(inclination);

		point->SetPosition(glm::vec3(x * sightRadius, y * sightRadius, z * sightRadius));

		// directions.push_back(glm::vec3(x, y, z));

		if (i < NR_POINTS / 10)
		{
			point->SetColor(glm::vec3(1.0f, 0.0f, 0.0f)); // Red points
		}
		points.push_back(point);
	}
}

void Bird::Draw(glm::mat4 &projectionMatrix, glm::mat4 &modelMatrix, glm::mat4 &viewMatrix)
{
	// Code

	// model matrix from position, front and right

	pyr->Draw(projectionMatrix, modelMatrix, viewMatrix);
}

glm::mat4 Bird::GetModelMatrix() const
{
	return modelMatrix;
}

void Bird::Update()
{
	// Code for updating bird position and rotation
	// position += GetFront() * speed;

	if (position[1] > boundary)
	{
		position[1] = -boundary;
	}
	else if (position[1] < -boundary)
	{
		position[1] = boundary;
	}

	if (position[0] > boundary)
	{
		position[0] = -boundary;
	}
	else if (position[0] < -boundary)
	{
		position[0] = boundary;
	}

	if (position[2] > boundary)
	{
		position[2] = -boundary;
	}
	else if (position[2] < -boundary)
	{
		position[2] = boundary;
	}

	// Smooth transition from current orientation to new orientation
	orientationFinal = glm::slerp(orientationFinal, orientationNew, 0.5f);

	// Convert quaternion to rotation matrix
	glm::mat4 rotationMatrix = glm::mat4_cast(orientationFinal);

	glm::mat4 glmRotation;
	glmRotation[0][0] = rotationMatrix[0][0];
	glmRotation[0][1] = rotationMatrix[0][1];
	glmRotation[0][2] = rotationMatrix[0][2];
	glmRotation[0][3] = rotationMatrix[0][3];
	glmRotation[1][0] = rotationMatrix[1][0];
	glmRotation[1][1] = rotationMatrix[1][1];
	glmRotation[1][2] = rotationMatrix[1][2];
	glmRotation[1][3] = rotationMatrix[1][3];
	glmRotation[2][0] = rotationMatrix[2][0];
	glmRotation[2][1] = rotationMatrix[2][1];
	glmRotation[2][2] = rotationMatrix[2][2];
	glmRotation[2][3] = rotationMatrix[2][3];
	glmRotation[3][0] = rotationMatrix[3][0];
	glmRotation[3][1] = rotationMatrix[3][1];
	glmRotation[3][2] = rotationMatrix[3][2];
	glmRotation[3][3] = rotationMatrix[3][3];

	// Apply orientation to model matrix: translate * rotate * scale
	modelMatrix = glm::translate(position) * glmRotation * glm::scale(1.0f, 1.0f, 1.0f);
}

void Bird::Uninitialize()
{
	if (pyr)
	{
		pyr->Uninitialize();
	}
}

glm::vec3 Bird::GetFront() const
{
	// Extract Y-axis (forward direction) from quaternion rotation matrix
	glm::mat4 rotMat = glm::mat4_cast(orientationFinal);
	return glm::vec3(rotMat[1][0], rotMat[1][1], rotMat[1][2]);
}

glm::vec3 Bird::GetVelocity() const
{
	return (GetFront() * speed);
}

glm::vec3 Bird::GetRight() const
{
	// Extract X-axis (right direction) from quaternion rotation matrix
	glm::mat4 rotMat = glm::mat4_cast(orientationFinal);
	return glm::vec3(rotMat[0][0], rotMat[0][1], rotMat[0][2]);
}

void Bird::SetOrientation(glm::quat newOrientation)
{
	// Directly set the orientation quaternion
	orientationFinal = glm::normalize(newOrientation);
}

void Bird::Rotate(glm::quat rotation)
{
	// Apply an additional rotation to the current orientation
	orientationNew = glm::normalize(rotation * orientationFinal);
}

void Bird::RotateAroundAxis(glm::vec3 axis, float angleInRadians)
{
	// Create a quaternion rotation and apply it
	glm::vec3 glmAxis(axis[0], axis[1], axis[2]);
	glm::quat rotation = glm::angleAxis(angleInRadians, glm::normalize(glmAxis));
	Rotate(rotation);
}

void Bird::SetFront(glm::vec3 newFront)
{
	// Code for setting the front direction
	glm::mat4 rotMat = glm::mat4_cast(orientationFinal);
	rotMat[1][0] = newFront[0];
	rotMat[1][1] = newFront[1];
	rotMat[1][2] = newFront[2];
	orientationFinal = glm::quat_cast(rotMat);
}

void Bird::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

glm::vec3 Bird::GetPosition() const
{
	return position;
}

bool Bird::IsInSight(const Bird *otherBird) const
{
	if (!otherBird)
		return false;

	glm::vec3 otherPos = otherBird->GetPosition();
	glm::vec3 directionToOther = otherPos - position;
	float distanceToOther = glm::length(glm::vec3(directionToOther[0], directionToOther[1], directionToOther[2]));

	// Check if within sight radius
	if (distanceToOther > sightRadius || distanceToOther < 0.0001f)
		return false;

	// Normalize direction
	glm::vec3 temp = glm::normalize(glm::vec3(directionToOther[0], directionToOther[1], directionToOther[2]));
	directionToOther = glm::vec3(temp[0], temp[1], temp[2]);
	glm::vec3 front = GetFront();

	// Check if within field of view (not in blind spot behind)
	float dotProduct = directionToOther[0] * front[0] + directionToOther[1] * front[1] + directionToOther[2] * front[2];
	float angleToOther = acos(glm::clamp(dotProduct, -1.0f, 1.0f));

	// If the angle is greater than blindAngleRadians/2, it's in the blind spot
	if (angleToOther > blindAngleRadians / 2.0f)
		return false;

	return true;
}

void Bird::AvoidCollision(glm::vec3 avoidanceDirection, float avoidanceStrength)
{
	// avoidanceDirection is the direction to move away from the threat
	// Normalize avoidance direction
	glm::vec3 glmAvoidDir = glm::normalize(glm::vec3(avoidanceDirection[0], avoidanceDirection[1], avoidanceDirection[2]));
	avoidanceDirection = glm::vec3(glmAvoidDir[0], glmAvoidDir[1], glmAvoidDir[2]);

	// Get current front direction
	glm::vec3 currentFront = GetFront();
	glm::vec3 glmCurrentFront(currentFront[0], currentFront[1], currentFront[2]);

	// Calculate rotation axis using cross product for proper 3D steering
	// This gives us the axis perpendicular to both current direction and desired direction
	glm::vec3 rotationAxis = glm::cross(glmCurrentFront, glmAvoidDir);

	// If axis is near zero (birds are parallel), use a default perpendicular
	if (glm::length(rotationAxis) < 0.001f)
	{
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	rotationAxis = glm::normalize(rotationAxis);

	// Create a rotation quaternion to steer toward avoidance direction
	glm::quat avoidanceRotation = glm::angleAxis(avoidanceStrength, rotationAxis);
	Rotate(avoidanceRotation);
}

void Bird::Align(glm::vec3 desiredDirection, float alignmentStrength)
{
	// Align bird toward the desired direction (average heading of flockmates)
	// Normalize desired direction
	glm::vec3 glmDesiredDir = glm::normalize(glm::vec3(desiredDirection[0], desiredDirection[1], desiredDirection[2]));
	desiredDirection = glm::vec3(glmDesiredDir[0], glmDesiredDir[1], glmDesiredDir[2]);

	// Get current front direction
	glm::vec3 currentFront = GetFront();
	glm::vec3 glmCurrentFront(currentFront[0], currentFront[1], currentFront[2]);

	// Calculate rotation axis using cross product for proper 3D steering
	glm::vec3 rotationAxis = glm::cross(glmCurrentFront, glmDesiredDir);

	// If axis is near zero (birds are already aligned), skip
	if (glm::length(rotationAxis) < 0.001f)
	{
		return;
	}

	rotationAxis = glm::normalize(rotationAxis);

	// Create a rotation quaternion to steer toward desired direction
	glm::quat alignmentRotation = glm::angleAxis(alignmentStrength, rotationAxis);
	Rotate(alignmentRotation);
}

void Bird::SeekPosition(glm::vec3 targetPosition, float cohesionStrength)
{
	// Steer toward the target position (center of mass)
	// Calculate direction to target
	glm::vec3 directionToTarget = targetPosition - position;

	// Normalize direction to target
	glm::vec3 glmDirToTarget = glm::normalize(glm::vec3(directionToTarget[0], directionToTarget[1], directionToTarget[2]));
	directionToTarget = glm::vec3(glmDirToTarget[0], glmDirToTarget[1], glmDirToTarget[2]);

	// Get current front direction
	glm::vec3 currentFront = GetFront();
	glm::vec3 glmCurrentFront(currentFront[0], currentFront[1], currentFront[2]);

	// Calculate rotation axis using cross product for proper 3D steering
	glm::vec3 rotationAxis = glm::cross(glmCurrentFront, glmDirToTarget);

	// If axis is near zero (already pointing at target), skip
	if (glm::length(rotationAxis) < 0.001f)
	{
		return;
	}

	rotationAxis = glm::normalize(rotationAxis);

	// Create a rotation quaternion to steer toward the target
	glm::quat cohesionRotation = glm::angleAxis(cohesionStrength, rotationAxis);
	Rotate(cohesionRotation);
}
