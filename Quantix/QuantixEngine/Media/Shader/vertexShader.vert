#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 UV;
out vec3 outNormal;
out vec3 fragPos;
out vec3 viewPos;

uniform mat4 TRS;
uniform mat4 view;
uniform mat4 proj;

void 	main()
{
	fragPos = vec3(TRS * vec4(position, 1.0));

	/* set pos of fragment */
	gl_Position = proj * view * TRS * vec4(position, 1.0);

	UV = uv;

	outNormal = mat3(transpose(inverse(TRS))) * normal;
}