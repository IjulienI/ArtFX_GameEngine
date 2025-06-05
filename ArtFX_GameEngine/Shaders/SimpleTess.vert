#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;


uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec2 uTiling;

out VS_OUT{
    vec4 color;
    vec2 texCoord;
} vs_out;

void main()
{
    gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
    vs_out.color = vec4(pos, 1.0);
    vs_out.texCoord = texCoord * uTiling;
}
