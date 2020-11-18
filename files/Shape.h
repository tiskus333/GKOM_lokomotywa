#pragma once
#include "Object.h"
#include "Shader.h"
#include "shprogram.h"
#include <vector>
#include <GL/glew.h>

class Shape : public Object
{
public:
	Shape* parent_ = nullptr;
	bool rotatable_;
	glm::vec3 color_;
	glm::vec3 size_;
	glm::vec3 scale_factor_;
	glm::mat4 model_;
	std::shared_ptr<ShaderProgram> shader_;


	std::vector<GLfloat> vertices_;
	std::vector<GLuint> indices_;
	GLuint VAO_, VBO_, EBO_;

	std::string texture_path_;

	Shape();
	~Shape();
	void bindBuffers();
	void freeBuffers();
	void draw();
	void move(const glm::vec3& displacement) override;
	void rotate(const glm::vec3& angle, const glm::vec3& point) override;
	void scale(const glm::vec3& factor);
	bool isRotatable();

};

