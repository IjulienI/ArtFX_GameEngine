#version 460 core

layout(vectices = 3) out;

void main(void)
{
    if(gl_InvocationID == 0){
        gl_TessLevelInner[0] = 5.0;
        //gl_TessLevelOuter[i]
        gl_TessLevelOuter[0] = 5.0;
        gl_TessLevelOuter[1] = 5.0;
        gl_TessLevelOuter[2] = 5.0;
    }
    gl_out[gl_InvocationID].gl_position = gl_in[gl_InvocationID].gl_Position;
}