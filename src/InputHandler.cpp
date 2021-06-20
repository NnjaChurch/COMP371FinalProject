#include "..\headers\InputHandler.h"

GLFWwindow* InputHandler::ProgramWindow;

vec3 InputHandler::CameraPos = Constants::DEF_CAMERA_POSITION;
vec3 InputHandler::LookAt = Constants::DEF_CAMERA_LOOKAT;
vec3 InputHandler::CameraUp = Constants::AXIS_Y;
vec3 InputHandler::CameraDirection = normalize(InputHandler::CameraPos - InputHandler::LookAt);
float InputHandler::FOV = 45.0f;

float InputHandler::DefaultCameraSpeed = Constants::DEF_CAMERA_SPEED;
float InputHandler::FastCameraSpeed = 20.0f;
float InputHandler::CurrentCameraSpeed = 10.0f;

bool InputHandler::keyCPressed = false;
bool InputHandler::keyLPressed = false;
bool InputHandler::keyHPressed = false;

void InputHandler::Update(World* RenderWorld) {
	// Window
	ProgramWindow = EventHandler::GetWindow();
	// Time
	float dt = EventHandler::GetFrameTime();

	// Hotkey Checks

	// Exit
	if (glfwGetKey(ProgramWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(ProgramWindow, true);
	}

	// Toggles
	if (glfwGetKey(ProgramWindow, GLFW_KEY_L) == GLFW_PRESS) {
		if (!keyLPressed) {
			RenderWorld->ToggleLights();
		}
		keyLPressed = true;
	}
	else {
		keyLPressed = false;
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_C) == GLFW_PRESS) {
		if (!keyCPressed) {
			RenderWorld->ToggleCamera();
		}
		keyCPressed = true;
	}
	else {
		keyCPressed = false;
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_H) == GLFW_PRESS) {
		if (!keyHPressed) {
			RenderWorld->ToggleAnimation();
		}
		keyHPressed = true;
	}
	else {
		keyHPressed = false;
	}

	// Camera
	if (glfwGetKey(ProgramWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(ProgramWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
		CurrentCameraSpeed = FastCameraSpeed;
	}
	else {
		CurrentCameraSpeed = DefaultCameraSpeed;
	}

	if (glfwGetMouseButton(ProgramWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		CameraPos = rotate(CameraPos, radians(EventHandler::GetMouseX() * CurrentCameraSpeed * dt), Constants::AXIS_Y);
	}
	if (glfwGetMouseButton(ProgramWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		FOV += EventHandler::GetMouseY() * CurrentCameraSpeed * dt;
		if (FOV <= 1.0f) {
			FOV = 1.0f;
		}
		if (FOV >= 60.0f) {
			FOV = 60.0f;
		}
	}
	if (glfwGetMouseButton(ProgramWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		CameraPos = rotate(CameraPos, radians(EventHandler::GetMouseY() * CurrentCameraSpeed * dt), cross(Constants::AXIS_Y, CameraPos));
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_HOME) == GLFW_PRESS) {
		CameraPos = Constants::DEF_CAMERA_POSITION;
		LookAt = Constants::DEF_CAMERA_LOOKAT;
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_W) == GLFW_PRESS) {
		vec3 CameraChange = CurrentCameraSpeed * CameraDirection * dt;
		CameraPos -= CameraChange;
		LookAt -= CameraChange;
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_S) == GLFW_PRESS) {
		vec3 CameraChange = CurrentCameraSpeed * CameraDirection * dt;
		CameraPos += CameraChange;
		LookAt += CameraChange;
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_A) == GLFW_PRESS) {
		vec3 CameraChange = normalize(cross(CameraDirection, CameraUp)) * CurrentCameraSpeed * dt;
		CameraPos += CameraChange;
		LookAt += CameraChange;

	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_D) == GLFW_PRESS) {
		vec3 CameraChange = normalize(cross(CameraDirection, CameraUp)) * CurrentCameraSpeed * dt;
		CameraPos -= CameraChange;
		LookAt -= CameraChange;	
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
		vec3 CameraChange = CurrentCameraSpeed * CameraUp * dt;
		CameraPos += CameraChange;
		LookAt += CameraChange;
	}
	if (glfwGetKey(ProgramWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		vec3 CameraChange = CurrentCameraSpeed * CameraUp * dt;
		CameraPos -= CameraChange;
		LookAt -= CameraChange;
	}

	// Update Camera Values
	CameraDirection = normalize(CameraPos - LookAt);
	RenderWorld->GetCurrentCamera()->SetPosition(CameraPos);
	RenderWorld->GetCurrentCamera()->SetLookAt(LookAt);
	RenderWorld->GetCurrentCamera()->SetFOV(FOV);
}
