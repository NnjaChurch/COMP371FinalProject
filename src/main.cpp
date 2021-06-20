// Includes
#include "..\headers\RenderHandler.h"
#include "..\headers\World.h"
#include "..\headers\InputHandler.h"

// Main Method
int main(int argc, char* argv[]) {
	// Initalize
	EventHandler::Initialize();
	RenderHandler::Initialize();

	World* RenderWorld = new World();

	while (EventHandler::GetExitRequest() == false) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// Update
		EventHandler::Update();
		InputHandler::Update(RenderWorld);
		
		float dt = EventHandler::GetFrameTime();
		// Update World
		RenderWorld->Update(dt);

		// Draw
		RenderWorld->Draw();
	}
	RenderHandler::Shutdown();
	EventHandler::Shutdown();
}