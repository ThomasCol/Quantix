#version 450 core

layout (location = 0) in vec3 pos;

layout (std140, binding = 0) uniform ViewProj
{
	mat4 view;
	mat4 proj;
	mat4 lightProj;
	mat4 lightView;
};

uniform mat4 TRS;

void main()
{
    gl_Position = proj * view * TRS * vec4(pos, 1.0);
}