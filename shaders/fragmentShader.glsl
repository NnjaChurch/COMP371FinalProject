#version 330 core
in vec3 VertexColor;
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D textureSampler;
void main() {
	vec4 textureColour = texture(textureSampler, TexCoords);
	FragColor = textureColour;
}