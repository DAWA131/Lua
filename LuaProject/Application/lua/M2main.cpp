#include "iostream"
#include <thread>
#include <Windows.h>
#include <string>
#include "lua.hpp"

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

	if (luaL_dofile(L, "lua/M2main.cpp")) std::cout << "CRASHED MOTHERFUCKER\n";;
}