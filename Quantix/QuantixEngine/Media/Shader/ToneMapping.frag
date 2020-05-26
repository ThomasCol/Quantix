#version 450 core

layout (location = 0) out vec4 fragColor;

uniform sampler2D scenescene;
uniform mat4 uColorTransform;

in vec2 UV;

void main()
{
    // Treat color like a homogeneous vector
    vec4 rgb4 = vec4(texture(scene, aUV).rgb, 1.0);
  
    fragColor.rgb = (uColorTransform * rgb4).rgb;
    fragColor.a = rgb4.a;
}