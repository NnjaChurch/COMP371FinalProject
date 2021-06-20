#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
// Includes
#include "Light.h"

// Class
class PointLight : public Light {
public:
	// Constructor
	PointLight(
		vec3 position = vec3(0.0f),
		vec3 ambient = vec3(0.0f),
		vec3 diffuse = vec3(0.0f),
		vec3 specular = vec3(0.0f),
		float constant = 0.0f,
		float linear = 0.0f,
		float quadratic = 0.0f,
		vec3 colour = COLOUR_WHT
	);
	// Destructor
	virtual ~PointLight();

	// Drawing Functions
	virtual void Update(float dt);

	// Setters
	void SetActive(bool active);
private:

	void SetShaderUniforms();
	static unsigned int PointLightCount;
};

#endif // !POINT_LIGHT_H
