#include "..\headers\Mesh.h"

Mesh::Mesh() : Position(DEF_POSITION), Scale(DEF_SCALING), RotationAngle(DEF_ROTATION_ANGLE), WorldMatrix(mat4(1.0f)), RelativeMatrix(mat4(1.0f)), MaterialNumber(0) {
}

Mesh::~Mesh() {
}

void Mesh::Update(float dt) {
	mat4 t = translate(mat4(1.0f), Position);
	mat4 nt = translate(mat4(1.0f), -Position);
	mat4 s = scale(mat4(1.0f), Scale);
	mat4 r = rotate(mat4(1.0f), radians(RotationAngle), Axis);
	WorldMatrix = RelativeMatrix * t * r * s;
	RelativeMatrix = t * r * nt;
}

mat4 Mesh::GetWorldMatrix() {
	return WorldMatrix;
}

mat4 Mesh::GetRelativeMatrix()
{
	return RelativeMatrix;
}

void Mesh::SetPosition(vec3 position) {
	Position.x = position.x;
	Position.y = position.y;
	Position.z = position.z;
}

void Mesh::SetAxis(vec3 axis) {
	Axis = axis;
}

void Mesh::SetRotation(float rotationAngle) {
	RotationAngle -= rotationAngle;
}

void Mesh::SetRelativeMatrix(mat4 relativeMatrix) {
	RelativeMatrix = relativeMatrix;
}

void Mesh::ChangeRotationAngle(float rotationAngle) {
	RotationAngle = rotationAngle;
}

