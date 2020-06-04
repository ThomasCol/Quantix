#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 UV;
out vec3 outNormal;
out vec3 fragPos;
out vec3 viewPos;
out vec4 fragPosLightSpace;

uniform mat4 TRS;

uniform vec2 tile;

layout (std140, binding = 0) uniform ViewProj
{
	mat4 view;
	mat4 proj;
};

layout (std140, binding = 1) uniform ViewProjLight
{
	mat4 lightView;
	mat4 lightProj;
};

void 	main()
{
	fragPos = vec3(TRS * vec4(position, 1.0));

	/* set pos of fragment */
	gl_Position = proj * view * TRS * vec4(position, 1.0);

	if (tile.x < 1 || tile.y < 1)
		UV = uv;
	else
		UV = uv * tile;

	outNormal = mat3(transpose(inverse(TRS))) * normal;

	fragPosLightSpace = lightProj * lightView * vec4(fragPos, 1.0);
}