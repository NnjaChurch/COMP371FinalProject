#include "..\headers\QuSphere.h"

QuSphere::QuSphere(const vec3 size, const vec3 position, const vec3 rotation, const float angle, const vec3 colour, const unsigned int materialNumber) {
	Position = position;
	Scale = size;
	Axis = rotation;
	RotationAngle = angle;
	MaterialNumber = materialNumber;
	GenerateQuSphere(colour, 36, 1.0f);

	// Create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// Create EBO
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

QuSphere::~QuSphere() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void QuSphere::Update(float dt) {
	Mesh::Update(dt);
}

void QuSphere::Draw() {
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

void QuSphere::GenerateQuSphere(vec3 colour, int numSegments, float radius) {
	int numVertices = 0;
	int numIndices = 0;

	int angleIncrement = 360 / numSegments;

	// Origin
	Vertex o = {
		vec3(0.0f),
		normalize(vec3(0.0f, -1.0f, -1.0f)),
		colour,
		vec2(0.5f, 0.5f)		
	};
	Vertices.push_back(o);
	numVertices++;

	// Vertices
	for (int i = 0; i <= 90; i += angleIncrement) {
		float vRad = radians((float)i);
		float xz = cosf(vRad) * radius;
		float y = sinf(vRad) * radius;
		for (int j = 0; j <= 180; j += angleIncrement) {
			float hRad = radians((float)j);
			float x = xz * cosf(hRad);
			float z = xz * sinf(hRad);

			float s = ((float)i / angleIncrement) / 9;
			float t = ((float)j / angleIncrement) / 18;

			Vertex v = {
				vec3(x, y, z),
				normalize(vec3(x, y, z)),
				colour,
				vec2(s, t)
			};
			Vertices.push_back(v);
			numVertices++;
		}
	}

	// Indices
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 18; j++) {

			int o = 0;
			int p1 = (i * 19) + j + 1;
			int p2 = ((i + 1) * 19) + j + 1;
			int p3 = (i * 19) + j + 2;
			int p4 = ((i + 1) * 19) + j + 2;

			// Horizontal Side
			if (i == 0) {
				Indices.push_back(o);
				Indices.push_back(p1);
				Indices.push_back(p3);
				numIndices += 3;
			}
			// Vertical Side
			if (j == 0) {
				Indices.push_back(o);
				Indices.push_back(p2);
				Indices.push_back(p1);
				numIndices += 3;
			}
			if (j == 17) {
				Indices.push_back(o);
				Indices.push_back(p3);
				Indices.push_back(p4);
				numIndices += 3;
			}
			
			
			// Surface T1
			Indices.push_back(p1);
			Indices.push_back(p2);
			Indices.push_back(p3);
			numIndices += 3;
			// Surface T2
			Indices.push_back(p2);
			Indices.push_back(p4);
			Indices.push_back(p3);
			numIndices += 3;
			
		}
	}


}
