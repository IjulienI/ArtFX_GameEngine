#version 450 core

layout(triangles, fractional_even_spacing, cw) in;

layout(binding = 1) uniform sampler2D uNoise;

uniform float uTime;
uniform float uAmplitude;
uniform float uFrequency;
uniform float uSpeed;

uniform float uDisplacementScale;

in TESC_OUT{
    vec4 color;
    vec2 texCoord;

} tese_in[];
out TESE_OUT{
    vec4 color;
    vec2 texCoord;
    float displacement;

} tese_out;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2) {
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

float animWave(vec2 uv, float noise){
    return sin((uv.x - uTime * uSpeed)* uFrequency) * (uAmplitude * noise);
}

void main(void)
{
    vec2 texCoord = interpolate2D(tese_in[0].texCoord, tese_in[1].texCoord, tese_in[2].texCoord);
    vec4 position = interpolate4D(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
    
    float noise = texture(uNoise, texCoord * 10.0).r;
    
    float wave = animWave(texCoord, noise) * mix(50, 150, noise);
    
    position.y += wave;
    gl_Position = position;
    
    tese_out.color = mix(tese_in[0].color, tese_in[1].color, gl_TessCoord.x);
    tese_out.texCoord = texCoord;
    tese_out.displacement = wave * uDisplacementScale;
}
