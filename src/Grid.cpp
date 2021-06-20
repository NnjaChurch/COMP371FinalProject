#include "..\headers\Grid.h"

Grid::Grid(const int gridSize, const float gridHeight, const unsigned int materialNumber) {
	MaterialNumber = materialNumber;
	GenerateGrid(gridSize, gridHeight);

	// Create VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Initial World Matrix
	mat4 t = translate(mat4(1.0f), Position);
	mat4 s = scale(mat4(1.0f), Scale);
	mat4 r = rotate(mat4(1.0f), radians(RotationAngle), AXIS_Y);
	WorldMatrix = t * r * s;
}

Grid::~Grid() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Grid::Update(float dt) {
}

void Grid::Draw() {
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

void Grid::GenerateGrid(int gridSize, float gridHeight) {
	float halfGridSize = 0.5f * gridSize;
	// Vertices
	for (float i = -halfGridSize; i < halfGridSize + 1.0f; i += 1.0f) {
		for (float j = -halfGridSize; j < halfGridSize + 1.0f; j += 1.0f) {
			float x = i;
			float z = j;
			float t1 = (int)i % 2;
			float t2 = (int)j % 2;
			// Add Vertex
			Vertex v = {
				vec3(x, gridHeight, z),
				NORMAL_Y,
				COLOUR_WHT,
				vec2(t1, t2)
			};
			Vertices.push_back(v);
		}
	}
	// Indices (Triangles)
	for (int i = 0; i < gridSize - 1; i++) {
		for (int j = 0; j < gridSize - 1; j++) {
			int row1 = i * (gridSize + 1);
			int row2 = (i + 1) * (gridSize + 1);

			int p1 = row1 + j;
			int p2 = row1 + j + 1;
			int p3 = row2 + j;
			int p4 = row2 + j + 1;
			
			// T1
			Indices.push_back(p1);
			Indices.push_back(p2);
			Indices.push_back(p3);
			// T2
			Indices.push_back(p2);
			Indices.push_back(p4);
			Indices.push_back(p3);		
		}
	}

}
