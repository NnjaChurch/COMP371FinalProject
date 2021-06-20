#ifndef LIGHT_H
#define LIGHT_H
// Includes
#include "RenderHandler.h"
#include "Cube.h"
// Class
class Light {
public:
	// Constructor
	Light();
	// Destructor
	virtual ~Light();

	// Drawing Functions
	virtual void Update(float dt);
protected:
	// Counter
	// Attributes
	unsigned int Number;
	vec3 Position;

	// Lighting
	vec3 Colour;
	vec3 Ambient;
	vec3 AmbientColour;
	vec3 Diffuse;
	vec3 DiffuseColour;
	vec3 Specular;

	// Attenuation
	float Constant;
	float Linear;
	float Quadratic;

	// Flags
	bool Active;

	// Functions
	virtual void SetShaderUniforms() = 0;
};


#endif // !LIGHT_H