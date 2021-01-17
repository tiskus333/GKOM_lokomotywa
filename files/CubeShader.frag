#version 330 core

struct PointLight {
    vec3 lightPos;
    vec3 lightColor;
};


out vec4 color;

in vec3 Normal;
in vec3 FragPos;  
in vec3 ourColor;
in vec2 TexCoord;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;

uniform sampler2D Texture0;
uniform bool hasTexture = false;

#define MAX_NUM_OF_POINT_LIGHTS 10
uniform int num_of_lights = 0;
uniform PointLight point_lights[MAX_NUM_OF_POINT_LIGHTS];
uniform vec3 ambientColor;
uniform vec3 viewPos;

float specularStrength = 0.5;
  
vec3 calculate_color_from_lightsource(PointLight light, vec3 norm, vec3 viewDir);

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(point_lights[0].lightPos - FragPos);
    float bias = 0.0015;
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 lights_colors;
    for(int i = 0; i < num_of_lights; i++)
        lights_colors += calculate_color_from_lightsource(point_lights[i], norm, viewDir);
    
    vec3 tmpColor = ourColor;
    if(hasTexture ) tmpColor = vec3(1.0f,1.0f,1.0f);

    float shadow = ShadowCalculation(FragPosLightSpace);

    vec3 result = (ambientColor + (1.0 - shadow) * lights_colors) * tmpColor;

    if(hasTexture ) 
        color = texture(Texture0, TexCoord) *vec4(result, 1.0f);
    else
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