#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Scene.h"

class Object
{
protected:
	Object* parent_ = nullptr;
	glm::vec3 position_;
	/* used to rotate around center */
	glm::mat4 static_rotation_matrix_;
	/* used to rotate around point */
	glm::mat4 dynamic_rotation_matrix_;

public:
	/* move object by the given vector */
	void move(const glm::vec3& displacement);

	/* rotate object by the given angle (X-degrees, Y-degrees, Z-degrees) around the specified point */
	void rotate(const glm::vec3& angle, const glm::vec3& point);

	/* rotate object by given angle (X-degrees, Y-degrees, Z-degrees) around it's center */
	void rotate(const glm::vec3& angle);

	/* set object position to a given point*/
	void setPosition(const glm::vec3& position);

	/* set object's parent */
	void setParent(Object* parent);

};

