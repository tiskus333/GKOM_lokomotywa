#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SOIL.h>
#include "shprogram.h"

#define MAX_NUM_OF_POINT_LIGHTS 10

class Scene
{
private:
    Scene(/* args */);
    ~Scene();

    glm::vec3 light_positions[MAX_NUM_OF_POINT_LIGHTS];
    glm::vec3 light_colors[MAX_NUM_OF_POINT_LIGHTS];
    bool is_light_used[MAX_NUM_OF_POINT_LIGHTS];
    unsigned int number_of_lights;
    std::vector<std::pair<std::string, GLuint>> texture_chache_;
public:
    //shadows
    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH = 16384, SHADOW_HEIGHT = 16384;
    const GLuint WIDTH = 1920, HEIGHT = 1080;
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 200.f;
    glm::vec3 lightPos = glm::vec3(-10.0f, 300.f, 10.f);
    //shadows

    glm::vec3 light_directions[MAX_NUM_OF_POINT_LIGHTS];
    glm::vec3 ambient_light;

    ShaderProgram shape_shader;
    ShaderProgram light_shader;
    ShaderProgram skybox_shader;
    ShaderProgram simpleDepthShader;

    static Scene &getScene();

    void operator=(const Scene &) = delete;

    void setVec3InShaders(const std::string &name, glm::vec3 &value);
    void setMatrix4fvInShaders(const std::string &name, glm::mat4 &matrix);

    unsigned int addPointLightSource(glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 light_direction = glm::vec3(0.0, 0.0, 0.0));
    void updatePointLightSource(unsigned int number, glm::vec3 lightPos,glm::vec3 lightColor);
    void removePointLightSource(unsigned int number);
    unsigned int getNUmberOfLights() { return number_of_lights; }
    void updateLights();
    /* Load texture from file */
    GLuint LoadMipmapTexture(GLuint texId, const char* fname);
    GLuint getTexture(std::string& texture);
    void initShadows();
    void setViewPort(const glm::vec3& train_pos);
    void resetViewPort();
    void renderQuad();
};