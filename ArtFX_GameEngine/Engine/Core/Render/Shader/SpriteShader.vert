#version 330 core

in vec3 pos;
in vec2 texCoord;

out vec2 fragTexCoord;
void main()
{
    gl_Position = vec4(pos, 1.0);
    fragTexCoord = texCoord;
}