#ifndef CYLINDER_H
#define CYLINDER_H
// Includes
#include "Mesh.h"
// Class
class Cylinder : public Mesh {
public:
	// Constructor
	Cylinder(
		const vec3 size = vec3(1.0f),
		const vec3 position = vec3(0.0f),
		const vec3 rotation = AXIS_Y,
		const float angle = 0.0f,
		const vec3 colour = COLOUR_WHT,
		const unsigned int materialNumber = 0
	);
	// Destructor
	virtual ~Cylinder();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw();

private:
	// Functions
	void GenerateCylinder(vec3 colour, int numSegments, float radius, float height);
};
#endif // !CYLINDER_H