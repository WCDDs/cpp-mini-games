#version 430
in vec3 ourColor;
out vec4 color;
void main(void)
{
	color = vec4(ourColor, 1.0);
}