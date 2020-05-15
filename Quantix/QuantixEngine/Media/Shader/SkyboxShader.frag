#version 420 core

in vec3 localPos;

layout (location = 0) out vec4			fragColor;
layout (location = 1) out vec4			brightColor;

uniform samplerCube skyboxTexture;

uniform vec3 		                    minBright = vec3(0.2126, 0.7152, 0.0722);

void main()
{
    vec3 envColor = texture(skyboxTexture, localPos).rgb;

    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));

    fragColor = vec4(envColor, 1.0);

    float brightness = dot(fragColor.rgb, minBright);
	if(brightness > 1.0)
        brightColor += vec4(fragColor.rgb, 1.0);
	else
		brightColor += vec4(0.0, 0.0, 0.0, 1.0);
}