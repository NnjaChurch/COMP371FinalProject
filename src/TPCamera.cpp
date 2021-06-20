#include "..\headers\TPCamera.h"

TPCamera::TPCamera(vec3 position, vec3 lookAt, vec3 up) : Camera(), Position(position), LookAt(lookAt), Up(up), FOV(45.0f) {
}

TPCamera::~TPCamera() {
}

void TPCamera::Update(float dt) {
}

mat4 TPCamera::GetViewMatrix() const {
	return lookAt(
		Position,
		LookAt,
		Up
	);
}

mat4 TPCamera::GetProjectionMatrix() const
{
	return perspective(
		radians(FOV),
		(float)EventHandler::GetScreenWidth() / (float)EventHandler::GetScreenHeight(),
		0.1f,
		100.0f
	);
}

void TPCamera::SetPosition(vec3 position) {
	Position = position;
}

void TPCamera::SetLookAt(vec3 lookat) {
	LookAt = lookat;
}

void TPCamera::SetUp(vec3 up) {
	Up = up;
}

void TPCamera::SetRight(vec3 right) {
	Right = right;
}

void TPCamera::SetFOV(float fov) {
	FOV = fov;
}
