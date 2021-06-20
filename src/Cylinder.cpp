#include "..\headers\Cylinder.h"

Cylinder::Cylinder(const vec3 size, const vec3 position, const vec3 rotation, const float angle, const vec3 colour, const unsigned int materialNumber) {
	Position = position;
	Scale = size;
	Axis = rotation;
	RotationAngle = angle;
	MaterialNumber = materialNumber;
	GenerateCylinder(colour, 36, 1.0f, 0.25f);

	// Setup VAO
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
	// Texture Coords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(vec3)));

	// Unbind VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Initial World Matrix
	mat4 t = translate(mat4(1.0f), Position);
	mat4 s = scale(mat4(1.0f), Scale);
	mat4 r = rotate(mat4(1.0f), radians(RotationAngle), AXIS_Y);
	WorldMatrix = t * r * s;
}

Cylinder::~Cylinder() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Cylinder::Update(float dt) {
	Mesh::Update(dt);
}

void Cylinder::Draw() {
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

void Cylinder::GenerateCylinder(vec3 colour, int numSegments, float radius, float height) {
	int numVertices = 0;
	int numIndices = 0;
	int angleIncrement = 360 / numSegments;

	// Origins
	Vertex bOrigin = {
		vec3(0.0f),
		-AXIS_Y,
		colour,
		vec2(0.5f, 0.5f)
	};
	Vertex tOrigin = {
		vec3(0.0f, height, 0.0f),
		AXIS_Y,
		colour,
		vec2(0.5f, 0.5f)
	};

	Vertices.push_back(bOrigin);
	Vertices.push_back(tOrigin);
	numVertices += 2;

	// Vertices
	for (int i = 0; i < 360; i += angleIncrement) {
		float angleRadians = radians((float)i);
		float x = cosf(angleRadians) * radius;
		float z = sinf(angleRadians) * radius;
		vec2 texCoord = normalize(vec2(x, z));
		vec3 bPoint = vec3(x, 0.0f, z);
		vec3 tPoint = vec3(x, height, z);
		Vertex bVertex = {
			bPoint,
			bPoint,
			colour,
			texCoord
		};
		Vertex tVertex = {
			tPoint,
			tPoint,
			colour,
			texCoord
		};
		Vertices.push_back(bVertex);
		Vertices.push_back(tVertex);
		numVertices += 2;
	}

	// Indices
	int halfVertices = numVertices / 2;
	for (int i = 1; i < halfVertices; i++) {
		// Bottom Circle
		int bO = 0;
		int b1 = 2 * i;
		int b2 = (b1 + 2) % numVertices;
		if (b2 == bO) {
			b2 += 2;
		}

		// Clock-wise PushBack to face down
		Indices.push_back(bO);
		Indices.push_back(b1);
		Indices.push_back(b2);
		numIndices += 3;

		// Top Circle
		int tO = 1;
		int t1 = (2 * i) + 1;
		int t2 = (t1 + 2) % numVertices;
		if (t2 == tO) {
			t2 += 2;
		}

		// Counter Clock-wise PushBack to face up
		Indices.push_back(tO);
		Indices.push_back(t2);
		Indices.push_back(t1);
		numIndices += 3;

		// Segments

		// Segment T1
		Indices.push_back(b2);
		Indices.push_back(b1);
		Indices.push_back(t2);
		numIndices += 3;

		// Segment T2
		Indices.push_back(t1);
		Indices.push_back(t2);
		Indices.push_back(b1);
		numIndices += 3;
	}
}
