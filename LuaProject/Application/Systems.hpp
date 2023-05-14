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
		auto view = registry.view<Drawable, Moving, Player>(entt::exclude<Stopping>);
		view.each([](Drawable& shape, Moving& moving, const Player& player)
			{
				if (moving.setPos)
					shape.sprite.setPosition(moving.xSpeed, moving.ySpeed);
				else
					shape.sprite.move(moving.xSpeed, moving.ySpeed);
			}
		);
		return false;
	}
};

class JumpingSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta)
		final
	{
		auto view = registry.view<Drawable, Jumping, Player>();
		view.each([](Drawable& shape, const Jumping& jump, const Player& player)
			{
				shape.sprite.move(jump.direction, jump.height);
			}
		);
		return false;
	}
};

class CollisionSystem : public System
{
	lua_State* L;
	bool falling;

public:
	CollisionSystem(lua_State* L, bool collide) : L(L), falling(falling) {}
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		falling = true;
		lua_pushboolean(L, falling);
		lua_setglobal(L, "falling");

		auto view = registry.view<Drawable, Collidable>();
		view.each([&](Drawable& platforms, const Collidable& collidable)
			{
				auto playerView = registry.view<Drawable, Player>();
				playerView.each([&](entt::entity entity, Drawable& sprite, const Player& player)
					{
						if (sprite.sprite.getGlobalBounds().intersects(platforms.sprite.getGlobalBounds()) &&
							sprite.sprite.getPosition() != platforms.sprite.getPosition())
						{
							lua_pushnumber(L, sprite.sprite.getPosition().x);
							lua_setglobal(L, "playerX");
							lua_pushnumber(L, sprite.sprite.getPosition().y);
							lua_setglobal(L, "playerY");

							lua_pushnumber(L, platforms.sprite.getPosition().x);
							lua_setglobal(L, "platformX");
							lua_pushnumber(L, platforms.sprite.getPosition().y);
							lua_setglobal(L, "platformY");

							if (luaL_dofile(L, "luaScripts/playerCollide.lua") != LUA_OK)
								std::cout << "Error\n";
						}
					});
			});

		if (luaL_dofile(L, "luaScripts/aftercheck.lua") != LUA_OK)
			std::cout << "Error\n";
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