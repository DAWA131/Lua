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
	//std::thread consoleThread(luaThreadLoop, L);
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(768, 816), "JumpKing ripoff");

	Scene scene;
	Scene::lua_openscene(L, &scene);
	//scene.CreateSystem<CleanupSystem>();
	//scene.CreateSystem<PoisonSystem>(100);
	//scene.CreateSystem<InfoSystem>();
	scene.CreateSystem<MovementSystem>();
	scene.CreateSystem<JumpSystem>();
	//scene.CreateSystem<EdgeSystem>();
	scene.CreateSystem<CollisionSystem>(L, false);
	scene.CreateSystem<Draw>(window);

	luaL_dofile(L, "luaScripts/setup.lua");
	luaL_dofile(L, "luaScripts/fileReader.lua");
	luaL_dofile(L, "luaScripts/replaceChar.lua");
	luaL_dofile(L, "luaScripts/maploader.lua");
	luaL_dofile(L, "luaScripts/newScreen.lua");
	dumpError(L);

	while (window->isOpen())
	{
		if (window->getSize().x != 768 || window->getSize().y != 816) {
			// Reset the window size to the initial size
			window->setSize(sf::Vector2u(768, 816));
		}

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.key.code == sf::Mouse::Left)
			{
				lua_pushinteger(L, (int)((sf::Mouse::getPosition().x - 8) - window->getPosition().x));
				lua_setglobal(L, "mouseX");

				lua_pushinteger(L, (int)((sf::Mouse::getPosition().y - 31) - window->getPosition().y));
				lua_setglobal(L, "mouseY");

				luaL_dofile(L, "luaScripts/mapEditor.lua");


				std::cout << "X: " << (int)((sf::Mouse::getPosition().x-8) - window->getPosition().x)/48 << " Y: " << (int)((sf::Mouse::getPosition().y-31) - window->getPosition().y)/48 << "\n";
			}
			if (event.type == sf::Event::KeyPressed)
			{
				lua_pushinteger(L, event.key.code);
				lua_setglobal(L, "key");
				lua_pushboolean(L, true);
				lua_setglobal(L, "moving");
				luaL_dofile(L, "luaScripts/keyInput.lua");
			}
			else if (event.type == sf::Event::KeyReleased)
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