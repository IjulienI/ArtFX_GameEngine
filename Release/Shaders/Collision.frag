#version 460 core

in vec3 fragPosition;
in vec3 position;
out vec4 outColor;

void main()
{
    float gradientX = clamp((position.x + 1.0) / 2.0, 0.0, 1.0);
    float gradientY = clamp((position.y + 1.0) / 2.0, 0.0, 1.0);
    
    vec3 colorX = mix(vec3(0.0, 0.5, 0.5), vec3(0.0, 1.0, 1.0), gradientX);
    vec3 colorY = mix(vec3(0.0, 0.5, 0.5), vec3(0.0, 1.0, 1.0), gradientY);

    vec3 finalColor = mix(colorX, colorY, 0.5);
    
    outColor = vec4(finalColor, 1.0);
}
    