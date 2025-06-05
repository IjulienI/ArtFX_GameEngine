#version 450 core

layout(triangles, fractional_even_spacing, cw) in;
in TESC_OUT{
    vec4 color;
    vec2 texCoord;

} tese_in[];
out TESE_OUT{
    vec4 color;
    vec2 texCoord;

} tese_out;

uniform sampler2D uNoise;
uniform float uDisplacementScale;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

void main(void)
{
    vec2 texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
    float displacement = texture(uNoise, texCoord).r * uDisplacementScale;

    vec4 position = (gl_TessCoord.x * gl_in[0].gl_Position +
    gl_TessCoord.y * gl_in[1].gl_Position +
    gl_TessCoord.z * gl_in[2].gl_Position);

    position.xyz += position.xyz * displacement; // Appliquer le déplacement

    gl_Position = position;
    tese_out.color = mix(tese_in[0].color, tese_in[1].color, gl_TessCoord.x);
    tese_out.texCoord = texCoord;
}
