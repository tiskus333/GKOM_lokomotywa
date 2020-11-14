#include "Cuboid.h"

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size)
{
	this->position_ = position;
	generateVertices();
}

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size, glm::vec4 color = glm::vec4(0.0,0.0,0.0,-1.0)) : size_(size)
{
	
	this->color_ = color;
	generateVertices();
}

Cuboid::Cuboid(glm::vec3 position, glm::vec3 size, std::string texture_path = "") : size_(size)
{
	
	this->texture_path_ = texture_path;
	generateVertices();
}

//adding vertivces counterclockwise from nearest to furthest
void Cuboid::generateVertices()
{
	vertices_.push_back(position_.x - size_.x / 2); // 0
	vertices_.push_back(position_.y - size_.y / 2); 
	vertices_.push_back(position_.z - size_.z / 2);

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(0.0);
	vertices_.push_back(0.0);


	vertices_.push_back(position_.x + size_.x / 2); // 1
	vertices_.push_back(position_.y - size_.y / 2); 
	vertices_.push_back(position_.z - size_.z / 2); 

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(1.0);
	vertices_.push_back(0.0);

	vertices_.push_back(position_.x + size_.x / 2); // 2
	vertices_.push_back(position_.y + size_.y / 2);
	vertices_.push_back(position_.z - size_.z / 2);

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(1.0);
	vertices_.push_back(1.0);

	vertices_.push_back(position_.x - size_.x / 2); // 3
	vertices_.push_back(position_.y + size_.y / 2);
	vertices_.push_back(position_.z - size_.z / 2);

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(0.0);
	vertices_.push_back(1.0);

	vertices_.push_back(position_.x - size_.x / 2); // 4
	vertices_.push_back(position_.y - size_.y / 2);
	vertices_.push_back(position_.z - size_.z / 2);

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(1.0);
	vertices_.push_back(0.0);

	vertices_.push_back(position_.x + size_.x / 2); // 5
	vertices_.push_back(position_.y - size_.y / 2);
	vertices_.push_back(position_.z - size_.z / 2);

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(0.0);
	vertices_.push_back(0.0);

	vertices_.push_back(position_.x + size_.x / 2); // 6
	vertices_.push_back(position_.y + size_.y / 2);
	vertices_.push_back(position_.z - size_.z / 2);

	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(0.0);
	vertices_.push_back(1.0);

	vertices_.push_back(position_.x - size_.x / 2); // 7
	vertices_.push_back(position_.y + size_.y / 2);
	vertices_.push_back(position_.z - size_.z / 2);

	
	if (color_.w != -1)
	{
		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);
		vertices_.push_back(color_.w);
	}
	else 
		for (int i = 0; i < 4; ++i)
			vertices_.push_back(0.0);

	vertices_.push_back(1.0);
	vertices_.push_back(1.0);

}

