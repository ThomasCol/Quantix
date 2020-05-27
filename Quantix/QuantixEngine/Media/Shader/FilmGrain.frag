#version 450 core

layout (location = 0) out vec4 fragColor;

uniform sampler2D scene;

in vec2 UV;

// For Film Grain
uniform float uAmount;
uniform float uCoef;

float random(vec2 pts)
{
	vec2 randomPoint = vec2(
		23.14069263277926,
		2.665144142690225
	);
	return fract( cos( dot(pts, randomPoint) ) * 12345.6789 );
}

void main()
{
    vec2 uvRandom = UV;
	uvRandom.y *= random(vec2(uvRandom.y, uAmount));
	// Apply Noises
	fragColor.rgb += random(uvRandom)* uCoef;
}