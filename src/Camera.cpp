#include "..\headers\Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

mat4 Camera::GetProjectionMatrix() const {
	return perspective(
		radians(45.0f),
		(float)EventHandler::GetScreenWidth() / (float)EventHandler::GetScreenHeight(),
		0.1f,
		100.0f
	);
}

mat4 Camera::GetViewProjectionMatrix() const
{
	return GetProjectionMatrix() * GetViewMatrix();
}
