#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
	GLuint program_id; // The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar *vertexPath, const GLchar *fragmentPath);
	ShaderProgram();

	// Use the program
	void Use() const
	{
		glUseProgram(get_programID());
	}

	// returns program ID
	GLuint get_programID() const
	{
		return program_id;
	}

	void setBool(const std::string &name, bool value) const
	{
		Use();
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const
	{
		Use();
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const
	{
		Use();
		glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
	}
	void setVec3(const std::string &name, glm::vec3 &value) const
	{
		Use();
		glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, glm::value_ptr(value));
	}
	void setMatrix4fv(const std::string &name, glm::mat4 &matrix)
	{
		Use();
		unsigned int transformLoc = glGetUniformLocation(program_id, name.c_str());
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
};