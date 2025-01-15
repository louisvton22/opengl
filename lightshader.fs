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
uniform Light light;
uniform Material material;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
	float specularStrength = 0.5;
	float ambientStrength = 0.1;
	// attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * distance * distance));

	//ambient
	vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 viewDir = normalize(light.direction - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoords));


	// specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(light.direction, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;
	

	//emission
	vec3 emission = vec3(texture(material.emission, TexCoords)).rgb;
	
	// spotlight
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	 float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	 diffuse *= intensity;
	 specular *= intensity;

	// attenuation
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	

	vec3 result = (ambient + diffuse + specular + emission);
	
	FragColor = vec4(result, 1.0);
}