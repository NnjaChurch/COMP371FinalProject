#version 330 core
out vec4 FragColor;

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

	bool isActive;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	bool isActive;
};

#define NR_POINT_LIGHTS 5
#define NR_SPOT_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform float Opacity;
uniform PointLight PointLights[NR_POINT_LIGHTS];
uniform SpotLight SpotLights[NR_SPOT_LIGHTS];
uniform Material material;

// Function Prototypes
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
	// Properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec4 result = vec4(0.0f);
	// PointLight Calculations
	for(int i = 0; i < NR_POINT_LIGHTS; i++) {
		if(PointLights[i].isActive == true) {
			result += CalcPointLight(PointLights[i], norm, FragPos, viewDir);
		}
	}
	// SpotLight Calculations
	
	for(int i = 0; i < NR_SPOT_LIGHTS; i++) {
		if(SpotLights[i].isActive == true) {
			result += CalcSpotLight(SpotLights[i], norm, FragPos, viewDir);
		}
	}
	FragColor = result;
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
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
	vec4 ambient = vec4(light.ambient, 1.0) * vec4(texture(material.diffuse, TexCoords));
	vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(texture(material.diffuse, TexCoords));
	vec4 specular = vec4(light.specular, 1.0) * spec * vec4(texture(material.specular, TexCoords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// Attenuation
	float rayDistance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * rayDistance + light.quadratic * (rayDistance * rayDistance));
	// SpotLight Intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// Combine
	vec4 ambient = vec4(light.ambient, 1.0) * vec4(texture(material.diffuse, TexCoords));
    vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(texture(material.diffuse, TexCoords));
    vec4 specular = vec4(light.specular, 1.0) * spec * vec4(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}