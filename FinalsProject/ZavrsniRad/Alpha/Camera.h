//#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera() {}
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
		: _position(startPosition), _front(glm::vec3(0.0f, 0.0f, -1.0f)), _worldUp(startUp),
		_yaw(startYaw), _pitch(startPitch),
		_moveSpeed(startMoveSpeed), _turnSpeed(startTurnSpeed) {}
	~Camera() {}

	void KeyboardControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 GetCameraPosition();
	glm::vec3 GetCameraDirection();

	glm::mat4 CalculateViewMatrix();

private:
	glm::vec3 _position; //position of the camera in xyz
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	GLfloat _yaw;
	GLfloat _pitch;

	GLfloat _moveSpeed;
	GLfloat _turnSpeed;

	void Set_FrontRightUp();
	void LimitUpDownLook();
};
#endif // !CAMERA_H
