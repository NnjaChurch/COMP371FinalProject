#ifndef PARTICLE_H
#define PARTICLE_H
// Includes
#include "Mesh.h"
// Class
class Particle : public Mesh {
public:
	// Constructor
	Particle(const vec3 position = vec3(0.0f), float age = 0.0f, float opacity = 1.0f, unsigned int material = 0);
	// Destructor
	virtual ~Particle();

	// Drawing Functions
	virtual void Update(float dt);
	virtual void Draw();

	// Lifetime Check
	bool isExpired() const;

	// Setter
	void SetVelocity(vec3 velocity);

private:
	float Age;
	float Opacity;
	vec3 Velocity;

	float Linear(float t);
	float Quadratic(float t);
	float Root(float t);
	float Smooth(float t);
};

#endif // !PARTICLE_H