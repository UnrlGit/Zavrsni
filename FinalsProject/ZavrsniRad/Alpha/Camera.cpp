#include "Camera.h"



void Camera::KeyboardControl(bool * keys, GLfloat deltaTime)
{
	GLfloat velocity = _moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		_position += _front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		_position -= _front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		_position -= _right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		_position += _right * velocity;
	}

	// polygon mode
	if (keys[GLFW_KEY_U])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (keys[GLFW_KEY_I])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= _turnSpeed;
	yChange *= _turnSpeed;
	_yaw += xChange;
	_pitch += yChange;

	LimitUpDownLook();
	Set_FrontRightUp();
}

// TODO TEST LOWER 2 WITH AND WITHOUT NORMALIZE
glm::vec3 Camera::GetCameraPosition()
{
	return glm::normalize(_front);
}

glm::vec3 Camera::GetCameraDirection()
{
	return glm::normalize(_front);
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}

void Camera::Set_FrontRightUp()
{
	_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front.y = sin(glm::radians(_pitch));
	_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(_front); // normalizing

	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front)); //cross product
}

void Camera::LimitUpDownLook()
{
	if (_pitch > 89.0f)
	{
		_pitch = 89.0f;
	}
	if (_pitch < -89.0f)
	{
		_pitch = -89.0f;
	}
}