#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

layout (std140, binding = 0) uniform ViewProj
{
	mat4 view;
	mat4 proj;
};

out vec3 localPos;

void main()
{
    localPos = position;

    mat4 rotView = mat4(mat3(view));
    vec4 clipPos = proj * rotView * vec4(localPos, 1.0);
    gl_Position = clipPos.xyww;
}
