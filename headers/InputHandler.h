#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
// Includes
#include "EventHandler.h"
#include "RenderHandler.h"
#include "World.h"

#include "gtx/rotate_vector.hpp"

// Class
class InputHandler {
public:
	static void Update(World* RenderWorld);

private:
	static GLFWwindow* ProgramWindow;

	// Camera
	static float CurrentCameraSpeed;
	static float DefaultCameraSpeed;
	static float FastCameraSpeed;

	static vec3 CameraPos;
	static vec3 LookAt;
	static vec3 CameraUp;
	static vec3 CameraDirection;
	static float FOV;

	// Flags
	static bool keyLPressed;
	static bool keyHPressed;
	static bool keyCPressed;

};
#endif // !INPUT_HANDLER_H