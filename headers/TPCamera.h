#ifndef TPCAMERA_H
#define TPCAMERA_H
// Includes
#include "Camera.h"
// Namespaces
using namespace glm;
// Class
class TPCamera : public Camera {
public:
	// Constructor
	TPCamera(vec3 position, vec3 lookAt, vec3 up);
	// Destructor
	virtual ~TPCamera();

	// Update Functions
	virtual void Update(float dt);

	// Getters
	vec3 GetPosition() {
		return Position;
	}
	vec3 GetLookAt() {
		return LookAt;
	}
	virtual mat4 GetViewMatrix() const;
	virtual mat4 GetProjectionMatrix() const;

	// Setters
	virtual void SetPosition(vec3 position);
	virtual void SetLookAt(vec3 lookat);
	virtual void SetUp(vec3 up);
	virtual void SetRight(vec3 right);
	virtual void SetFOV(float fov);
private:
	vec3 Position;
	vec3 LookAt;
	vec3 Up;
	vec3 Right;
	float FOV;
};
#endif // !TPCAMERA_H