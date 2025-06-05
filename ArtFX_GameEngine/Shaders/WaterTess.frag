#version 450

in TESE_OUT{
    vec4 color;
    vec2 texCoord;
    float displacement;

} frag_in;

out vec4 FragColor;

layout(binding = 0) uniform sampler2D uTexture;

uniform vec4 uBaseColor = vec4(0.2, 0.6, 0.9, 1.0);
uniform vec4 uTopColor = vec4(0.82, 0.87, 0.9, 1.0);
uniform vec4 uBottomColor = vec4(0.07, 0.2, 0.6, 1.0);

float Clamp (float value, float min, float max)
{
    if(value >= max)
    {
        return max;
    }
    else if(value <= min)
    {
        return min;
    }
    return value;
}

void main()
{
    float foam = Clamp(frag_in.displacement, 0.0, 1.0);
    vec4 foamWave = mix(uBaseColor, uTopColor, foam);

    float depth = 1 + Clamp(frag_in.displacement, -1.0, 0.0);

    vec3 color = mix(uBottomColor, foamWave, depth).rgb;
    
    FragColor = vec4(color, 1.0);
}
