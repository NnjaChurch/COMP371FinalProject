#include "..\headers\World.h"

World* World::WorldInstance;
vector<BumperCar*> Cars;
vector<Camera*> Cameras;
vector<Grid*> Grids;
vector<Cube*> Walls;
vector<Light*> Lights;

World::World() {
	// Initialize Values
	WorldInstance = this;
	
	// Grid
	Grids.push_back(new Grid(100, 0.0f, 2));

	// Walls
	Walls.push_back(new Cube(vec3(50.0f, 2.0f, 0.75f), vec3(0.0f, 1.0f, -25.0f), AXIS_Y, 0.0f, COLOUR_YLW, 1));
	Walls.push_back(new Cube(vec3(50.0f, 2.0f, 0.75f), vec3(0.0f, 1.0f, 25.0f), AXIS_Y, 0.0f, COLOUR_YLW, 1));
	Walls.push_back(new Cube(vec3(0.75f, 2.0f, 50.0f), vec3(25.0f, 1.0f, 0.0f), AXIS_Y, 0.0f, COLOUR_YLW, 1));
	Walls.push_back(new Cube(vec3(0.75f, 2.0f, 50.0f), vec3(-25.0f, 1.0f, 0.0f), AXIS_Y, 0.0f, COLOUR_YLW, 1));

	// Cars
	Cars.push_back(new BumperCar(vec3(1.0f), vec3(-15.0f, 0.0f, -15.0f), AXIS_Y, 0.0f, COLOUR_PRP));
	Cars.push_back(new BumperCar(vec3(1.0f), vec3(-15.0f, 0.0f, -5.0f), AXIS_Y, 0.0f, COLOUR_RED));
	Cars.push_back(new BumperCar(vec3(1.0f), vec3(-15.0f, 0.0f, 0.0f), AXIS_Y, 0.0f, COLOUR_BLU));
	Cars.push_back(new BumperCar(vec3(1.0f), vec3(-15.0f, 0.0f, 5.0f), AXIS_Y, 0.0f, COLOUR_GRN));
	Cars.push_back(new BumperCar(vec3(1.0f), vec3(-15.0f, 0.0f, 10.0f), AXIS_Y, 0.0f, COLOUR_YLW));

	// Lights
	Lights.push_back(new PointLight(vec3(0.0f, 10.0f, 0.0f), vec3(0.2f), vec3(0.5f), vec3(1.0f), 1.0f, 0.014f, 0.0007f, COLOUR_WHT));
	Lights.push_back(new PointLight(vec3(15.0f, 10.0f, 15.0f), vec3(0.2f), vec3(0.5f), vec3(1.0f), 1.0f, 0.022f, 0.0019f, COLOUR_BLU));
	Lights.push_back(new PointLight(vec3(15.0f, 10.0f, -15.0f), vec3(0.2f), vec3(0.5f), vec3(1.0f), 1.0f, 0.022f, 0.0019f, COLOUR_RED));
	Lights.push_back(new PointLight(vec3(-15.0f, 10.0f, 15.0f), vec3(0.2f), vec3(0.5f), vec3(1.0f), 1.0f, 0.022f, 0.0019f, COLOUR_RED));
	Lights.push_back(new PointLight(vec3(-15.0f, 10.0f, -15.0f), vec3(0.2f), vec3(0.5f), vec3(1.0f), 1.0f, 0.022f, 0.0019f, COLOUR_BLU));

	// Camera
	Cameras.push_back(new TPCamera(vec3(0.0f, 25.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), AXIS_Y));
	vec3 CarPos = Cars[0]->GetBoundingCenter();
	Cameras.push_back(new FPCamera(vec3(CarPos.x, 1.5f, CarPos.z)));
	CurrentCamera = 0;

	// Pass Cameras to each BumperCar
	for (BumperCar* b : Cars) {
		b->SetCurrentCamera(Cameras[CurrentCamera]);
	}

	// Shader Setup
	Camera* c = Cameras[CurrentCamera];
	Shader* s = RenderHandler::GetCurrentShader();
	s->SetViewMatrix(c->GetViewMatrix());
	s->SetProjectionMatrix(c->GetProjectionMatrix());
}

World::~World() {
	// Delete Grid
	for (Grid* g : Grids) {
		g->~Grid();
	}
	// Delete Walls
	for (Cube* c : Walls) {
		c->~Cube();
	}
	// Delete Parts
	for (BumperCar* b : Cars) {
		b->~BumperCar();
	}
	// Delete Cameras
	for (Camera* c : Cameras) {
		c->~Camera();
	}
	// Delete Lights
	for (Light* l : Lights) {
		l->~Light();
	}
}

void World::Update(float dt) {
	// Update Grid
	for (Grid* g : Grids) {
		g->Update(dt);
	}
	// Update Walls
	for (Cube* c : Walls) {
		c->Update(dt);
	}
	// Update Parts
	for (BumperCar* b : Cars) {
		b->Update(dt);
	}
	if (CurrentCamera == 1) {
		vec3 CarPos = Cars[0]->GetBoundingCenter();
		Cameras[CurrentCamera]->SetPosition(vec3(CarPos.x, 1.5f, CarPos.z));
	}
	// Update Cameras
	Cameras[CurrentCamera]->Update(dt);
	// Update Camera Position in Shader
	vec3 CameraPos = Cameras[CurrentCamera]->GetPosition();
	RenderHandler::GetCurrentShader()->SetVec3("viewPos", CameraPos);
	// Update Lights
	for (Light* l : Lights) {
		l->Update(dt);
	}
	// Check for Collisions
	CalculateCollisions();
}

