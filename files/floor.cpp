#include "floor.h"

Floor::Floor(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3& color, const std::string& texture_path, bool is_light_source) : Shape(position, size, color, texture_path, is_light_source)
{
	if (is_light_source_)
		this->shader_ = Scene::getScene().light_shader;
	else
		this->shader_ = Scene::getScene().shape_shader;
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
}

Floor::Floor(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color, bool is_light_source) : Floor(position, size, color, "", is_light_source)
{
}

Floor::Floor(const glm::vec3 &position, const glm::vec3 &size, const std::string &texture_path, bool is_light_source) : Floor(position, size, glm::vec3(1.0f, 1.0f, 1.0f),texture_path, is_light_source)
{
}

Floor::Floor(const glm::vec3& position, const glm::vec3& size): Floor(position, size, glm::vec3(1.0f, 1.0f, 1.0f), "", false)
{
}
void Floor::generateIndices()
{
	for (int i = 0; i < 36; ++i)
		indices_.push_back(i);
}

//adding vertivces counterclockwise from nearest to furthest
void Floor::generateVertices()
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

	-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	24.9f, 50.1f,			//5
	 0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   24.9f, 99.9f,
	 0.5f, 0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.1f, 99.9f,
	 0.5f, 0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   00.1f, 99.9f,
	-0.5f, 0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   00.1f, 50.1f,
	-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,   24.9f, 50.1f
};
	for (uint32_t i = 3; i < vertices_.size(); i += 11)
	{
		vertices_.at(i) = color_.x;
		vertices_.at(i+1) = color_.y;
		vertices_.at(i+2) = color_.z;
	}
}
void Floor::adjustPosition(const glm::vec3& train_pos)
{
	//if((int)std::abs(std::floor(train_pos.z)) < )
	//position_ = { 0,-.5,std::floor(train_pos.z) + 4.02};
}