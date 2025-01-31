#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	float shininess;
};


struct DirLight {
	vec3 direction;

	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	//ambient
	vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords)) * light.ambient;

	// diffuse
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.texture_diffuse1, TexCoords));


	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.texture_specular1, TexCoords)) * spec * light.specular;

	return (ambient + diffuse + specular);
}


void main()
{
	// vec3 norm = normalize(Normal);
	// vec3 viewDir = normalize(viewPos - FragPos);
	// vec3 result = CalcDirLight(dirLight, norm, viewDir);

	FragColor = texture(material.texture_diffuse1, TexCoords);
}