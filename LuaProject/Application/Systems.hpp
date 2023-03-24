#include "entt\entt.hpp"
#include "lua.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class System
{
protected:

public:
	virtual bool OnUpdate(entt::registry& registry, float delta) = 0;
};

class PoisonSystem : public System
{
	int m_lifetime;

public:

	PoisonSystem(int lifetime) : m_lifetime(lifetime) {}
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Health, Poison>();
		view.each([](Health& health, const Poison& poison) {
			health.Value -= poison.TickDamage;
			});

		return (--m_lifetime) <= 0;
	}
};

class CleanupSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta)
		final
	{
		auto view = registry.view < Health >();
		view.each([&](entt::entity entity, const Health&
			health) {
				if (health.Value <= 0.f)
				{
					registry.destroy(entity);
				}
			});
		return false;
	}
};

class InfoSystem : public System
{
	int m_updateCounter = 0;
public:
	InfoSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta)
		final
	{
		int count = registry.alive();
		auto healthView = registry.view<Health>();
		auto poisonView = registry.view<Poison>();
		printf("\n--Update %i--\n", ++m_updateCounter);
		printf("Living entities:\t%i\n", healthView.size());
		printf("Poisoned entities:\t%i\n", poisonView.size());
		return false;
	}
};

class MovementSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Moving>();
		view.each([&](entt::entity entity, const Moving& movement)
			{

			}
		);
	}
};

class Draw : public System
{
private:
	sf::RenderWindow* window;

public:
	Draw(sf::RenderWindow*& window) :window(window) {};
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Drawable>();
		view.each([&](entt::entity entity, const Drawable& shape)
			{
				window->clear();
				window->draw(shape.shape);
				window->display();
			}
		);
		return false;
	}
};