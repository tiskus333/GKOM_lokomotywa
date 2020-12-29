#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;	// The color variable has attribute position 1
layout (location = 2) in vec3 aNormal; // normal vector
  
out vec3 ourColor; // Output a color to the fragment shader
out vec3 Normal; //normal vector passed to the fragment shader
out vec3 FragPos; //thi

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection*view*transform * vec4(position, 1.0);
    ourColor = color; // Set ourColor to the input color we got from the vertex data
    Normal = aNormal;
    FragPos = vec3(view*transform * vec4(position, 1.0));
} 