void World::Draw() {
	RenderHandler::FrameStart();

	// Matrices
	Shader* s = RenderHandler::GetCurrentShader();
	Camera* c = Cameras[CurrentCamera];
	s->SetViewMatrix(c->GetViewMatrix());
	s->SetProjectionMatrix(c->GetProjectionMatrix());

	// Draw Grids
	for (Grid* g : Grids) {
		g->Draw();
	}
	// Draw Walls
	for (Cube* c : Walls) {
		c->Draw();
	}
	// Draw Parts
	for (BumperCar* b : Cars) {
		b->Draw();
	}
	RenderHandler::FrameEnd();
}

void World::ToggleAnimation() {
	for (BumperCar* b : Cars) {
		b->ToggleAnimation();
	}
}

void World::ToggleLights() {
	for (BumperCar* b : Cars) {
		b->ToggleLights();
	}
}

void World::ToggleCamera() {
	if (CurrentCamera == 0) {
		CurrentCamera = 1;
	}
	else if (CurrentCamera == 1) {
		CurrentCamera = 0;
	}
	for (BumperCar* b : Cars) {
		b->SetCurrentCamera(Cameras[CurrentCamera]);
	}
}

void World::CalculateCollisions() {
	// Check for Wall Collisions
	for (int i = 0; i < Cars.size(); i++) {
		for (int j = 0; j < Walls.size(); j++) {
			// Get Object Information
			vec3 bPos = Cars[i]->GetBoundingCenter();
			vec3 bSize = Cars[i]->GetBoundingSize();
			vec3 wPos = Walls[j]->GetPosition();
			vec3 wSize = Walls[j]->GetScale();

			// Calculation Values
			vec2 bCenter(bPos.x, bPos.z);
			float bRad = bSize.x;
			vec2 wCenter(wPos.x, wPos.z);
			vec2 wRad(wSize.x / 2, wSize.z / 2);

			// Distance Between Car & Wall
			vec2 distance = bCenter - wCenter;

			// Closest Point on Wall
			vec2 clamped = clamp(distance, -wRad, wRad);
			vec2 closest = wCenter + clamped;

			distance = closest - bCenter;
			//cout << "Distance between Car: " << i << " and Wall: " << j << " | " << distance.x << ", " << distance.y << endl;

			if (length(distance) < bRad) {
				//cout << "COLLISION::CAR_" << i << "::WALL_" << j << endl;
				float offset;
				if (distance.x != 0) {
					if (distance.x < 0) {
						offset = distance.x + bRad;
						//cout << "COLLISION::OFFSET_" << offset << endl;
						Cars[i]->CorrectCollisionX(offset);
					}
					else if (distance.x > 0) {
						offset = distance.x - bRad;
						//cout << "COLLISION::OFFSET_" << offset << endl;
						Cars[i]->CorrectCollisionX(offset);
					}
				}
				else if (distance.y != 0) {
					if (distance.y < 0) {
						offset = distance.y + bRad;
						//cout << "COLLISION::OFFSET_" << offset << endl;
						Cars[i]->CorrectCollisionZ(offset);
					}
					else if (distance.y > 0) {
						offset = distance.y - bRad;
						//cout << "COLLISION::OFFSET_" << offset << endl;
						Cars[i]->CorrectCollisionZ(offset);
					}
				}
			}
		}
	}

	// Check for Car Collisions
	for (int i = 0; i < Cars.size(); i++) {
		for (int j = 0; j < Cars.size(); j++) {
			if (i != j) {
				// Get Car BoundingValues
				vec3 c1Pos = Cars[i]->GetBoundingCenter();
				vec3 c2Pos = Cars[j]->GetBoundingCenter();
				vec3 c1Size = Cars[i]->GetBoundingSize();
				vec3 c2Size = Cars[j]->GetBoundingSize();

				// Calculation Values
				vec2 c1Center(c1Pos.x, c1Pos.z);
				vec2 c2Center(c2Pos.x, c2Pos.z);
				float c1Rad = c1Size.x;
				float c2Rad = c2Size.x;

				// Distance Between Two Car Centers
				vec2 distance = c1Center - c2Center;
				//cout << "DISTANCE::CAR_" << i << "::CAR_" << j << " | " << distance.x << ", " << distance.y << endl;

				if (length(distance) < 2 * c1Rad) {
					float offset;
					//cout << "COLLISION::CAR_" << i << "::CAR_" << j << endl;
					if (distance.x != 0) {
						if (distance.x < 0) {
							offset = distance.x + (2 * c1Rad);
							//cout << "COLLISION::OFFSET_" << offset << endl;
							Cars[i]->CorrectCollisionX(offset);
						}
						else if (distance.x > 0) {
							offset = distance.x - (2 * c1Rad);
							//cout << "COLLISION::OFFSET_" << offset << endl;
							Cars[j]->CorrectCollisionX(offset);
						}
					}
					else if (distance.y != 0) {
						if (distance.y < 0) {
							offset = distance.y + (2 * c1Rad);
							//cout << "COLLISION::OFFSET_" << offset << endl;
							Cars[i]->CorrectCollisionZ(offset);
						}
						else if (distance.y > 0) {
							offset = distance.y - (2 * c1Rad);
							//cout << "COLLISION::OFFSET_" << offset << endl;
							Cars[j]->CorrectCollisionZ(offset);
						}

					}
				}
			}
		}
	}
}
