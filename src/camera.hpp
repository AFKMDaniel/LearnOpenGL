#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 2.0f;
const GLfloat SENSITIVITY = 0.25f;

enum class Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
private:
	GLfloat mYaw;
	GLfloat mPitch;

	GLfloat mSpeed;
	GLfloat mSensitivity;

	glm::vec3 mGlobalUp;
	glm::vec3 mPos;
	glm::vec3 mFront;
	glm::vec3 mUp;
	glm::vec3 mRight;

private:
	void updateVectors();

public:
	Camera(
		const glm::vec3& cameraPos = glm::vec3{ 0.0f, 0.0f, 0.0f },
		const glm::vec3& up = glm::vec3( 0.0f, 1.0f, 0.0f ),
		GLfloat yaw = YAW,
		GLfloat pitch = PITCH,
		GLfloat speed = SPEED,
		GLfloat sensitivity = SENSITIVITY
	);
	void processKeyInput(Direction direction, GLfloat deltaTime);
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset);
	glm::mat4 getViewMatrix();
};
