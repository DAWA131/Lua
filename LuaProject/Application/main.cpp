#include "iostream"
#include <thread>
#include "entt\entt.hpp"
#include <Windows.h>
#include <string>
#include "lua.hpp"
//#include "lua/M2main.cpp"

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

int main()
{

	entt::registry reg;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";

	std::thread consoleThread(luaThreadLoop, L);

	std::cout << "Before: " << lua_gettop(L) << std::endl;
	luaL_dofile(L, "lua/fail.lua");
	std::cout << "After: " << lua_gettop(L) << std::endl;
	std::string luaString = lua_tostring(L, -1);
	
	std::cout << luaString;

	while (true)
	{
		//run game here
	}

	return 0;
}