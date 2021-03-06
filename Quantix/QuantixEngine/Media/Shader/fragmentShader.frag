#version 420 core

layout (location = 0) out vec4			fragColor;
layout (location = 1) out vec4			brightColor;

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
	bool	isTextured;
	bool	hasEmissive;

	sampler2D	shadowMap;
	samplerCube	pointShadowMap;
	sampler2D	diffuseTexture;
	sampler2D	emissiveTexture;
};

layout (std140, binding = 2) uniform lights
{
	uint count;
	Light light[10];
};

uniform Material	material;
/* light array with constant size */
uniform Light		lightArray[10];

in vec2				UV;
in vec3				outNormal;
in vec3				fragPos;
in vec4				fragPosLightSpace;

uniform vec3 		minBright = vec3(0.2126, 0.7152, 0.0722);

uniform vec3		viewPos;
uniform float		farPlane;
uniform vec3		lightPos;

// array of offset direction for sampling
const vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

/* calculate light react */
vec3	calculateDiffuse(vec3 lightDir, vec3 norm, vec3 diffuse);
vec3	calculateAmbient(vec3 ambient);
vec3	calculateSpecular(vec3 lightDir, vec3 norm, vec3 specular);

/* calculate type light */
vec3	calculateDirectional(Light light, vec3 lightDir, vec3 norm, float shadow);
vec3	calculatePointLight(Light light, vec3 lightDir, vec3 norm, float shadow);
vec3	calculateSpotLight(Light light, vec3 lightDir, vec3 norm, float shadow);
float	ComputeShadow(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal);
float 	ComputePointShadow(vec3 fragPos);

void main()
{
	vec3	norm = normalize(outNormal);
	vec3	lightDir;
	vec3	output = vec3(0.0);
	
	if (material.hasEmissive)
    	brightColor = texture(material.emissiveTexture, UV);
	else
		brightColor = vec4(0.0);

	float shadow;

	if (count > 1)
	{
		shadow = ComputePointShadow(fragPos);
		//shadow = ComputeShadow(fragPosLightSpace, normalize(light[0].position - fragPos), norm);
	}
	else
		shadow = ComputeShadow(fragPosLightSpace, normalize(light[0].position - fragPos), norm);

	output += calculateDirectional(light[0], lightDir, norm, shadow);

	for (int i = 1; i < count; ++i)
	{
		/* calculate influence of all lights */
		if (light[i].type == 1)
			output += calculateDirectional(light[i], lightDir, norm, shadow);

		if (light[i].type == 2)
			output += calculatePointLight(light[i], lightDir, norm, shadow);

		if (light[i].type == 3)
			output += calculateSpotLight(light[i], lightDir, norm, shadow);
	}

	if (material.isTextured)
		fragColor = vec4(output, 1.0) * texture(material.diffuseTexture, UV);
	else
		fragColor = vec4(output, 1.0);

	float brightness = dot(fragColor.rgb, minBright);
	if(brightness > 1.0)
        brightColor += vec4(fragColor.rgb, 1.0);
	else
		brightColor += vec4(0.0, 0.0, 0.0, 1.0);
}

float	ComputeShadow(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal)
{
	// perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(material.shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
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

float ComputePointShadow(vec3 fragPos)
{
	// get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // use the fragment to light vector to sample from the depth map    
    // float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    // closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    // float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    // float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
    // PCF
    // float shadow = 0.0;
    // float bias = 0.05; 
    // float samples = 4.0;
    // float offset = 0.1;
    // for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    // {
        // for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        // {
            // for(float z = -offset; z < offset; z += offset / (samples * 0.5))
            // {
                // float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r; // use lightdir to lookup cubemap
                // closestDepth *= far_plane;   // Undo mapping [0;1]
                // if(currentDepth - bias > closestDepth)
                    // shadow += 1.0;
            // }
        // }
    // }
    // shadow /= (samples * samples * samples);
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / farPlane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(material.pointShadowMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= farPlane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
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