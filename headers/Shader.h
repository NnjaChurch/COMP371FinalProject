#ifndef SHADER_H
#define SHADER_H
// Includes
#include "Constants.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
// Namespaces
using namespace std;
// Class
class Shader {
public:
	// Constructor
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	// Destructor
	virtual ~Shader();

	// Functions
	void UseShader();

	// Getters
	unsigned int GetShaderID() {
		return ID;
	}

	// Setters
	void SetInt(const string& name, int value) const;
	void SetFloat(const string& name, float value) const;
	void SetVec3(const string& name, vec3& value) const;
	void SetBool(const string& name, bool value) const;
	void SetViewMatrix(mat4 viewMatrix);
	void SetProjectionMatrix(mat4 projectionMatrix);
	void SetWorldMatrix(mat4 worldMatrix);

private:
	// Attributes
	unsigned int ID;
};
#endif // !SHADER_H
