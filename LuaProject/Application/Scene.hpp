
#include "iostream"
#include <thread>
#include "entt\entt.hpp"
#include <Windows.h>
#include <string>
#include "lua.hpp"

class Scene
{
	entt::registry m_registry;

public:
	Scene();
	~Scene();

public:
	int GetEntityCount();

	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);
};