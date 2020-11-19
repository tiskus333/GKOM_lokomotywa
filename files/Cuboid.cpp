#include "Cuboid.h"

Cuboid::Cuboid(const glm::vec3& position,const  glm::vec3& size) 
{
	this->position_ = position;
	this->size_ = size;
	this->color_ = glm::vec3(1.0f, 1.0f, 1.0f);
	this->texture_path_ = "";
}


Cuboid::Cuboid(const glm::vec3& position, const glm::vec3&size, const glm::vec3& color): Cuboid(position, size)
{
	this->color_ = color;
	init();
}

Cuboid::Cuboid(const glm::vec3& position, const glm::vec3& size, const std::string& texture_path): Cuboid(position, size)
{
	texture_path_ = texture_path;
	init();
}
Cuboid::~Cuboid()
{
	Shape::freeBuffers();
}
void Cuboid::init()
{
	this->shader_ = ShaderProgram("CubeShader.vert", "CubeShader.frag");
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
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

	for (uint32_t i = 3; i < vertices_.size(); i += 8)
	{
		vertices_.at(i) = color_.x;
		vertices_.at(i+1) = color_.y;
		vertices_.at(i+2) = color_.z;
	}
}

