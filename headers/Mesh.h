#ifndef MESH_H
#define MESH_H
// Includes
#include "Constants.h"
#include "RenderHandler.h"

#include <gtc/matrix_transform.hpp>
#include <vector>

// Namespaces
using namespace std;
using namespace glm;
using namespace Constants;

// Class
class Mesh {
public:
	// Constructor
	Mesh();
	// Destructor
	virtual ~Mesh();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw() = 0;

	// Getters
	virtual mat4 GetWorldMatrix();
	virtual mat4 GetRelativeMatrix();

	vec3 GetPosition() {
		return Position;
	}
	vec3 GetScale() {
		return Scale;
	}
	float GetRotationAngle() {
		return RotationAngle;
	}

	// Setters
	void SetPosition(vec3 position);
	void SetAxis(vec3 axis);
	void SetRotation(float rotationAngle);
	void SetRelativeMatrix(mat4 relativeMatrix);
	void ChangeRotationAngle(float rotationAngle);

protected:
	// Attributes
	vec3 Position;
	vec3 Scale;
	vec3 Axis;
	float RotationAngle;

	mat4 WorldMatrix;
	mat4 RelativeMatrix;

	// Vertex Definition
	struct Vertex {
		vec3 Position;
		vec3 Normal;
		vec3 Colour;
		vec2 TexUV;
	};

	// Buffers
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	// Data
	vector<Vertex> Vertices;
	vector<unsigned int> Indices;
	unsigned int MaterialNumber;
};
#endif // !MESH_H