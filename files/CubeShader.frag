#version 330 core

in vec3 ourColor;
out vec4 color;
in vec3 Normal;
in vec3 FragPos;  


uniform vec3 lightPos;
uniform vec3 ambientColor;

float near = 0.01;
float far = 100.0;
  
void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * lightColor;
    vec3 result = (/*ambient + */diff) * ourColor + ambientColor * ourColor;

    color = vec4(result, 1.0f);
}