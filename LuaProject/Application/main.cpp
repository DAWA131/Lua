#define NOMINMAX
#include "iostream"
#include <iomanip>
#include <thread>
#include "entt\entt.hpp"
#include <Windows.h>
#include <string>
#include "lua.hpp"
#include <stdlib.h>
#include <time.h>
#include "Scene.hpp"


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


//#ifdef _DEBUG
//#pragma comment(lib, "sfml-window-d.lib")
//#pragma comment(lib, "sfml-system-d.lib")
//#pragma comment(lib, "sfml-graphics-d.lib")
//#else
//#pragma comment(lib, "sfml-window.lib")
//#pragma comment(lib, "sfml-system.lib")
//#pragma comment(lib, "sfml-graphics.lib")
//#endif

void dumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "LUA Error: " << lua_tostring(L, -1) << "\n";
		lua_pop(L, 1);
	}
}

void luaThreadLoop(lua_State* L)
{
	std::string input;
	while (GetConsoleWindow())
	{
		std::cout << "-> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK)
		{
			dumpError(L);
		}
	}
}

std::string GetValueString(lua_State* L, int i)
{
	switch (lua_type(L, i))
	{
	case LUA_TNIL: return "nil";
	case LUA_TBOOLEAN:
		return lua_toboolean(L, i) ? "true" : "false";
	case LUA_TNUMBER: return std::to_string(lua_tonumber(L, i));
	case LUA_TSTRING: return lua_tostring(L, i);
	default: return "";
	}
}

void dumpStack(lua_State* L)
{
	int size = lua_gettop(L);

	std::cout << "--- STACK BEGIN ---" << std::endl;
	for (int i = size; i > 0; i--)
	{
		std::cout << i
			<< "\t"
			<< lua_typename(L, lua_type(L, i))
			<< "\t\t" << GetValueString(L, i)
			<< std::endl;
	}
	std::cout << "---- STACK END ----" << std::endl;
}

int main()
{
	entt::registry registry;
	lua_State* L = luaL_newstate();
	std::thread consoleThread(luaThreadLoop, L);
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 800), "JumpKing ripoff");

	Scene scene;
	Scene::lua_openscene(L, &scene);
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	//scene.CreateSystem<CleanupSystem>();
	//scene.CreateSystem<PoisonSystem>(100);
	//scene.CreateSystem<InfoSystem>();
	scene.CreateSystem<MovementSystem>();
	scene.CreateSystem<JumpSystem>();
	scene.CreateSystem<CollisionSystem>();
	scene.CreateSystem<Draw>(window);

	luaL_dofile(L, "luaScripts/setup.lua");

	/*
	//POISON example
	//srand(time(NULL));
	//for (int i = 0; i < 100; i++)
	//{
	//	auto entity = registry.create();
	//	registry.emplace<Health>(entity, 100.f);
	//	float tickDamage = rand() % 10 + 1;
	//	registry.emplace<Poison>(entity, tickDamage);
	//}

	//int iterations = 0;
	//while (registry.alive())
	//{
	//	//Poison system
	//	{
	//		auto view = registry.view<Health, Poison>();
	//		view.each([](Health& health, const Poison& poison)
	//			{
	//				health.Value -= poison.TickDamage;
	//			});
	//	}

	//	//Cleanup system
	//	{
	//		auto view = registry.view<Health>();
	//		view.each([&](entt::entity entity, const Health& health)
	//			{
	//				if (health.Value <= 0.f)
	//				{
	//					registry.destroy(entity);
	//				}
	//			});
	//	}

	//	//Cure system
	//	{
	//		float cure = rand() % 20;
	//		if (cure == 0)
	//		{
	//			auto view = registry.view<Poison>();
	//			view.each([&](entt::entity entity, const Poison& poison)
	//				{
	//					registry.remove<Poison>(entity);
	//					//std::cout << "Cured\n";
	//				});
	//		}
	//	}

	//	//Spawn poison system
	//	{
	//		auto view = registry.view<Health>(entt::exclude<Poison>);
	//		view.each([&](entt::entity entity, const Health& health)
	//			{
	//				if ((rand() % 4) == 0)
	//				{
	//					float damage = rand() % 11 + 1;
	//					registry.emplace<Poison>(entity, damage);
	//					//std::cout << "Poisoned entity " << (int)entity << std::endl;
	//				}
	//			});
	//	}

	//	iterations++;
	//	std::cout << "Iteration " << iterations << ", entities alive: " << registry.alive() << std::endl;
	//}
	*/
	

	while (window->isOpen())
	{
		if (window->getSize().x != 800 || window->getSize().y != 800) {
			window->setSize(sf::Vector2u(800, 800));
		}

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::KeyPressed)
			{
				lua_pushinteger(L, event.key.code);
				lua_setglobal(L, "key");
				lua_pushboolean(L, true);
				lua_setglobal(L, "moving");
				luaL_dofile(L, "luaScripts/keyInput.lua");
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				lua_pushinteger(L, event.key.code);
				lua_setglobal(L, "key");
				lua_pushboolean(L, false);
				lua_setglobal(L, "moving");
				luaL_dofile(L, "luaScripts/keyInput.lua");
			}
			dumpError(L);
		}
		scene.UpdateSystems(1);
	}

	delete window;
	return 0;




	for (int i = 0; i < 100; i++){}

	while (scene.GetEntityCount() != 0)
	{
		scene.UpdateSystems(1);	
	}


	while (true)
	{
	}

	return 0;
}