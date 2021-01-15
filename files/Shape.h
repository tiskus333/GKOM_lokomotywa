#pragma once
#include "Object.h"
#include "Scene.h"
#include "Shader.h"
#include "shprogram.h"
#include <SOIL.h>
#include <vector>

class Shape : public Object
{
protected:
	glm::vec3 color_;
	glm::vec3 size_;
	glm::mat4 model_;
	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;
	GLuint VAO_, VBO_, EBO_;
	ShaderProgram shader_;
	std::string texture_path_;
	GLuint texture_;

	bool is_light_source_;
	int number_of_light_; //number of light in scene

	/* creating openGL buffers */
	void bindBuffers();
	/* deleting openGL buffers */
	void freeBuffers();

	/* internaly construct shape with provided parameters */
	Shape(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color, const std::string &texture_path, bool is_light_source);

public:
	/* free buffers and delete shape */
	~Shape();

	/* Load texture from file */
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);

	/* draw shape in relation to parent object, if no parent leave empty */
	void draw(const glm::mat4 &parent_model = glm::mat4(1.f));

	/* scale shape by given scale factor in each direction */
	void scale(const glm::vec3 &factor);

	/* set object's size */
	void setSize(const glm::vec3 &size);

	/* set object color using float range 0.0->1.0*/
	void setColor(const float r, const float g, const float b);

	/* set shape color using standard 0-255 range */
	void setColor(const uint32_t r, uint32_t g, const uint32_t b);

	/* set shader to use */
	void setShader(const ShaderProgram& shader);
};
