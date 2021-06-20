#include "..\headers\Particle.h"

Particle::Particle(vec3 position, float age, float opacity, unsigned int material) {
	Age = age;
	Opacity = opacity;
	Position = position;
	Scale = P_SCALE_INITIAL;
	Axis = AXIS_Y;
	RotationAngle = 0.0f;
	WorldMatrix = mat4(1.0f);
	RelativeMatrix = mat4(1.0f);
	MaterialNumber = material;

	Vertices = {
		{ vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f), COLOUR_WHT, vec2(0, 0) },
		{ vec3(0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f), COLOUR_WHT, vec2(1, 0) },
		{ vec3(-0.5f, 0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f), COLOUR_WHT, vec2(0, 1) },
		{ vec3(0.5f, 0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f), COLOUR_WHT, vec2(1, 1) }
	};

	Indices = {
		0, 1, 2,
		1, 3, 2
	};

	// Create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));
	// Colour
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(vec3)));
	// Texture
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(vec3)));

	// Unbind VAO
	glBindVertexArray(0);

	// Initial World Matrix
	mat4 t = translate(mat4(1.0f), Position);
	mat4 s = scale(mat4(1.0f), Scale);
	mat4 r = rotate(mat4(1.0f), radians(RotationAngle), AXIS_Y);
	WorldMatrix = t * r * s;
}

Particle::~Particle() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Particle::Update(float dt) {
	Age += dt;

	float interpolationParam = Age / P_LIFETIME;

	float scalingParam = Linear(interpolationParam);
	float opacityParam = Linear(interpolationParam);

	Opacity = P_OPACITY_INITIAL * (1 - opacityParam) + P_OPACITY_FINAL * opacityParam;
	Scale = P_SCALE_INITIAL * (1 - scalingParam) + P_SCALE_FINAL * scalingParam;

	Position += Velocity * dt;

	Mesh::Update(dt);
}

void Particle::Draw() {
	Shader* s = RenderHandler::GetCurrentShader();
	// Bind VAO
	glBindVertexArray(VAO);

	// Set Texture
	RenderHandler::SetMaterial(MaterialNumber);

	// World Matrix
	s->SetWorldMatrix(GetWorldMatrix());

	// Opacity
	s->SetFloat("Opacity", Opacity);

	// Draw
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// Unbind VAO
	glBindVertexArray(0);
}

bool Particle::isExpired() const
{
	return (Age > P_LIFETIME);
}

void Particle::SetVelocity(vec3 velocity) {
	Velocity = velocity;
}

float Particle::Linear(float t) {
	return t;
}

float Particle::Quadratic(float t) {
	return t * t;
}

float Particle::Root(float t) {
	return sqrt(t);
}

float Particle::Smooth(float t) {
	float theta = pi<float>() * (1 + t);
	return (cos(theta) + 1) / 2;
}
