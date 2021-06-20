#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
// Includes
#include "Light.h"
// Class
class SpotLight : public Light {
public:
	// Constructor
	SpotLight(
		vec3 position = vec3(0.0f),
		vec3 ambient = vec3(0.0f),
		vec3 diffuse = vec3(0.0f),
		vec3 specular = vec3(0.0f),
		float constant = 0.0f,
		float linear = 0.0f,
		float quadratic = 0.0f,
		vec3 colour = COLOUR_WHT,
		vec3 direction = vec3(0.0f),
		float cutOff = 0.0f,
		float outerCutOff = 0.0f
	);
	// Destructor
	virtual ~SpotLight();

	// Drawing Functions
	virtual void Update(float dt);
	// Setter
	void SetPosition(vec3 position);
	void SetDirection(vec3 direction);
	void SetActive(bool active);

	// Getter
	vec3 GetPosition() {
		return Position;
	}
private:
	void SetShaderUniforms();
	static unsigned int SpotLightCount;
	vec3 Direction;
	float CutOff;
	float OuterCutOff;
};
#endif // !SPOT_LIGHT_H
