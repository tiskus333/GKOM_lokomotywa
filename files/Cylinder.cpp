#include "Cylinder.h"
#include <math.h>

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size) : Shape(position, size, glm::vec3(1.0f, 1.0f, 1.0f), "")
{
}

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color) : Cylinder(position, size)
{
	this->color_ = color;
	init();
}

Cylinder::Cylinder(const glm::vec3& position, const glm::vec3& size, const std::string& texture_path): Cylinder(position, size)
{
	texture_path_ = texture_path;
	init();
}

Cylinder::~Cylinder()
{
}

void Cylinder::generateIndices()
{
	indices_.reserve((3 * 2 + 2) * SEGMENTS);
	for (uint32_t i = 1; i <= SEGMENTS; ++i)
	{
		indices_.push_back(0); //top triangle
		indices_.push_back(2 * i);
		indices_.push_back(2 * i + 2);

		indices_.push_back(1); //bottom triangle
		indices_.push_back(2 * i + 1);
		indices_.push_back(2 * i + 3);

		indices_.push_back(2 * i); //right side triangle
		indices_.push_back(2 * i + 3);
		indices_.push_back(2 * i + 1);
		
		indices_.push_back(2 * i); //left side triangle
		indices_.push_back(2 * i + 2);
		indices_.push_back(2 * i + 3);
	}
	indices_.push_back(0); //top triangle
	indices_.push_back(2 * SEGMENTS);
	indices_.push_back(2);

	indices_.push_back(1); //bottom triangle
	indices_.push_back(2 * SEGMENTS + 1);
	indices_.push_back(3);

	indices_.push_back(2 * SEGMENTS); //right side triangle
	indices_.push_back(3);
	indices_.push_back(2*SEGMENTS + 1);

	indices_.push_back(2 * SEGMENTS); //left side triangle
	indices_.push_back(2);
	indices_.push_back(3);
}

void Cylinder::generateVertices()
{
	float theta = 0.0;
	float step = 2 * 3.14159265f / static_cast<float>(SEGMENTS);
	vertices_.reserve((2 * SEGMENTS + 2) * 8);
	vertices_.push_back(0.0f);  //0 top middle
	vertices_.push_back(size_.y );
	vertices_.push_back(0.0f);
	vertices_.push_back(color_.x);
	vertices_.push_back(color_.y);
	vertices_.push_back(color_.z);

	vertices_.push_back(1.0f);//Normal vec tmp TODO remove it
	vertices_.push_back(0.0f);
	vertices_.push_back(0.0f);


	vertices_.push_back(0.0f);
	vertices_.push_back(0.0f);
	vertices_.push_back(0.0f);  //1 bottom middle
	vertices_.push_back(-size_.y );
	vertices_.push_back(0.0f);
	vertices_.push_back(color_.x);
	vertices_.push_back(color_.y);
	vertices_.push_back(color_.z);

	vertices_.push_back(1.0f);//Normal vec tmp TODO remove it
	vertices_.push_back(0.0f);
	vertices_.push_back(0.0f);

	vertices_.push_back(0.0f);
	vertices_.push_back(0.0f);
	for (uint32_t i = 0; i < SEGMENTS; ++i)
	{
		vertices_.push_back(size_.x * cos(theta)); // top vertice
		vertices_.push_back(size_.y );
		vertices_.push_back(size_.z * sin(theta));
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);

		vertices_.push_back(1.0f);//Normal vec tmp TODO remove it
		vertices_.push_back(0.0f);//
		vertices_.push_back(0.0f);//

		vertices_.push_back(0.0f);
		vertices_.push_back(0.0f);

		vertices_.push_back(size_.x * cos(theta)); // bottom vertice
		vertices_.push_back(-size_.y);
		vertices_.push_back(size_.z * sin(theta));
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);

		vertices_.push_back(0.0f);
		vertices_.push_back(1.0f);//Normal vec tmp TODO remove it
		vertices_.push_back(0.0f);

		vertices_.push_back(0.0f);
		vertices_.push_back(0.0f);
		theta += step;
	}
}

void Cylinder::init()
{
	this->shader_ = ShaderProgram("CubeShader.vert", "CubeShader.frag");
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
}
