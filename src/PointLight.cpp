#include "PointLight.h"
#include "..\headers\PointLight.h"

unsigned int PointLight::PointLightCount = 0;

PointLight::PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic, vec3 colour) {
	Position = position;
	Colour = colour;
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
	Constant = constant;
	Linear = linear;
	Quadratic = quadratic;
	Number = PointLightCount;

	Active = true;

	// Update PointLight Counter
	PointLightCount++;
}

PointLight::~PointLight() {
}

void PointLight::Update(float dt) {
	// Update Light Values	
	DiffuseColour = Colour * Diffuse;
	AmbientColour = DiffuseColour * Ambient;

	SetShaderUniforms();
}

void PointLight::SetActive(bool active) {
	Active = active;
}

void PointLight::SetShaderUniforms() {
	Shader* s = RenderHandler::GetCurrentShader();
	string n = to_string(Number);

	s->SetVec3(("PointLights[" + n + "].position").c_str(), Position);
	s->SetVec3(("PointLights[" + n + "].ambient").c_str(), AmbientColour);
	s->SetVec3(("PointLights[" + n + "].diffuse").c_str(), DiffuseColour);
	s->SetVec3(("PointLights[" + n + "].specular").c_str(), Specular);
	s->SetFloat(("PointLights[" + n + "].constant").c_str(), Constant);
	s->SetFloat(("PointLights[" + n + "].linear").c_str(), Linear);
	s->SetFloat(("PointLights[" + n + "].quadratic").c_str(), Quadratic);
	s->SetBool(("PointLights[" + n + "].isActive").c_str(), Active);
}
