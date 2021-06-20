#include "..\headers\SpotLight.h"

unsigned int SpotLight::SpotLightCount = 0;

SpotLight::SpotLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic, vec3 colour, vec3 direction, float cutOff, float outerCutOff) {

	Position = position;
	Direction = direction;
	Colour = colour;
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
	Constant = constant;
	Linear = linear;
	Quadratic = quadratic;
	CutOff = cutOff;
	OuterCutOff = outerCutOff;
	Number = SpotLightCount;

	Active = true;

	// Update SpotLight Counter
	SpotLightCount++;
}

SpotLight::~SpotLight() {
}

void SpotLight::Update(float dt) {
	// Update Light Values	
	DiffuseColour = Colour * Diffuse;
	AmbientColour = DiffuseColour * Ambient;

	SetShaderUniforms();
}

void SpotLight::SetPosition(vec3 position) {
	Position = position;
}

void SpotLight::SetDirection(vec3 direction) {
	Direction = direction;
}

void SpotLight::SetActive(bool active) {
	Active = active;
}

void SpotLight::SetShaderUniforms() {
	Shader* s = RenderHandler::GetCurrentShader();
	string n = to_string(Number);

	s->SetVec3(("SpotLights[" + n + "].position").c_str(), Position);
	s->SetVec3(("SpotLights[" + n + "].direction").c_str(), Direction);
	s->SetFloat(("SpotLights[" + n + "].cutOff").c_str(), CutOff);
	s->SetFloat(("SpotLights[" + n + "].outerCutOff").c_str(), OuterCutOff);
	s->SetVec3(("SpotLights[" + n + "].ambient").c_str(), AmbientColour);
	s->SetVec3(("SpotLights[" + n + "].diffuse").c_str(), DiffuseColour);
	s->SetVec3(("SpotLights[" + n + "].specular").c_str(), Specular);
	s->SetFloat(("SpotLights[" + n + "].constant").c_str(), Constant);
	s->SetFloat(("SpotLights[" + n + "].linear").c_str(), Linear);
	s->SetFloat(("SpotLights[" + n + "].quadratic").c_str(), Quadratic);
	s->SetBool(("SpotLights[" + n + "].isActive").c_str(), Active);
}
