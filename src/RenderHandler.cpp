#include "..\headers\RenderHandler.h"

GLFWwindow* RenderHandler::ProgramWindow;
vector<Shader*> RenderHandler::Shaders;
vector<Material*> RenderHandler::Materials;
unsigned int RenderHandler::ShadowDepthMap;
unsigned int RenderHandler::CurrentShader;
unsigned int RenderHandler::CurrentMaterial;
const unsigned int RenderHandler::SHADOW_HEIGHT = 1024;
const unsigned int RenderHandler::SHADOW_WIDTH = 1024;


// Shader Paths
const GLchar* B_VERT_PATH = ".\\shaders\\vertexLShader.glsl";
const GLchar* B_FRAG_PATH = ".\\shaders\\fragmentLShader.glsl";

// Material Path
const GLchar* B_BASE_DIFF = ".\\textures\\blackRubber_diffuse.png";
const GLchar* B_BASE_SPEC = ".\\textures\\blackRubber_specular.png";
const GLchar* B_BODY_DIFF = ".\\textures\\purpleMetal_diffuse.png";
const GLchar* B_BODY_SPEC = ".\\textures\\purpleMetal_specular.png";
const GLchar* G_TILE_DIFF = ".\\textures\\blueTile_diffuse.png";
const GLchar* G_TILE_SPEC = ".\\textures\\blueTile_specular.png";
const GLchar* P_SMOK_DIFF = ".\\textures\\particle_diffuse.png";
const GLchar* P_SMOK_SPEC = ".\\textures\\particle_specular.png";

void RenderHandler::Initialize() {
	// Window Setup
	ProgramWindow = EventHandler::GetWindow();
	glfwMakeContextCurrent(ProgramWindow);

	// Mouse Input
	glfwSetInputMode(ProgramWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cerr << "RENDER_HANDLER::INITIALIZE::FAILED_TO_INITIALIZE_GLEW" << endl;
		glfwTerminate();
		exit(-1);
	}

	// Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// OpenGL States
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	// Shaders
	Shaders.push_back(new Shader(B_VERT_PATH, B_FRAG_PATH));
	CurrentShader = 0;
	SetShader(CurrentShader);

	// Materials
	Materials.push_back(new Material(B_BASE_DIFF, B_BASE_SPEC, 32.0f));
	Materials.push_back(new Material(B_BODY_DIFF, B_BODY_SPEC, 32.0f));
	Materials.push_back(new Material(G_TILE_DIFF, G_TILE_SPEC, 32.0f));
	Materials.push_back(new Material(P_SMOK_DIFF, P_SMOK_SPEC, 16.0f));
	CurrentMaterial = 0;
}

void RenderHandler::Shutdown() {
	// Delete Shaders
	for (Shader* s : Shaders) {
		s->~Shader();
	}
	Shaders.clear();

	ProgramWindow = nullptr;
}

void RenderHandler::FrameStart() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderHandler::FrameEnd() {
	glfwSwapBuffers(ProgramWindow);
}

void RenderHandler::CreateShadowDepthMap() {
	// Generate Depth Framebuffer
	glGenFramebuffers(1, &ShadowDepthMap);
	// Generate Depth Texture
	unsigned int cubeMap;
	glGenTextures(1, &cubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
	for (unsigned int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Attach Texture to Frambuffer
	glBindFramebuffer(GL_FRAMEBUFFER, ShadowDepthMap);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, cubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	// Unbind Framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderHandler::SetShader(unsigned int shaderNumber) {
	CurrentShader = shaderNumber;
	Shaders[CurrentShader]->UseShader();
}

void RenderHandler::SetMaterial(unsigned int materialNumber) {
	CurrentMaterial = materialNumber;
	Materials[CurrentMaterial]->UseMaterial(Shaders[CurrentShader]);
}
