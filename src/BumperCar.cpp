#include "..\headers\BumperCar.h"

BumperCar::BumperCar(vec3 size, vec3 position, vec3 rotation, float angle, vec3 colour) {
	Position = position;
	Scale = size;
	Axis = rotation;
	RotationAngle = angle;
	float r = radians(RotationAngle);
	Forward = normalize(vec3(cosf(r), 0.0f, sinf(r)));

	// Time
	totalTime = 0.0f;
	refreshRate = 1.0f / 120.0f;

	// Add Parts
	Parts.push_back(new Cylinder(1.25f * size, vec3(0.0f), rotation, angle, colour, 0));
	Parts.push_back(new QuSphere(0.75f * size, vec3(0.45f, 0.30f, 0.0f), rotation, 90.0f, colour, 1));
	Parts.push_back(new QuSphere(1.0f * size, vec3(-0.15f, 0.30f, 0.0f), rotation, -90.0f, colour, 1));
	Parts.push_back(new Cube(vec3(0.1f, 0.5f, 0.80f) * size, vec3(0.1f, 0.5f, 0.65f), rotation, -75.0f, colour, 1));
	Parts.push_back(new Cube(vec3(0.1f, 0.5f, 0.80f) * size, vec3(0.1f, 0.5f, -0.65f), rotation, 75.0f, colour, 1));
	// Headlight
	Parts.push_back(new Cube(vec3(0.1f) * size, vec3(0.75f, 1.0f, 0.0f), rotation, 0.0f, colour, 1));
	// Taillight
	Parts.push_back(new Cube(vec3(0.1f) * size, vec3(-0.9f, 0.95f, 0.0f), rotation, 0.0f, colour, 1));
	// Exhaust Pipe
	Parts.push_back(new Cube(vec3(0.1f, 1.0f, 0.1f) * size, vec3(-0.9f, 0.95f, 0.25f), rotation, 0.0f, colour, 1));

	// Lights
	SpotLights.push_back(new SpotLight(vec3(0.75f, 1.0f, 0.0f), vec3(0.0f), vec3(1.0f), vec3(1.0f), 1.0f, 0.09f, 0.032f, COLOUR_WHT, Forward, cos(radians(12.5f)), cos(radians(15.0f))));
	SpotLights.push_back(new SpotLight(vec3(-0.9f, 0.95f, 0.0f), vec3(0.0f), vec3(1.0f), vec3(1.0f), 1.0f, 0.09f, 0.032f, COLOUR_RED, -Forward, cos(radians(12.5f)), cos(radians(15.0f))));

	// Place Car in World
	for (int i = 0; i < Parts.size(); i++) {
		vec3 cPos = Parts[i]->GetPosition();
		cPos.x += position.x;
		cPos.y += position.y;
		cPos.z += position.z;
		Parts[i]->SetPosition(cPos);
	}
	// Place Lights in the World
	SpotLights[0]->SetPosition(Parts[5]->GetPosition());
	SpotLights[0]->SetDirection(Forward);
	SpotLights[1]->SetPosition(Parts[6]->GetPosition());
	SpotLights[1]->SetDirection(-Forward);

	// Initalize Flags
	Animation = true;
	Lights = true;

	// Initialize Movement
	MotionSteps = 10 + rand() % 21;
	CurrentStep = 0;
}

BumperCar::~BumperCar() {
	for (Mesh* m : Parts) {
		m->~Mesh();
	}
}

