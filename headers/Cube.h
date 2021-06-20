#ifndef CUBE_H
#define CUBE_H
// Includes
#include "Mesh.h"

// Class
class Cube : public Mesh {
public:
	// Constructor
	Cube(
		const vec3 size = vec3(1.0f),
		const vec3 position = vec3(0.0f),
		const vec3 rotation = AXIS_Y,
		const float angle = 0.0f,
		const vec3 colour = COLOUR_WHT,
		const unsigned int materialNumber = 0
	);
	// Destructor
	virtual ~Cube();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw();
};
#endif // !CUBE_H