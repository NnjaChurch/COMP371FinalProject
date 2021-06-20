#include "..\headers\EventHandler.h"

float EventHandler::dt = 0.0f;
double EventHandler::lastFrameTime = glfwGetTime();
double EventHandler::lastMouseX = 0.0f;
double EventHandler::lastMouseY = 0.0f;
float EventHandler::dx = 0.0f;
float EventHandler::dy = 0.0f;
GLFWwindow* EventHandler::ProgramWindow;
unsigned int EventHandler::SCR_WIDTH = 1024;
unsigned int EventHandler::SCR_HEIGHT = 768;


void EventHandler::Initialize() {
	if (!glfwInit()) {
		cerr << "EVENT_HANDLER::INITIALIZE::FAILED_TO_INTIALIZE_GLFW" << endl;
		exit(-1);
	}

#if defined(PLATFORM_OSX)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#endif

	glfwWindowHint(GLFW_RESIZABLE, 1);
	ProgramWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "COMP371 - FINAL PROJECT", nullptr, nullptr);

	if (ProgramWindow == nullptr) {
		cerr << "EVENT_HANDLER::INITIALIZE::FAILED_TO_CREATE_WINDOW" << endl;
		glfwTerminate();
		exit(-1);
	}

	// Sticky Key Input
	glfwSetInputMode(ProgramWindow, GLFW_STICKY_KEYS, GL_TRUE);

	// Mouse
	glfwPollEvents();
	double mouseX, mouseY;
	glfwGetCursorPos(ProgramWindow, &mouseX, &mouseY);

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// Frame Time
	lastFrameTime = glfwGetTime();

	// Resize
	glfwSetFramebufferSizeCallback(ProgramWindow, framebuffer_size_callback);
}

void EventHandler::Shutdown() {
	glfwTerminate();
	ProgramWindow = nullptr;
}

void EventHandler::Update() {
	// Get Events
	glfwPollEvents();

	// Mouse
	double mouseX, mouseY;
	glfwGetCursorPos(ProgramWindow, &mouseX, &mouseY);
	dx = (float)(mouseX - lastMouseX);
	dy = (float)(mouseY - lastMouseY);
	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// Time
	double frameTime = glfwGetTime();
	dt = (float)(frameTime - lastFrameTime);
	lastFrameTime = frameTime;
}

void EventHandler::framebuffer_size_callback(GLFWwindow* ProgramWindow, int width, int height) {
	glfwSetWindowAspectRatio(ProgramWindow, 4, 3);
	glfwSetWindowSize(ProgramWindow, width, height);
	glViewport(0, 0, width, height);
}