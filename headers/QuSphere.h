#ifndef QU_SPHERE_H
#define QU_SPHERE_H
// Includes
#include "Mesh.h"
// Class
class QuSphere : public Mesh {
public:
	// Constructor
	QuSphere(
		const vec3 size = vec3(1.0f),
		const vec3 position = vec3(0.0f),
		const vec3 rotation = AXIS_Y,
		const float angle = 0.0f,
		const vec3 colour = COLOUR_WHT,
		const unsigned int materialNumber = 0
	);
	// Destructor
	virtual ~QuSphere();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw();

private:
	void GenerateQuSphere(vec3 colour, int numSegments, float radius);
};


#endif // !QU_SPHERE_H
