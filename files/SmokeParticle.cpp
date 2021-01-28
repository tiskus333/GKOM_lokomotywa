#include "SmokeParticle.h"

SmokeParticle::SmokeParticle(const glm::vec3& position, float maxLife): Composite(position), maxLifeTime(maxLife)
{
	c2.rotate({ 45,45,45 });
	addElement(c1);
	addElement(c2);
}

bool SmokeParticle::update(float deltaTime)
{
	lifeTime += deltaTime;

	int rot = rand() % 10;
	move({ 0,0.04 * (1.f - (lifeTime / maxLifeTime)),0 });
	rotate({ rot,rot,rot });
	scale(glm::vec3{ 1.01,1.01,1.01 });

	return lifeTime > maxLifeTime;
}

void SmokeParticle::scale(const glm::vec3& scale)
{
	for (auto& e : elements)
		e->scale(scale);
}
