#ifndef GRID_H
#define GRID_H
// Includes
#include "Mesh.h"
// Namespaces
using namespace glm;
// Class
class Grid : public Mesh {
public:
	// Constructor
	Grid(const int gridSize = 100.0f, const float gridHeight = 0.0f, const unsigned int materialNumber = 0);
	// Destructor
	virtual ~Grid();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw();

private:
	// Functions
	void GenerateGrid(int gridSize, float gridHeight);
};
#endif // !GRID_H