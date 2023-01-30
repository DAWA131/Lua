#include "iostream"
#include <thread>
#include <Windows.h>
#include <string>
#include "lua.hpp"


void luaStackReader(lua_State* L)
{
	int start = lua_gettop(L);
	int stackNum = -1;
	int i = 0;
	std::cout << "------ Stack Start ------\n";
	for (; i < start; i++, stackNum--)
	{
		std::cout << start - i << " | " << lua_typename(L, lua_type(L, stackNum)) << " |	 " ;

		if (true)
		{

		}

		std::cout << stackNum << "\n";
	}
	std::cout << "------ Stack End ------\n";
}

void master(lua_State* L)
{
	lua_pushnumber(L, 3.14159f);
	lua_setglobal(L, "Pi");
	lua_pushnumber(L, 1.41421f);
	lua_setglobal(L, "SqrtOfTwo");
	lua_pushnumber(L, 1.61803f);
	lua_setglobal(L, "Phi");
	lua_pushnumber(L, 2.71828f);
	lua_setglobal(L, "Euler");
	lua_pushnumber(L, 0.56714f);
	lua_setglobal(L, "Omega");
	lua_pushnumber(L, 0.83462f);
	lua_setglobal(L, "Gauss");

	if (luaL_dofile(L, "lua/M2main.cpp")) std::cout << "CRASHED MOTHERFUCKER\n";; //lua stack will grow when error, luatostring to see then pop

	std::cout << "Before: " << lua_gettop(L) << std::endl;
	auto ret luaL_dofile(L, "lua/fail.lua");
	std::cout << "After: " << lua_gettop(L) << std::endl;
	std::string luaString = lua_tostring(L, -1);
	lua_pop(L, -1);
	std::cout << "After Pop: " << lua_gettop(L) << std::endl;

	auto ret2 = luaL_dofile(L, "lua/fizz.lua");
	std::cout << "After working file: " << lua_gettop(L) << std::endl;


	lua_pushboolean(L, false);
	lua_pushnil(L);
	lua_pushstring(L, "Hello!");
	lua_pushnumber(L, 3.14f);
	lua_pushvalue(L, -2);
	luaStackReader(L);

	std::cout << luaString;

	lua_getglobal(L, "dino_species");
	std::cout << "[C++] dino_species: " << lua_tostring(L, -1) << "\n";
	lua_pop(L, 1);

	lua_getglobal(L, "dino_name");
	std::cout << "[C++] dino_name: " << lua_tostring(L, -1) << "\n";
	lua_pop(L, 1);

	lua_getglobal(L, "dino_wings");
	std::cout << "[C++] has wings?: " << lua_toboolean(L, -1) << "\n";
	lua_pop(L, 1);

	lua_getglobal(L, "dino_getnoise");
	lua_pushnumber(L, 7);
	lua_pcall(L, 1, 1, 0);
	std::cout << "[C++] dino_noise: " << lua_tostring(L, -1) << "\n";
	lua_pop(L, 1);

	lua_getfield(L, -1, "name");
	std::cout << "name: " << lua_tostring(L, -1) << "\n";
	lua_pop(L, 1);
	lua_getfield(L, -1, "getnoise");
	lua_pushnumber(L, 7);
	lua_pcall(L, 1, 1, 0);
	std::cout << "noise: " << lua_tostring(L, -1) << "\n";
	lua_pop(L, 1);
	//others goes here
	lua_pop(L, 1);
}