#include "Cuboid.h"

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size)
{
	this->position_ = position;
	generateVertices();
}

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size, glm::vec3 color = glm::vec3(0, 0, 0))
{
	this->size_ = size;
	this->position_ = position;
	this->color_ = color;
	ShaderProgram cubeShader("CubeShader.vert", "CubeShader.frag");
	shader_ = std::make_shared<ShaderProgram>(cubeShader);
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
}

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size, std::string texture_path = "")
{
	
	this->texture_path_ = texture_path;
	generateVertices();
}

void Cuboid::generateIndices()
{
	indices_ = { 
		0,1,2,
		0,2,3,
		4,5,6,
		4,6,7,
		3,2,6,
		3,6,7,
		0,1,5,
		0,5,4,
		1,5,6,
		1,6,2,
		0,4,7,
		0,7,3

	};

}

//adding vertivces counterclockwise from nearest to furthest
void Cuboid::generateVertices()
{
	vertices_ = { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
				-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f, -0.5f,0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
				-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	for (int i = 3; i < vertices_.size(); i += 8)
	{
		vertices_.at(i) = color_.x;
		vertices_.at(i+1) = color_.y;
		vertices_.at(i+2) = color_.z;
	}
}

