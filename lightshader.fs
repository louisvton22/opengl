#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 FragColor;
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
struct Light {

	//note: position and direction of light needed for spotlights
	vec3 position; // no longer necessary when using directional lights
	vec3 direction; // used for direction
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	// point light attenuation constants
	float constant;
	float linear;
	float quadratic;

	// spotlight cutoff radius
	float cutOff;
	float outerCutOff;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform Light light;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	//ambient
	vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

	// diffuse
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoords));


	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant  + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)) * attenuation;
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords)) * attenuation;
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords)) * attenuation;

	return (ambient + diffuse + specular);
}

void main()
{
	float specularStrength = 0.5;
	float ambientStrength = 0.1;
	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}
	

	//emission
	vec3 emission = vec3(texture(material.emission, TexCoords)).rgb;
	
	// spotlight
	
	float theta = dot(normalize(light.position-FragPos), normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	//diffuse *= intensity;
	//specular *= intensity;

	result += 0.2 * intensity;
	FragColor = vec4(result, 1.0);
}
