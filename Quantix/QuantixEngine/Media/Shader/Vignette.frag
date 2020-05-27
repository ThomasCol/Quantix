#version 450 core

in vec2 UV;
out vec4 color;
uniform sampler2D colorTexture;

// For Vignette
uniform vec2 uResolution;
uniform float uOuterRadius;
uniform float uInnerRadius;

void main()
{
    color = vec4(texture(colorTexture, UV).rgb, 1.0);

	// Calc Vignette Coef
	vec2 relativePosition = gl_FragCoord.xy / uResolution - .5;
	float len = length(relativePosition);
	float vignette = smoothstep(uOuterRadius, uInnerRadius, len);

    color.rgb = color.rgb * vignette;
}