#version 450 core

layout (location = 0) in vec3 pos;

layout (std140, binding = 1) uniform ViewProjLight
{
	mat4 lightView;
	mat4 lightProj;
};

uniform mat4 model;

void main()
{
    gl_Position = lightProj * lightView * model * vec4(pos, 1.0);
}