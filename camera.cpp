#include "camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front)
{
	sensitivity = 0.1f;
	this->position = position;
	this->up = up;
	this->front = front;
	yaw = -90.0f;
	pitch = 0.0f;
	zoom = 45.0f;
}

Camera::Camera(float sensitivity, glm::vec3 position, glm::vec3 up, glm::vec3 front)
{
	this->sensitivity = sensitivity;
	this->position = position;
	this->up = up;
	this->front = front;
	yaw = -90.0f;
	pitch = 0.0f;
	zoom = 45.0f;
}

void Camera::setFront()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
};

void Camera::changeUp(glm::vec3 pos)
{
	up += pos;
}
void Camera::moveRight(float cameraSpeed)
{
	position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	std::cout << position.x  << position.y << position.z << std::endl;
}

void Camera::moveLeft(float cameraSpeed)
{

	position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
}

void Camera::moveUp(float cameraSpeed)
{
	position += up * cameraSpeed;
}

void Camera::moveDown(float cameraSpeed)
{
	position -= up * cameraSpeed;
}
void Camera::rotate(float xoffset, float yoffset)
{
	yaw += xoffset * sensitivity;
	pitch += yoffset * sensitivity;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
}

void Camera::zoomCamera(double yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f)
	{
		zoom = 1.0f;
	}
	if (zoom > 45.0f)
	{
		zoom = 45.0f;
	}
}

void Camera::moveForward(float cameraSpeed)
{
	position += front * cameraSpeed;
}

void Camera::moveBackward(float cameraSpeed)
{
	position -= front * cameraSpeed;
}