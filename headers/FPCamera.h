#ifndef FP_CAMERA_H
#define FP_CAMERA_H
// Includes
#include "Camera.h"
// Class
class FPCamera : public Camera {
public:
	// Constructor
	FPCamera(vec3 position);
	// Destructor
	virtual ~FPCamera();

	virtual void Update(float dt);

	virtual mat4 GetViewMatrix() const;

	vec3 GetPosition() {
		return Position;
	}
	vec3 GetLookAt() {
		return LookAt;
	}

	void SetPosition(vec3 position);
	virtual void SetLookAt(vec3 lookAt);
	virtual void SetUp(vec3 up);
	virtual void SetRight(vec3 right);
	virtual void SetFOV(float fov);

private:
	vec3 Position;
	float Horizontal;
	float Vertical;

	float Speed;
	float Angular;

	vec3 LookAt;

};




#endif // !FP_CAMERA_H
