#include "Cuboid.h"

Cuboid::Cuboid(const glm::vec3 &position, const glm::vec3 &size, bool is_light_source) : Shape(position, size, glm::vec3(1.0f, 1.0f, 1.0f), "", is_light_source)
{
}

Cuboid::Cuboid(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color, bool is_light_source) : Cuboid(position, size, is_light_source)
{
	this->color_ = color;
	init();
}

Cuboid::Cuboid(const glm::vec3 &position, const glm::vec3 &size, const std::string &texture_path, bool is_light_source) : Cuboid(position, size, is_light_source)
{
	texture_path_ = texture_path;
	init();
}
Cuboid::~Cuboid()
{
}
void Cuboid::init()
{
	if(is_light_source_)
		this->shader_ = Scene::getScene().light_shader;
	else
		this->shader_ = Scene::getScene().shape_shader;
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
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
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
};
	for (uint32_t i = 3; i < vertices_.size(); i += 11)
	{
		vertices_.at(i) = color_.x;
		vertices_.at(i+1) = color_.y;
		vertices_.at(i+2) = color_.z;
	}
}

