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
		auto view = registry.view<Drawable, Moving, Player>(entt::exclude<Jumping>);
		view.each([](Drawable& shape, const Moving& moving, const Player& player)
			{
				shape.sprite.move(moving.Xspeed, 0.f);
			}
		);
		return false;
	}
};

class JumpSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Drawable, Jumping, Player>();
		view.each([&](entt::entity entity, Drawable& shape, Jumping& jump, const Player& player)
			{
				jump.ySpeed = jump.ySpeed + 0.05;
				shape.sprite.move(0.f, jump.ySpeed);
			}
		);
		return false;
	}
};

class EdgeSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Drawable, Player>();
		view.each([](Drawable& shape, const Player& player)
			{
				if (shape.sprite.getPosition().x < 0)
				shape.sprite.setPosition(0.f, shape.sprite.getPosition().y);
				else if (shape.sprite.getPosition().x > 750)
					shape.sprite.setPosition(750, shape.sprite.getPosition().y);
				
				if (shape.sprite.getPosition().y > 800)
					shape.sprite.setPosition(shape.sprite.getPosition().x, 800);
			}
		);

		return false;
	}
};

class CollisionSystem : public System
{
	lua_State* L;

public:
	CollisionSystem(lua_State* L) : L(L) {}
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Drawable, Collidable>();
		view.each([&](Drawable& platforms, const Collidable& collidable)
			{
				auto playerView = registry.view<Drawable, Player>();
				playerView.each([&](entt::entity entity, Drawable& sprite, const Player& player)
					{
						if (sprite.sprite.getGlobalBounds().intersects(platforms.sprite.getGlobalBounds()))
						{
							luaL_dofile(L, "playerCollide.lua");

							if (platforms.sprite.getPosition().y > sprite.sprite.getPosition().y)
								registry.remove<Jumping>(entity);

							if (platforms.sprite.getPosition().x > sprite.sprite.getPosition().x)
								sprite.sprite.setPosition(platforms.sprite.getPosition().x - platforms.sprite.getGlobalBounds().width, sprite.sprite.getPosition().y);
						}
					});
			});

		return false;
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
		window->clear();
		auto view = registry.view<Drawable>();
		view.each([&](entt::entity entity, const Drawable& shape)
			{
				window->draw(shape.sprite);
			}
		);
		window->display();
		return false;
	}
};