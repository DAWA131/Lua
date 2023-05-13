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

class MovementSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Drawable, Moving, Player>(entt::exclude<Jumping>);
		view.each([](Drawable& shape, const Moving& moving, const Player& player)
			{
				if (moving.setPos)
					shape.sprite.setPosition(moving.Xspeed, moving.Yspeed);
				else
					shape.sprite.move(moving.Xspeed, moving.Yspeed);
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
				if (jump.ySpeed != 0.f)
				{
					jump.ySpeed = jump.ySpeed + 0.05;
					shape.sprite.move(jump.xSpeed, jump.ySpeed);
				}
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

class screenChangeSystem : public System
{
	lua_State* L;
	int WINDOWHEIGHT;
public:
	screenChangeSystem(lua_State* L, int screenHeight) : L(L), WINDOWHEIGHT(screenHeight){}
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto View = registry.view<Drawable, Player>();
		View.each([&](entt::entity entity, Drawable& sprite, const Player& player)
		{
			if (sprite.sprite.getPosition().y < 0 || sprite.sprite.getPosition().y > WINDOWHEIGHT)
			{
				lua_pushnumber(L, sprite.sprite.getPosition().y);
				lua_setglobal(L, "playerY");
				lua_pushnumber(L, sprite.sprite.getPosition().x);
				lua_setglobal(L, "playerX");
				if (luaL_dofile(L, "luaScripts/screenHandler.lua") != LUA_OK)
				{
					std::cout << "Error Lua file not found!\n";
				}
			}
		});
		return false;
	}
};