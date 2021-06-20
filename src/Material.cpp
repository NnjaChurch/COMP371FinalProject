#include "..\headers\Material.h"

Material::Material(const GLchar* diffusePath, const GLchar* specularPath, float shininess) {
	DiffuseMap = LoadTexture(diffusePath);
	SpecularMap = LoadTexture(specularPath);
	Shininess = shininess;
}

Material::~Material() {

}

void Material::UseMaterial(Shader* s) {
	s->SetInt("material.diffuse", 0);
	s->SetInt("material.specular", 1);
	s->SetFloat("material.shininess", Shininess);

	// Bind Diffuse Map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DiffuseMap);

	// Bind Specular Map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, SpecularMap);
}

int Material::LoadTexture(const GLchar* texturePath) {
	// Load image using the Free Image library
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(texturePath, 0);
	FIBITMAP* image = FreeImage_Load(format, texturePath);
	FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);

	// Get an available texture index from OpenGL
	GLuint texture = 0;
	glGenTextures(1, &texture);
	assert(texture != 0);

	// Set OpenGL filtering properties (bi-linear interpolation)
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Retrieve width and hight
	int width = FreeImage_GetWidth(image32bits);
	int height = FreeImage_GetHeight(image32bits);

	// This will upload the texture to the GPU memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

	// Free images
	FreeImage_Unload(image);
	FreeImage_Unload(image32bits);

	return texture;
}