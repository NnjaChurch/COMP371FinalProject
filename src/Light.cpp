#include "..\headers\Light.h"

Light::Light() : Position(vec3(0.0f)), Ambient(vec3(0.0f)), Diffuse(vec3(0.0f)), Specular(vec3(0.0f)), Constant(0.0f), Linear(0.0f), Quadratic(0.0f) {
}

Light::~Light() {
}

void Light::Update(float dt) {
}