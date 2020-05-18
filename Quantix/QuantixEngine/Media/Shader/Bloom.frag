#version 450 core

layout (location = 0) out vec4 fragColor;

in vec2 UV;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform bool bloom;
uniform float exposure;
uniform float gamma;

void main()
{             
    vec3 hdrColor = texture(scene, UV).rgb;      
    vec3 bloomColor = texture(bloomBlur, UV).rgb;
    if(bloom)
        hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    fragColor = vec4(result, 1.0);
}