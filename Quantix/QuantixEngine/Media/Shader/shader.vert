#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 vViewPos;
layout(location = 2) out vec3 vViewNormal;
layout(location = 3) out mat4 vView;


void main()
{
    fragTexCoord = inTexCoord;
    vView = ubo.view;
    mat4 modelView = ubo.view * ubo.model;
    vec4 viewPos4 = (modelView * vec4(inPosition, 1.0));
    vViewPos = viewPos4.xyz / viewPos4.w;
    vViewNormal = (transpose(inverse(modelView)) * vec4(inNormals, 0.0)).xyz;
    gl_Position = ubo.proj * viewPos4;
}