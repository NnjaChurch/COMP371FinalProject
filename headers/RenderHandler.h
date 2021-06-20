#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H
// Includes
#include "Shader.h"
#include "Material.h"
#include "EventHandler.h"

#include <GLFW/glfw3.h>
#include <vector>

// Namespaces
using namespace glm;

struct GLFWwindow;

// Class
class RenderHandler {
public:
	// Functions
	static void Initialize();
	static void Shutdown();

	static void FrameStart();
	static void FrameEnd();

	static void CreateShadowDepthMap();

	// Getters
	static Shader* GetCurrentShader() {
		return Shaders[CurrentShader];
	}
	static unsigned int GetShaderNumber() {
		return CurrentShader;
	}
	static unsigned int GetShaderID() {
		return Shaders[CurrentShader]->GetShaderID();
	}

	// Setters
	static void SetShader(unsigned int shaderNumber);
	static void SetMaterial(unsigned int materialNumber);

private:
	static GLFWwindow* ProgramWindow;
	static vector<Shader*> Shaders;
	static vector<Material*> Materials;
	static const unsigned int SHADOW_HEIGHT;
	static const unsigned int SHADOW_WIDTH;
	static unsigned int ShadowDepthMap;
	static unsigned int CurrentShader;
	static unsigned int CurrentMaterial;
};
#endif // !RENDER_HANDLER_H