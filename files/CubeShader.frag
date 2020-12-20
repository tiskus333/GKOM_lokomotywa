#version 330 core

in vec3 ourColor;
out vec4 color;
in vec3 Normal;

float near = 0.01;
float far = 100.0;
  
void main()
{
    color = vec4(ourColor, 1.0f);
}