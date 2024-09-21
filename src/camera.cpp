#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 GLOBAL_UP = glm::vec3(0.0f, 1.0f, 0.0f);

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = std::cos(glm::radians(mPitch)) * std::cos(glm::radians(mYaw));
	front.y = std::sin(glm::radians(mPitch));
	front.z = std::cos(glm::radians(mPitch)) * std::sin(glm::radians(mYaw));
	mFront = glm::normalize(front);

	mRight = glm::normalize(glm::cross(mFront, GLOBAL_UP));
	mUp = glm::normalize(glm::cross(mRight, mFront));
}

Camera::Camera(
	const glm::vec3& cameraPos,
	GLfloat yaw,
	GLfloat pitch,
	GLfloat speed,
	GLfloat sensitivity
) :
	mPos{ cameraPos },
	mYaw{ yaw },
	mPitch{ pitch },
	mSpeed{ speed },
	mSensitivity{ sensitivity }
{
	updateVectors();
}

void Camera::processKeyInput(Direction direction, GLfloat deltaTime)
{
	switch (direction)
	{
	case Direction::FORWARD:
		mPos += mFront * mSpeed * deltaTime;
		break;
	case Direction::BACKWARD:
		mPos -= mFront * mSpeed * deltaTime;
		break;
	case Direction::LEFT:
		mPos -= mRight * mSpeed * deltaTime;
		break;
	case Direction::RIGHT:
		mPos += mRight * mSpeed * deltaTime;
		break;
	case Direction::UP:
		mPos += mUp * mSpeed * deltaTime;
		break;
	case Direction::DOWN:
		mPos -= mUp * mSpeed * deltaTime;
	}
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset)
{
	mYaw += xOffset * mSensitivity;
	mPitch += yOffset * mSensitivity;

	if (mPitch > 89.0f)
		mPitch = 89.0f;
	if (mPitch < -89.0f)
		mPitch = -89.0f;

	updateVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(mPos, mPos + mFront, GLOBAL_UP);
}

