#version 420 core

in vec3 localPos;

out vec4 color;

uniform samplerCube skyboxTexture;

void main()
{
    vec3 envColor = texture(skyboxTexture, localPos).rgb;

    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));

    color = vec4(envColor, 1.0);
}