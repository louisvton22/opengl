#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
class Camera
{
public:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 position;
	float sensitivity;
	float zoom;
	float yaw;
	float pitch;
	Camera(float sensitivity, glm::vec3 position, glm::vec3 up, glm::vec3 front);
	Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front);
	void setFront();
	void changeUp(glm::vec3 pos);
	void moveRight(float cameraSpeed);
	void moveLeft(float cameraSpeed);
	void moveUp(float cameraSpeed);
	void moveDown(float cameraSpeed);
	void moveForward(float cameraSpeed);
	void moveBackward(float cameraSpeed);
	void zoomCamera(double yoffset);
	void rotate(float xoffset, float yoffset);
};


#endif // CAMERA_H