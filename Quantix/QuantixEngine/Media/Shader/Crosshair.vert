#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV;

void main()
{
    UV = aUV;
    mat4 scaleMat;
    scaleMat[0] = vec4(0.05, 0.0, 0.0, 0.0);
    scaleMat[1] = vec4(0.0, 0.05, 0.0, 0.0);
    scaleMat[2] = vec4(0.0, 0.0, 0.05, 0.0);
    scaleMat[3] = vec4(0.0, 0.0, 0.0, 1);
    gl_Position = scaleMat * vec4(aPos, 1.0);
}