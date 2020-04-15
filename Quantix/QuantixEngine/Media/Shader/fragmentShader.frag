#version 420 core

/* light struct for all lights */
struct Light
{
	vec3	direction;
	vec3	position;

	vec3	ambient;
	vec3	diffuse;
	vec3	specular;

	float	constant;
	float	linear;
	float	quadratic;

	float	cutOff;
	float	outerCutOff;

	int		type;
};

struct Material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;

	float	shininess;
	bool	textured;
	sampler2D	texture;
};

layout (std140, binding = 1) uniform lights
{
	uint count;
	Light light[10];
};

uniform Material	material;
/* light array with constant size */
uniform Light		lightArray[10];

out vec4			color;

in vec2				UV;
in vec3				outNormal;
in vec3				fragPos;

uniform sampler2D	textureSampler;
uniform vec3		viewPos;

/* calculate light react */
vec3	calculateDiffuse(vec3 lightDir, vec3 norm, vec3 diffuse);
vec3	calculateAmbient(vec3 ambient);
vec3	calculateSpecular(vec3 lightDir, vec3 norm, vec3 specular);

/* calculate type light */
vec3	calculateDirectional(Light light, vec3 lightDir, vec3 norm);
vec3	calculatePointLight(Light light, vec3 lightDir, vec3 norm);
vec3	calculateSpotLight(Light light, vec3 lightDir, vec3 norm);

void main()
{
	vec3	norm = normalize(outNormal);
	vec3	lightDir;
	vec3	output = vec3(0.0);

	for (int i = 0; i < count; ++i)
	{
		/* calculate influence of all lights */
		if (light[i].type == 1)
			output += calculateDirectional(light[i], lightDir, norm);

		if (light[i].type == 2)
			output += calculatePointLight(light[i], lightDir, norm);

		if (light[i].type == 3)
			output += calculateSpotLight(light[i], lightDir, norm);
	}

	if (material.textured)
		color = vec4(output, 1.0) * texture(material.texture, UV);
	else
		color = vec4(output, 1.0);
}

vec3	calculateDirectional(Light light, vec3 lightDir, vec3 norm)
{
	/* direction only */
	lightDir = normalize(-light.direction);

	vec3	diffuse = calculateDiffuse(lightDir, norm, light.diffuse);

	vec3	ambient = calculateAmbient(light.ambient);

	vec3	specular = calculateSpecular(lightDir, norm, light.specular);

	/* return all light composant */
	return (ambient + diffuse + specular);
}

vec3	calculatePointLight(Light light, vec3 lightDir, vec3 norm)
{
	lightDir = normalize(light.position - fragPos);

	/* calculate light attenuation */
	float	distance    = length(lightDir);
	float	attenuation = 1.0 / (light.constant + light.linear * distance +
    		    light.quadratic * (distance * distance));

	vec3	diffuse = calculateDiffuse(lightDir, norm, light.diffuse);

	vec3	ambient = calculateAmbient(light.ambient);

	vec3	specular = calculateSpecular(lightDir, norm, light.specular);

	/* apply attenuation */
	diffuse *= attenuation;
	ambient *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3	calculateSpotLight(Light light, vec3 lightDir, vec3 norm)
{
	lightDir = normalize(light.position - fragPos);

	/* claculate angle of spot */
	float	theta = dot(lightDir, normalize(-light.direction.xyz));
	float	epsilon = light.cutOff - light.outerCutOff;

	float	intensity = clamp((theta - light.cutOff) / epsilon, 0.0, 1.0);

	/* if current angle in the spot */
	if (theta > light.cutOff)
	{
		/* apply intensity */
		vec3	diffuse = calculateDiffuse(lightDir, norm, light.diffuse)
																		* intensity;

		vec3	ambient = calculateAmbient(light.ambient);

		vec3	specular = calculateSpecular(lightDir, norm, light.specular)
																		* intensity;

		return (ambient + diffuse + specular);
	}
	else
		return calculateAmbient(light.ambient);
}

vec3 calculateDiffuse(vec3 lightDir, vec3 norm, vec3 diffuse)
{
	float diff = max(dot(norm, lightDir), 0.0);

	return diffuse * diff * material.diffuse;
}

vec3 calculateAmbient(vec3 ambient)
{
	return ambient * material.ambient;
}

vec3	calculateSpecular(vec3 lightDir, vec3 norm, vec3 specular)
{
	 // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    return specular * spec * material.specular;  
}