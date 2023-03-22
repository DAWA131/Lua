#include <cstring>

struct Behaviour
{
	char Path[64];
	int LuaRef;

	Behaviour(const char* path, int luaRef) : LuaRef(luaRef)
	{
		memset(Path, '\0', 64);
		strcpy_s(Path, path);
	}
};