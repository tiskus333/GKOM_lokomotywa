#version 330 core

out vec4 color;

in vec2 TexCoord;

uniform sampler2D Texture0;

void main()
{    
    color = texture(Texture0, TexCoord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}