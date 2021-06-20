#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;

void main() {
	vs_out.FragPos = vec3(worldMatrix * vec4(aPos, 1.0));
	vs_out.Normal = transpose(inverse(mat3(worldMatrix))) * aNormal;
	vs_out.TexCoords = aTexCoords;
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos, 1.0);
}