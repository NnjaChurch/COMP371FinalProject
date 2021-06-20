#ifndef MATERIAL_H
#define MATERIAL_H
// Includes
#include "Constants.h"
#include "Shader.h"
#include <FreeImageIO.h>

// Class
class Material {
public:
	// Constructor
	Material(const GLchar* diffusePath, const GLchar* specularPath, float shininess);
	// Destructor
	virtual ~Material();

	// Functions
	void UseMaterial(Shader* s);

private:
	unsigned int DiffuseMap;
	unsigned int SpecularMap;
	float Shininess;

	int LoadTexture(const GLchar* texturePath);
};


#endif // !MATERIAL_H
