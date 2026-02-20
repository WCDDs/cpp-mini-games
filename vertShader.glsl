#version 430

uniform float kuan_chang;

layout (location = 0) in vec2 position;  // 从顶点缓冲区接收位置数据
layout (location = 1) in vec3 aColor; //从顶点缓冲区接收颜色数据

out vec3 ourColor;


void main(void)
{
    gl_Position = vec4(position.x*kuan_chang, position.y, 0.0, 1.0);
    ourColor = aColor;
}