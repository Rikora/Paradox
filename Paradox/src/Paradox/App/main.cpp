#include <entt/entity/registry.hpp>
#include <cstdint>

struct position
{
	float x;
	float y;
};

struct velocity
{
	float dx;
	float dy;
};

void update(entt::registry<unsigned int> &registry) 
{
	auto view = registry.view<position, velocity>();

	for (auto entity : view) 
	{
		auto &vel = view.get<velocity>(entity);

		vel.dx = 0.;
		vel.dy = 0.;
	}
}

int main()
{
	entt::registry<unsigned int> registry;
	std::uint64_t dt = 16;

	for (auto i = 0; i < 10; ++i)
	{
		auto entity = registry.create();
		registry.assign<position>(entity, i * 1.f, i * 1.f);

		if (i % 2 == 0)
		{
			registry.assign<velocity>(entity, i * .1f, i * .1f);
		}
	}

	return 0;
}
