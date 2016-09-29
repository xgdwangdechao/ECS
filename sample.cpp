#include <iostream>

#include "Entity.h"

using namespace ECS;

struct Position
{
	Position(float x, float y) : x(x), y(y) {}
	Position() {}

	float x;
	float y;
};

struct Rotation
{
	Rotation(float angle) : angle(angle) {}
	Rotation() {}

	float angle;
};

class TestSystem : public EntitySystem
{
	virtual ~TestSystem() {}

	virtual void tick(class World* world, float deltaTime)
	{
		world->each<Position, Rotation>([&](Entity* ent, auto pos, auto rot) {
			pos->x += deltaTime;
			pos->y += deltaTime;
			rot->angle += deltaTime * 2;
		});
	}
};

int main(int argc, char** argv)
{
	std::cout << "EntityComponentSystem Test" << std::endl
		<< "==========================" << std::endl;

	World world;

	world.registerSystem(new TestSystem());

	Entity* ent = world.create();
	auto pos = ent->assign<Position>(0.f, 0.f);
	auto rot = ent->assign<Rotation>(0.f);

	std::cout << "Initial values: position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;

	world.tick(10.f);

	std::cout << "After tick(10): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;

	std::cout << "Press any key to exit..." << std::endl;
	std::getchar();

	return 0;
}