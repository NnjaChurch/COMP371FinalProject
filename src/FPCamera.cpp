#include "..\headers\FPCamera.h"

FPCamera::FPCamera(vec3 position) : Camera(), 
Position(position), 
LookAt(Constants::DEF_CAMERA_LOOKAT),
Horizontal(Constants::DEF_HORIZONTAL_ANGLE),
Vertical(Constants::DEF_VERTICAL_ANGLE),
Speed(Constants::DEF_CAMERA_SPEED),
Angular(Constants::DEF_CAMERA_ROTATION_SPEED) {
}

FPCamera::~FPCamera() {
}

void FPCamera::Update(float dt) {
	Horizontal -= EventHandler::GetMouseX() * Angular * dt;
	Vertical -= EventHandler::GetMouseY() * Angular * dt;

	Vertical = max(-85.0f, min(85.0f, Vertical));
	if (Horizontal > 360) {
		Horizontal -= 360;
	}
	if (Horizontal < -360) {
		Horizontal += 360;
	}

	float theta = radians(Horizontal);
	float phi = radians(Vertical);

	LookAt = vec3(
		cosf(phi) * cosf(theta),
		sinf(phi),
		-cosf(phi) * sinf(theta)
	);
	vec3 sideVector = cross(LookAt, Constants::AXIS_Y);
	normalize(sideVector);
}

mat4 FPCamera::GetViewMatrix() const
{
	return lookAt(Position, Position + LookAt, Constants::AXIS_Y);
}

void FPCamera::SetPosition(vec3 position) {
	Position = position;
}

void FPCamera::SetLookAt(vec3 lookAt) {
}

void FPCamera::SetUp(vec3 up) {
}

void FPCamera::SetRight(vec3 right) {
}

void FPCamera::SetFOV(float fov) {
}
