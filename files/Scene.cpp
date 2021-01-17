
#include "Scene.h"

Scene::Scene(/* args */) : number_of_lights(0), ambient_light(0.2, 0.2, 0.2)
{
    shape_shader = ShaderProgram("CubeShader.vert", "CubeShader.frag");
    light_shader = ShaderProgram("LightShader.vert", "LightShader.frag");
    skybox_shader = ShaderProgram("SkyBox.vert", "SkyBox.frag");
    for (int i = 0; i < MAX_NUM_OF_POINT_LIGHTS; i++)
    {
        is_light_used[i] = false;
    }
}

Scene::~Scene()
{
}

Scene &Scene::getScene()
{
    static Scene instance;
    return instance;
}

void Scene::setVec3InShaders(const std::string &name, glm::vec3 &value)
{
    shape_shader.Use();
    shape_shader.setVec3(name, value);
    light_shader.setVec3(name, value);
    skybox_shader.setVec3(name, value);
}

void Scene::setMatrix4fvInShaders(const std::string &name, glm::mat4 &matrix)
{
    shape_shader.setMatrix4fv(name, matrix);
    light_shader.setMatrix4fv(name, matrix);
    skybox_shader.setMatrix4fv(name, matrix);
}

unsigned int Scene::addPointLightSource(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 light_direction)
{
    if (number_of_lights == MAX_NUM_OF_POINT_LIGHTS)
        throw std::exception("All of lights already used");
    for (int i = 0; i < MAX_NUM_OF_POINT_LIGHTS; i++)
    {
        if (!is_light_used[i])
        {
            is_light_used[i] = true;
            light_positions[i] = lightPos;
            light_colors[i] = lightColor;
            light_directions[i] = light_direction;
            number_of_lights++;
            return i;
        }
    }
    throw std::exception("No free light found");
}

void Scene::updatePointLightSource(unsigned int number, glm::vec3 lightPos, glm::vec3 lightColor)
{
    if (is_light_used[number])
    {
        light_positions[number] = lightPos;
        light_colors[number] = lightColor;
    }
    else
    {
        throw std::exception("Tried to update unused light source");
    }
}

void Scene::removePointLightSource(unsigned int number)
{
    if (is_light_used[number])
    {
        is_light_used[number] = false;
        number_of_lights--;
    }
}

/**
 * Update light sources stored in shaders
**/
void Scene::updateLights()
{
    shape_shader.setVec3("ambientColor", ambient_light);
    int found_lights = 0;
    for (int i = 0; i < MAX_NUM_OF_POINT_LIGHTS; i++)
    {
        if (is_light_used[i])
        {
            std::string light = "point_lights[" + std::to_string(found_lights) + "]";
            shape_shader.setVec3(light + ".lightPos", light_positions[found_lights]);
            shape_shader.setVec3(light + ".lightColor", light_colors[found_lights]);
            shape_shader.setVec3(light + ".lightDir", light_directions[found_lights]);
            found_lights++;
        }
    }
    shape_shader.setInt("num_of_lights", found_lights);
    if (found_lights != number_of_lights)
    {
        throw std::exception("Something went wrong during counting ligts");
    }
}

GLuint Scene::LoadMipmapTexture(GLuint texId, const char* fname)
{
    int width, height;
    unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == nullptr)
        throw std::exception("Failed to load texture file");

    GLuint texture;
    glGenTextures(1, &texture);

    glActiveTexture(texId);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

GLuint Scene::getTexture(std::string& texture)
{
    for (auto& p : texture_chache_)
        if (p.first == texture)
            return p.second;
    GLuint text_id =  LoadMipmapTexture(GL_TEXTURE0, texture.c_str());
    texture_chache_.emplace_back(texture, text_id);
    return text_id;
}