void BumperCar::Update(float dt) {	
	totalTime += dt;
	spawnTime += dt;
	// Add Particles
	if (spawnTime > P_SPAWN_TIME) {
		vec3 exhaustPos = Parts[7]->GetPosition();
		exhaustPos.y += 0.5f;

		Particle* p = new Particle(exhaustPos, 0.0f, 1.0f, 3);
		// Velocity
		float angle = ((float) rand() / (float) RAND_MAX) * 360 ;
		vec4 randomSidewaysVelocity(0.5, 2, 0 ,0);
		randomSidewaysVelocity = rotate(mat4(1.0f), glm::radians(angle), vec3(0,1,0)) * randomSidewaysVelocity;
		p->SetVelocity(randomSidewaysVelocity);
		Particles.push_back(p);
		spawnTime = 0;
	}

	// Billboard Particles
	vec3 originalAxis = AXIS_Z;
	vec3 cameraLookAt = -CurrentCamera->GetLookAt();
	// Project on to XZ
	cameraLookAt.y = 0.0f;
	cameraLookAt.x *= -1.0f;
	cameraLookAt = normalize(cameraLookAt);

	vec3 billboardAxis = AXIS_Y;

	float billboardRotation = acos(-1.0f * dot(originalAxis, cameraLookAt)) * 360 / (2 * pi<float>());

	if (cameraLookAt.x > 0) {
		billboardRotation = 360 - billboardRotation;
	}

	// Update Animation
	if (Animation && (totalTime > refreshRate)) {
		if (CurrentStep != MotionSteps) {
			vec3 dP = vec3(0.0f);
			dP.x += Forward.x * 0.1f;
			dP.y += Forward.y * 0.1f;
			dP.z += Forward.z * 0.1f;
			// Update Parts Position
			for (int i = 0; i < Parts.size(); i++) {
				vec3 cPos = Parts[i]->GetPosition();
				cPos.x += dP.x;
				cPos.y += dP.y;
				cPos.z += dP.z;
				Parts[i]->SetPosition(cPos);
			}
			for (int i = 0; i < SpotLights.size(); i++) {
				vec3 lPos = SpotLights[i]->GetPosition();
				lPos.x += dP.x;
				lPos.y += dP.y;
				lPos.z += dP.z;
				SpotLights[i]->SetPosition(lPos);
			}
			CurrentStep++;
		}
		else {
			// Rotate Randomly Left or Right
			int rDir = rand() % 2;
			float dR = 0.0f;
			if (rDir == 0) {
				dR -= 30.0f;
				RotationAngle += dR;
			}
			if (rDir == 1) {
				dR += 30.0f;
				RotationAngle += dR;
			}
			float r = radians(RotationAngle);
			Forward = vec3(cosf(r), 0.0f, sinf(r));
			// Update Part Rotation
			Parts[0]->SetRotation(dR);

			// Update Light Rotation
			SpotLights[0]->SetDirection(Forward);
			SpotLights[1]->SetDirection(-Forward);

			// Generate New Motion
			MotionSteps = 10 + rand() % 21;
			CurrentStep = 0;
		}
		totalTime = 0.0f;
	}

	// Update Base
	Parts[0]->SetRelativeMatrix(mat4(1.0f));
	Parts[0]->Update(dt);
	mat4 relativeMatrix = Parts[0]->GetRelativeMatrix();

	for (int i = 1; i < Parts.size(); i++) {
		Parts[i]->SetRelativeMatrix(relativeMatrix);
		Parts[i]->Update(dt);
	}
	// Update Lights
	for (SpotLight* s : SpotLights) {
		s->Update(dt);
	}
	// Update Particles
	for(int i = 0; i < Particles.size(); i++) {
		Particles[i]->SetAxis(billboardAxis);
		Particles[i]->ChangeRotationAngle(billboardRotation);
		Particles[i]->Update(dt);
		if (Particles[i]->isExpired()) {
			Particles[i]->~Particle();
			Particles.erase(Particles.begin() + i);
		}
	}
}
void BumperCar::Draw() {
	for (Mesh* m : Parts) {
		m->Draw();
	}
	glDisable(GL_DEPTH_TEST);
	for (Particle* p : Particles) {
		p->Draw();
	}
	glEnable(GL_DEPTH_TEST);
}

void BumperCar::ToggleAnimation() {
	Animation = !Animation;
}

void BumperCar::ToggleLights() {
	Lights = !Lights;
	for (SpotLight* s : SpotLights) {
		s->SetActive(Lights);
	}
}

void BumperCar::SetCurrentCamera(Camera* camera) {
	CurrentCamera = camera;
}

void BumperCar::CorrectCollisionX(float offset) {
	for (Mesh* m : Parts) {
		vec3 cPos = m->GetPosition();
		cPos.x += offset;
		m->SetPosition(cPos);
	}
	for (SpotLight* s : SpotLights) {
		vec3 lPos = s->GetPosition();
		lPos.x += offset;
		s->SetPosition(lPos);
	}
}

void BumperCar::CorrectCollisionZ(float offset) {
	for (Mesh* m : Parts) {
		vec3 cPos = m->GetPosition();
		cPos.z += offset;
		m->SetPosition(cPos);
	}
	for (SpotLight* s : SpotLights) {
		vec3 lPos = s->GetPosition();
		lPos.z += offset;
		s->SetPosition(lPos);
	}
}
