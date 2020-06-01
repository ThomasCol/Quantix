#version 450 core

layout (location = 0) out vec4 fragColor;

uniform sampler2D crosshairTex;

in vec2 UV;

void main()
{
    vec4 texColor = texture(crosshairTex, UV);

    if (texColor.a == 0)
        discard;

	fragColor = texColor;
}