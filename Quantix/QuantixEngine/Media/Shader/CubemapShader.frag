#version 420 core

in vec3 worldPos;

out vec4 color;

uniform sampler2D skyboxTexture;

const vec2 invTan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invTan;
    uv += 0.5;
    return uv;
}

void main()
{
   vec2 uv = SampleSphericalMap(normalize(worldPos));

    color = vec4(texture(skyboxTexture, uv).rgb, 1.0);
}