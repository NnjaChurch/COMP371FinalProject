#ifndef BUMPER_CAR_H
#define BUMPER_CAR_H
// Includes
#include "Camera.h"
#include "SpotLight.h"
#include "Particle.h"
#include "Cube.h"
#include "Cylinder.h"
#include "QuSphere.h"
// Class
class BumperCar {
public:
	// Constructor
	BumperCar(vec3 size = vec3(1.0f), vec3 position = vec3(0.0f), vec3 rotation = AXIS_Y, float angle = 0.0f, vec3 colour = COLOUR_WHT);
	// Destructor
	virtual ~BumperCar();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw();

	// Setters
	void ToggleAnimation();
	void ToggleLights();
	void SetCurrentCamera(Camera* camera);

	// Bounding Circle
	vec3 GetBoundingCenter() {
		return Parts[0]->GetPosition();
	}
	vec3 GetBoundingSize() {
		return Parts[0]->GetScale();
	}

	void CorrectCollisionX(float offset);
	void CorrectCollisionZ(float offset);

private:
	vec3 Position;
	vec3 Forward;
	vec3 Scale;
	vec3 Axis;
	float RotationAngle;
	vector<Mesh*> Parts;
	vector<SpotLight*> SpotLights;
	vector<Particle*> Particles;
	Camera* CurrentCamera;

	bool Animation;
	bool Lights;

	float totalTime;
	float spawnTime;
	float refreshRate;
	int MotionSteps;
	int CurrentStep;
};
#endif // !BUMPER_CAR_H