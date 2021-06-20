#include "..\headers\Cube.h"

Cube::Cube(const vec3 size, const vec3 position, const vec3 rotation, const float angle, const vec3 colour, unsigned int materialNumber) {
	// Update Values
	Position = position;
	Scale = size;
	Axis = rotation;
	RotationAngle = angle;
	MaterialNumber = materialNumber;

	Vertices = {
		// Left Face
		{ CUBE_LFT_TOP_FRT, -NORMAL_X, colour, vec2(1, 1) },	// 0
		{ CUBE_LFT_TOP_BCK, -NORMAL_X, colour, vec2(0, 1) },	// 1
		{ CUBE_LFT_BOT_BCK, -NORMAL_X, colour, vec2(0, 0) },	// 2
		{ CUBE_LFT_BOT_FRT, -NORMAL_X, colour, vec2(1, 0) },	// 3
		// Right Face
		{ CUBE_RGT_TOP_FRT, NORMAL_X, colour, vec2(0, 1) },		// 4
		{ CUBE_RGT_TOP_BCK, NORMAL_X, colour, vec2(1, 1) },		// 5
		{ CUBE_RGT_BOT_BCK, NORMAL_X, colour, vec2(1, 0) },		// 6
		{ CUBE_RGT_BOT_FRT, NORMAL_X, colour, vec2(0, 0) },		// 7
		// Top Face
		{ CUBE_LFT_TOP_FRT, NORMAL_Y, colour, vec2(0, 0) },		// 8
		{ CUBE_LFT_TOP_BCK, NORMAL_Y, colour, vec2(0, 1) },		// 9
		{ CUBE_RGT_TOP_FRT, NORMAL_Y, colour, vec2(1, 0) },		// 10
		{ CUBE_RGT_TOP_BCK, NORMAL_Y, colour, vec2(1, 1) },		// 11
		// Bottom Face
		{ CUBE_LFT_BOT_FRT, -NORMAL_Y, colour, vec2(0, 1) },	// 12
		{ CUBE_LFT_BOT_BCK, -NORMAL_Y, colour, vec2(0, 0) },	// 13
		{ CUBE_RGT_BOT_FRT, -NORMAL_Y, colour, vec2(1, 1) },	// 14
		{ CUBE_RGT_BOT_BCK, -NORMAL_Y, colour, vec2(1, 0) },	// 15
		// Front Face
		{ CUBE_LFT_TOP_FRT, -NORMAL_Z, colour, vec2(0, 1) },	// 16
		{ CUBE_LFT_BOT_FRT, -NORMAL_Z, colour, vec2(0, 0) },	// 17
		{ CUBE_RGT_TOP_FRT, -NORMAL_Z, colour, vec2(1, 1) },	// 18
		{ CUBE_RGT_BOT_FRT, -NORMAL_Z, colour, vec2(1, 0) },	// 19
		// Back Face
		{ CUBE_LFT_TOP_BCK, NORMAL_Z, colour, vec2(1, 1) },		// 20
		{ CUBE_LFT_BOT_BCK, NORMAL_Z, colour, vec2(1, 0) },		// 21
		{ CUBE_RGT_TOP_BCK, NORMAL_Z, colour, vec2(0, 1) },		// 22
		{ CUBE_RGT_BOT_BCK, NORMAL_Z, colour, vec2(0, 0) }		// 23
	};

	Indices = {
		// LEFT T1
		0, 1, 2,
		// LEFT T2
		0, 2, 3,
		// RIGHT T1
		4, 7, 6,
		// RIGHT T2
		4, 6, 5,
		// TOP T1
		8, 10, 9,
		// TOP T2
		10, 11, 9,
		// BOTTOM T1
		12, 13, 14,
		// BOTTOM T2
		13, 15, 14,
		// FRONT T1
		16, 17, 19,
		// FRONT T2
		16, 19, 18,
		// BACK T1
		20, 23, 21,
		// BACK T2
		20, 22, 23
	};

	// Create Cube VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create Cube VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// Create Cube EBO
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

Cube::~Cube() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Cube::Update(float dt) {
	Mesh::Update(dt);
}

void Cube::Draw() {
	Shader* s = RenderHandler::GetCurrentShader();
	// Bind VAO
	glBindVertexArray(VAO);

	// Set Texture
	RenderHandler::SetMaterial(MaterialNumber);

	// World Matrix
	s->SetWorldMatrix(GetWorldMatrix());

	// Opacity
	s->SetFloat("Opacity", 1.0f);

	// Draw
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	// Unbind VAO
	glBindVertexArray(0);
}
