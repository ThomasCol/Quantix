#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 worldPos;

uniform mat4 captureView;
uniform mat4 projection;

void main()
{
    worldPos = position;
    gl_Position =  projection * captureView * vec4(position, 1.0);
}