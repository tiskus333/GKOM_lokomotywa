#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 3) in vec2 vertexUV; // Texture coordinates

out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0);
    TexCoord = vertexUV;
} 