
#include "Scene.h"

Scene::Scene(/* args */) : number_of_lights(0), ambient_light(0.2, 0.2, 0.2)
{
    shape_shader = ShaderProgram("CubeShader.vert", "CubeShader.frag");
    light_shader = ShaderProgram("LightShader.vert", "LightShader.frag");
    skybox_shader = ShaderProgram("SkyBox.vert", "SkyBox.frag");
    simpleDepthShader = ShaderProgram("3.1.3.shadow_mapping_depth.vs", "3.1.3.shadow_mapping_depth.fs");
    debugDepthQuad = ShaderProgram("3.1.3.debug_quad.vs", "3.1.3.debug_quad_depth.fs");
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

unsigned int Scene::addPointLightSource(glm::vec3 lightPos, glm::vec3 lightColor)
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

void Scene::initShadows()
{
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // shader configuration
    // --------------------
    shape_shader.Use();
    shape_shader.setInt("shadowMap", 1);
    debugDepthQuad.Use();
    debugDepthQuad.setInt("depthMap", 0);
}

void Scene::setViewPort(const glm::vec3& train_pos)
{
    lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, train_pos, glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    simpleDepthShader.setMatrix4fv("lightSpaceMatrix", lightSpaceMatrix);
    
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Scene::renderQuad()
{
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Scene::resetViewPort()
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // reset viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shape_shader.Use();
    shape_shader.setMatrix4fv("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    //glUniform1i(glGetUniformLocation(shape_shader.get_programID(), "shadowMap"), 1);
}

void Scene::debug()
{

    debugDepthQuad.Use();
    debugDepthQuad.setFloat("near_plane", near_plane);
    debugDepthQuad.setFloat("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    //glUniform1i(glGetUniformLocation(shape_shader.get_programID(), "depthMap"), 0);
    renderQuad();
}


