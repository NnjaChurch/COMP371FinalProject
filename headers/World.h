#ifndef WORLD_H
#define WORLD_H
// Includes
#include "EventHandler.h"
#include "RenderHandler.h"
#include "PointLight.h"
#include "TPCamera.h"
#include "FPCamera.h"
#include "BumperCar.h"
#include "Grid.h"
// Class
class World {
public:
	// Constructor
	World();
	// Destructor
	~World();

	// Drawing Functions
	void Update(float dt);
	void Draw();

	// Getters
	static World* GetWorldInstance(){
		return WorldInstance;
	}
	Camera* GetCurrentCamera() {
		return Cameras[CurrentCamera];
	}

	// Setters
	void ToggleAnimation();
	void ToggleLights();
	void ToggleCamera();

private:
	static World* WorldInstance;
	vector<BumperCar*> Cars;
	vector<Camera*> Cameras;
	vector<Grid*> Grids;
	vector<Cube*> Walls;
	vector<Light*> Lights;

	unsigned int CurrentCamera;

	void CalculateCollisions();
};



#endif // !WORLD_H