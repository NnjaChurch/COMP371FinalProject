#ifndef CAMERA_H
#define CAMERA_H
// Includes
#include "EventHandler.h"

#include <gtc/matrix_transform.hpp>
// Class
class Camera {
public:
	// Constructor
	Camera();
	// Destructor
	virtual ~Camera();

	// Update
	virtual void Update(float dt) = 0;

	// Getters
	virtual vec3 GetPosition() = 0;
	virtual vec3 GetLookAt() = 0;
	virtual mat4 GetViewMatrix() const = 0;
	virtual mat4 GetProjectionMatrix() const;
	virtual mat4 GetViewProjectionMatrix() const;

	// Setters
	virtual void SetPosition(vec3 position) = 0;
	virtual void SetLookAt(vec3 lookAt) = 0;
	virtual void SetUp(vec3 up) = 0;
	virtual void SetRight(vec3 right) = 0;
	virtual void SetFOV(float fov) = 0;
};
#endif // !CAMERA_H