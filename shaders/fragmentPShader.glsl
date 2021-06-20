#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 5

uniform PointLight PointLights[NR_POINT_LIGHTS];
uniform Material material;

uniform samplerCube depthMap;

uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;

float ShadowCalculation(vec3 lightPos, vec3 fragPos) {
	// Get Vector betwee fragPos and lightPos
	vec3 fragLight = fragPos - lightPos;

	float closestDepth = texture(depthMap, fragLight).r;
	// Transform back to original depthMap
	closestDepth *= far_plane;
	// Get Current Linear Depth
	float currentDepth = length(fragLight);
	// Shadow Testing
	float bias = 0.05;
	// Check if a shadow is cast
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// Attenuation
	float rayDistance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * rayDistance + light.quadratic * (rayDistance * rayDistance));
	// Combine
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.TexCoords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

void main() {
	// Properties
	vec3 norm = normalize(fs_in.Normal);
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);

	vec3 result = vec3(0.0f);
	// PointLight Calculations
	for(int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += CalcPointLight(PointLights[i], norm, fs_in.FragPos, viewDir);
	}
	FragColor = vec4(result, 1.0);
}

