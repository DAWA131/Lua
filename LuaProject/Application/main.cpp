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

void dumpStack(lua_State* L)
{
	int size = lua_gettop(L);
	std::cout << " " << std::string(11, '-');
	std::cout << " STACK BEGIN ";
	std::cout << " " << std::string(11, '-');

	for (int i = size; i > 0; i--)
	{
		int type = lua_type(L, i);
		std::string typeName = lua_typename(L, type);
		std::string value;

		if (type == LUA_TSTRING)
		{
			value = "\"";
			value += lua_tostring(L, i);

			if (value.size() > 11)
			{
				value.resize(9);
				value += " . . ";
			}

			value += "\"";
		}
		else if (type == LUA_TBOOLEAN)
		{
			value = lua_toboolean(L, i) ? "true" : "false";
		}
		else if (type == LUA_TNIL)
		{
			value = "nil";
		}
		else if (lua_isnumber(L, i))
		{
			value = std::to_string(lua_tonumber(L, i));
		}
		else if (lua_isstring(L, i))
		{
			value = lua_tostring(L, i);
		}

		std::cout << std::setw(3) << i << " | ";
		std::cout << typeName << std::setw(25 - typeName.size()) << value;
		std::cout << std::setw(5 - typeName.size() - value.size()) << " | ";
		std::cout << std::setw(2) << -(size - i + 1);
		std::cout << std::endl;
	}

	std::cout << " " << std::string(12, '-');
	std::cout << " STACK END ";
	std::cout << std::string(12, '-') << std::endl;
}

int main()
{
	entt::registry registry;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";

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

	Scene scene;
	scene.CreateSystem<PoisonSystem>(5);
	scene.UpdateSystems(1);

	std::thread consoleThread(luaThreadLoop, L);

	while (true)
	{

	}

	return 0;
}