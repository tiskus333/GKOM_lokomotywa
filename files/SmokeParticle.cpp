#include "SmokeParticle.h"

SmokeParticle::SmokeParticle(const glm::vec3& position, float maxLife): Composite(position), maxLifeTime(maxLife)
{
	//gwiazdki
	c1.rotate({ 45,0,0 });

	//chmurki
	/*c1.rotate({ 0,0,90 });
	c2.rotate({ 0,0,90 });
	c3.rotate({ 0,0,90 });*/

	addElement(c1);
	addElement(c2);
	//addElement(c3);
}

bool SmokeParticle::update(float deltaTime)
{
	lifeTime += deltaTime;

	int rot = rand() % 10;
	move({ 0,0.04 * (1.1f - (lifeTime / maxLifeTime)),0 });
	//rotate({ 0,30,0 });
	scale(glm::vec3{ 1.01,1.01,1.01 });

	return lifeTime > maxLifeTime;
}

void SmokeParticle::scale(const glm::vec3& scale)
{
	for (auto& e : elements)
		e->scale(scale);
}
