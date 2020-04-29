#version 420 core

/* light struct for all lights */
struct Light
{
	float   test[2];
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

	sampler2D	shadowMap;
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

uniform bool phong;

out vec4			FragColor;

in vec2				UV;
in vec3				outNormal;
in vec3				fragPos;
in vec4				fragPosLightSpace;

uniform vec3		viewPos;

/* calculate light react */
vec3	calculateDiffuse(vec3 lightDir, vec3 norm, vec3 diffuse);
vec3	calculateAmbient(vec3 ambient);
vec3	calculateSpecular(vec3 lightDir, vec3 norm, vec3 specular);

/* calculate type light */
vec3	calculateDirectional(Light light, vec3 lightDir, vec3 norm, float shadow);
vec3	calculatePointLight(Light light, vec3 lightDir, vec3 norm, float shadow);
vec3	calculateSpotLight(Light light, vec3 lightDir, vec3 norm, float shadow);
float	ComputeShadow(vec4 fragPosLightSpace);

void main()
{
	/*vec3	norm = normalize(outNormal);
	vec3	lightDir;
	vec3	output = vec3(0.0);

	float shadow = ComputeShadow(fragPosLightSpace);

	for (int i = 0; i < count; ++i)
	{*/
		/* calculate influence of all lights */
		/*if (light[i].type == 1)
			output += calculateDirectional(light[i], lightDir, norm, shadow);

		if (light[i].type == 2)
			output += calculatePointLight(light[i], lightDir, norm, shadow);

		if (light[i].type == 3)
			output += calculateSpotLight(light[i], lightDir, norm, shadow);
	}

	if (material.textured)
		color = vec4(output, 1.0) * texture(material.texture, UV);
	else
		color = vec4(output, 1.0);*/
	vec3 color = vec3(1.0);
	if (material.textured)
		color = texture(material.texture, UV).rgb;
    vec3 normal = normalize(outNormal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(light[0].position - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ComputeShadow(fragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}

float	ComputeShadow(vec4 fragPosLightSpace)
{
	vec3 lightDir = normalize(light[0].position - fragPos);
	// perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(material.shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(normalize(outNormal), lightDir)), 0.005);
    // check whether current frag pos is in shadow
    float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(material.shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
    	for(int y = -1; y <= 1; ++y)
    	{
      		float pcfDepth = texture(material.shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
        	shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
    	}    
	}
	shadow /= 9.0;

	if (projCoords.z > 1.0)
		shadow = 0.0;

    return shadow;
}

vec3	calculateDirectional(Light light, vec3 lightDir, vec3 norm, float shadow)
{
	/* direction only */
	lightDir = normalize(-light.direction);

	vec3	diffuse = calculateDiffuse(lightDir, norm, light.diffuse);

	vec3	ambient = calculateAmbient(light.ambient);

	vec3	specular = calculateSpecular(lightDir, norm, light.specular);

	/* return all light composant */
	return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3	calculatePointLight(Light light, vec3 lightDir, vec3 norm, float shadow)
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

	return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3	calculateSpotLight(Light light, vec3 lightDir, vec3 norm, float shadow)
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

		return (ambient + (1.0 - shadow) * (diffuse + specular));
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
	vec3 halwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halwayDir), 0.0), material.shininess);
	
    return specular * spec * material.specular;  
}