#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
// Includes
#include "Constants.h"
#include <GLFW/glfw3.h>
#include <iostream>

struct GLFWwindow;
// Class
class EventHandler {
public:
	// Functions
	static void Initialize();
	static void Shutdown();

	// Update Functions
	static void Update();
	static void framebuffer_size_callback(GLFWwindow* ProgramWindow, int width, int height);

	// Data Functions
	static float GetFrameTime() {
		return dt;
	}
	static bool GetExitRequest() {
		return glfwWindowShouldClose(ProgramWindow);
	}

	// Getters
	static GLFWwindow* GetWindow() {
		return ProgramWindow;
	}
	static float GetMouseX() {
		return dx;
	}
	static float GetMouseY() {
		return dy;
	}
	static unsigned int GetScreenWidth() {
		return SCR_WIDTH;
	}
	static unsigned int GetScreenHeight() {
		return SCR_HEIGHT;
	}

private:
	// Screen Attributes
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	// Time Attributes
	static double lastFrameTime;
	static float dt;
	// Mouse Attributes
	static double lastMouseX;
	static double lastMouseY;
	static float dx;
	static float dy;
	// Window Attributes
	static GLFWwindow* ProgramWindow;
};
#endif // !EVENT_HANDLER_H

