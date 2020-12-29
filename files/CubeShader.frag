#version 330 core

struct PointLight {
    vec3 lightPos;
    vec3 lightColor;
};


out vec4 color;

in vec3 Normal;
in vec3 FragPos;  
in vec3 ourColor;

#define MAX_NUM_OF_POINT_LIGHTS 10
uniform int num_of_lights = 0;
uniform PointLight point_lights[MAX_NUM_OF_POINT_LIGHTS];
uniform vec3 ambientColor;
uniform vec3 viewPos;

float near = 0.01;
float far = 100.0;
float specularStrength = 0.5;
  
vec3 calculate_color_from_lightsource(PointLight light, vec3 norm, vec3 viewDir);

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lights_colors;
    for(int i = 0; i < num_of_lights; i++)
        lights_colors += calculate_color_from_lightsource(point_lights[0], norm, viewDir);

    vec3 result = (ambientColor + lights_colors) * ourColor;
    color = vec4(result, 1.0f);
}

vec3 calculate_color_from_lightsource(PointLight light, vec3 norm, vec3 viewDir)
{
    //diffuse
    vec3 lightDir = normalize(light.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.lightColor;

    //specular
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.lightColor; 

    return (diffuse + specular);
}