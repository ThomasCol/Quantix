#version 450 core

out vec4 fragColor;
  
in vec2 UV;

uniform sampler2D image;
  
uniform bool horizontal;
uniform float weight[5];

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, UV).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, UV + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, UV - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, UV + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, UV - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    fragColor = vec4(result, 1.0);
}