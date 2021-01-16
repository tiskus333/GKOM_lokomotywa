#include "Cylinder.h"
#include <math.h>

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, const std::string& texture_path, bool is_light_source) : Shape(position, size, color, texture_path, is_light_source)
{
	if (is_light_source_)
		this->shader_ = Scene::getScene().light_shader;
	else
		this->shader_ = Scene::getScene().shape_shader;
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
}

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, bool is_light_source) : Cylinder(position, size,color,"", is_light_source)
{
}

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size, const std::string& texture_path, bool is_light_source): Cylinder(position, size, glm::vec3(1.0f,1.0f,1.0f),texture_path, is_light_source)
{
}

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size) : Cylinder(position, size, glm::vec3(1.0f, 1.0f, 1.0f), "", false)
{
}

void Cylinder::generateIndices()
{
	indices_.reserve((3 * 2 + 2) * SEGMENTS);
	int segmod = 4 * SEGMENTS;
	int tmp_ind;
	for (uint32_t i = 0; i < SEGMENTS; ++i)
	{
		indices_.push_back((4 * i + 2) % segmod); //right side triangle
		indices_.push_back((4 * (i + 1) + 2) % segmod);
		indices_.push_back((4 * i + 3) % segmod);

		indices_.push_back((4 * (i + 1) + 2) % segmod); //left side triangle
		indices_.push_back((4 * (i + 1) + 3) % segmod);
		indices_.push_back((4 * i + 3) % segmod);

	}
	for (uint32_t i = 0; i < SEGMENTS - 1; ++i)
	{

		//top lid
		tmp_ind = (4 * (i + 1)) % (segmod + 1);
		indices_.push_back(0);
		indices_.push_back(tmp_ind);
		indices_.push_back(tmp_ind + 4);

		//botom lid
		++tmp_ind;
		indices_.push_back(1);
		indices_.push_back(tmp_ind);
		indices_.push_back(tmp_ind+4);
	}
	tmp_ind = (4 * (SEGMENTS)) % (segmod + 1);
	indices_.push_back(0);
	indices_.push_back(tmp_ind);
	indices_.push_back((tmp_ind + 4)%segmod);

	//botom lid
	++tmp_ind;
	indices_.push_back(1);
	indices_.push_back(tmp_ind);
	indices_.push_back((tmp_ind + 4)%segmod);
}

void Cylinder::generateVertices()
{
	float theta = 0.0;
	float step = 2 * 3.14159265f / static_cast<float>(SEGMENTS);
	vertices_.reserve(11*(SEGMENTS+1)*4 + 11*2);

	//lids
	vertices_.push_back(0.0f);  //0 top middle
	vertices_.push_back(0.5f);
	vertices_.push_back(0.0f);
	vertices_.push_back(color_.x);
	vertices_.push_back(color_.y);
	vertices_.push_back(color_.z);

	vertices_.push_back(0.0f);//Normal vec tmp TODO remove it
	vertices_.push_back(1.0f);
	vertices_.push_back(0.0f);

	vertices_.push_back(0.5f);
	vertices_.push_back(0.5f);

	vertices_.push_back(0.0f);  //1 bottom middle
	vertices_.push_back(-0.5f);
	vertices_.push_back(0.0f);
	vertices_.push_back(color_.x);
	vertices_.push_back(color_.y);
	vertices_.push_back(color_.z);

	vertices_.push_back(0);//Normal vec tmp TODO remove it
	vertices_.push_back(-1);
	vertices_.push_back(0);

	vertices_.push_back(0.5f);
	vertices_.push_back(0.5f);
	
	//sides
	for (uint32_t i = 0; i < SEGMENTS; ++i)
	{
		float y_mul = 1.0;
		theta = i * step;
		for (int j = 0; j < 4; ++j)
		{
			y_mul = j % 2 ? -1.0 : 1.0;
			vertices_.push_back(cos(theta)/2);
			vertices_.push_back(y_mul/2 );
			vertices_.push_back(sin(theta)/2);
			vertices_.push_back(color_.x);
			vertices_.push_back(color_.y);
			vertices_.push_back(color_.z);

			if (j < 2)
			{
				vertices_.push_back(cos(theta));
				vertices_.push_back(0);
				vertices_.push_back(sin(theta));
			}
			else
			{
				vertices_.push_back(0);
				vertices_.push_back(y_mul);
				vertices_.push_back(0);
			}
			
			vertices_.push_back(-cos(theta) * 0.5f + 0.5f);
			vertices_.push_back(-sin(theta) * 0.5f + 0.5f);
		}
	}
}

