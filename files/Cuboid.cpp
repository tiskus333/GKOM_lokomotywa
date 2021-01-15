#include "Cuboid.h"

Cuboid::Cuboid(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3& color, const std::string& texture_path, bool is_light_source) : Shape(position, size, color, texture_path, is_light_source)
{
	if (is_light_source_)
		this->shader_ = Scene::getScene().light_shader;
	else
		this->shader_ = Scene::getScene().shape_shader;
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
}

Cuboid::Cuboid(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color, bool is_light_source) : Cuboid(position, size, color, "", is_light_source)
{
}

Cuboid::Cuboid(const glm::vec3 &position, const glm::vec3 &size, const std::string &texture_path, bool is_light_source) : Cuboid(position, size, glm::vec3(1.0f, 1.0f, 1.0f),texture_path, is_light_source)
{
}

Cuboid::Cuboid(const glm::vec3& position, const glm::vec3& size): Cuboid(position, size, glm::vec3(1.0f, 1.0f, 1.0f), "", false)
{
}
void Cuboid::generateIndices()
{
	for (int i = 0; i < 36; ++i)
		indices_.push_back(i);
}

//adding vertivces counterclockwise from nearest to furthest
void Cuboid::generateVertices()
{

	vertices_ = {//TODO proper texture values
	//position(x,y,z), color(rgb),vecNorm(x,y,z), texture(x,y)
	//wall
	-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,	 0.75f, 0.499f,	//3
	 0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,	 0.5f, 0.499f,
	 0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,	 0.5f, 0.001f,
	 0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,	 0.5f, 0.001f,
	-0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,	 0.75f, 0.001f,
	-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f,	 0.75f, 0.499f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.499f,		//1
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.25f, 0.499f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.25f, 0.001f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.25f, 0.001f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.001f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f,  0.0f, 1.0f,	0.0f, 0.499f,

	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	1.0f, 0.001f,		//4
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	0.75f, 0.001f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	0.75f, 0.499f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	0.75f, 0.499f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	1.0f, 0.499f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	1.0f, 0.001f,

	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0.25, 0.001f,		//2
	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0.5f, 0.001f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0.5f, 0.499f,
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0.5f, 0.499f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0.25f, 0.499f,
	 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0.25f, 0.001f,

	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	0.499f, 0.999f,			//6
	 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	0.499f, 0.501f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	0.251f, 0.501f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	0.251f, 0.501f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	0.251f, 0.999f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	0.499f, 0.999f,

	-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	0.249f, 0.501f,			//5
	 0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.249f, 0.999f,
	 0.5f, 0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.001f, 0.999f,
	 0.5f, 0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.001f, 0.999f,
	-0.5f, 0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.001f, 0.501f,
	-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.249f, 0.501f
};
	for (uint32_t i = 3; i < vertices_.size(); i += 11)
	{
		vertices_.at(i) = color_.x;
		vertices_.at(i+1) = color_.y;
		vertices_.at(i+2) = color_.z;
	}
}

