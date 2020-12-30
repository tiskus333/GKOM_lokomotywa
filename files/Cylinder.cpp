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
	/*std::vector<float>vertices;
	std::vector<float>normals;
	std::vector<float>texCoords;

	// get unit circle vectors on XY-plane
	std::vector<float> unitVertices = getUnitCircleVertices();

	// put side vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -size_.z / 2.0f + i * size_.z;           // z value; -h/2 to h/2
		float t = 1.0f - i;                              // vertical tex coord; 1 to 0

		for (int j = 0, k = 0; j <= SEGMENTS; ++j, k += 3)
		{
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			float uz = unitVertices[k + 2];
			// position vector
			vertices.push_back(ux * size_.x);             // vx
			vertices.push_back(uy * size_.y);             // vy
			vertices.push_back(h);                       // vz
			// normal vector
			normals.push_back(ux);                       // nx
			normals.push_back(uy);                       // ny
			normals.push_back(uz);                       // nz
			// texture coordinate
			texCoords.push_back((float)j / SEGMENTS); // s
			texCoords.push_back(t);                      // t
		}
	}

	// the starting index for the base/top surface
	//NOTE: it is used for generating indices later
	int baseCenterIndex = (int)vertices.size() / 3;
	int topCenterIndex = baseCenterIndex + SEGMENTS + 1; // include center vertex

	// put base and top vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -size_.z / 2.0f + i * size_.z;           // z value; -h/2 to h/2
		float nz = -1 + i * 2;                           // z value of normal; -1 to 1

		// center point
		vertices.push_back(0);     vertices.push_back(0);     vertices.push_back(h);
		normals.push_back(0);      normals.push_back(0);      normals.push_back(nz);
		texCoords.push_back(0.5f); texCoords.push_back(0.5f);

		for (int j = 0, k = 0; j < SEGMENTS; ++j, k += 3)
		{
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			// position vector
			vertices.push_back(ux * size_.x);             // vx
			vertices.push_back(uy * size_.y);             // vy
			vertices.push_back(h);                       // vz
			// normal vector
			normals.push_back(0);                        // nx
			normals.push_back(0);                        // ny
			normals.push_back(nz);                       // nz
			// texture coordinate
			texCoords.push_back(-ux * 0.5f + 0.5f);      // s
			texCoords.push_back(-uy * 0.5f + 0.5f);      // t
		}
	}
	int k1 = 0;                         // 1st vertex index at base
	int k2 = SEGMENTS + 1;           // 1st vertex index at top

	for (int i = 0, j=0; i < vertices.size()/3; i+= 3, j+=2)
	{
		vertices_.push_back(vertices[i]);
		vertices_.push_back(vertices[i + 1]);
		vertices_.push_back(vertices[i + 2]);

		vertices_.push_back(color_.x);
		vertices_.push_back(color_.y);
		vertices_.push_back(color_.z);

		vertices_.push_back(normals[i]);
		vertices_.push_back(normals[i + 1]);
		vertices_.push_back(normals[i + 2]);

		vertices_.push_back(texCoords[j]);
		vertices_.push_back(texCoords[j + 1]);

	}

	// indices for the side surface
	for (int i = 0; i < SEGMENTS; ++i, ++k1, ++k2)
	{
		// 2 triangles per sector
		// k1 => k1+1 => k2
		indices_.push_back(k1);
		indices_.push_back(k1 + 1);
		indices_.push_back(k2);

		// k2 => k1+1 => k2+1
		indices_.push_back(k2);
		indices_.push_back(k1 + 1);
		indices_.push_back(k2 + 1);
	}

	// indices for the base surface
	//NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
	//      please see the previous code snippet
	for (int i = 0, k = baseCenterIndex + 1; i < SEGMENTS; ++i, ++k)
	{
		if (i < SEGMENTS - 1)
		{
			indices_.push_back(baseCenterIndex);
			indices_.push_back(k + 1);
			indices_.push_back(k);
		}
		else // last triangle
		{
			indices_.push_back(baseCenterIndex);
			indices_.push_back(baseCenterIndex + 1);
			indices_.push_back(k);
		}
	}

	// indices for the top surface
	for (int i = 0, k = topCenterIndex + 1; i < SEGMENTS; ++i, ++k)
	{
		if (i < SEGMENTS - 1)
		{
			indices_.push_back(topCenterIndex);
			indices_.push_back(k);
			indices_.push_back(k + 1);
		}
		else // last triangle
		{
			indices_.push_back(topCenterIndex);
			indices_.push_back(k);
			indices_.push_back(topCenterIndex + 1);
		}
	}*/
	float theta = 0.0;
	float step = 2 * 3.14159265f / static_cast<float>(SEGMENTS);
	std::vector<float> normals = getUnitCircleVertices();
	vertices_.reserve((2 * SEGMENTS + 2) * 8);

	//lids
	vertices_.push_back(0.0f);  //0 top middle
	vertices_.push_back(size_.y);
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
	vertices_.push_back(-size_.y);
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
			vertices_.push_back(size_.x * cos(theta));
			vertices_.push_back(y_mul*size_.y );
			vertices_.push_back(size_.z * sin(theta));
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

void Cylinder::init()
{
	this->shader_ = ShaderProgram("CubeShader.vert", "CubeShader.frag");
	generateVertices();
	generateIndices();
	Shape::bindBuffers();
}

std::vector<float> Cylinder::getUnitCircleVertices()
{
	const float PI = 3.1415926f;
	float sectorStep = 2 * PI / SEGMENTS;
	float sectorAngle;  // radian

	std::vector<float> unitCircleVertices;
	for (int i = 0; i <= SEGMENTS; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle));		// x
		unitCircleVertices.push_back(sin(sectorAngle));					// y
		unitCircleVertices.push_back(0);     // z
	}
	return unitCircleVertices;
}
