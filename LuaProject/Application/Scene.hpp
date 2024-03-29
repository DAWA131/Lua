#include "entt\entt.hpp"
#include "lua.hpp"
#include "Components.hpp"
#include "Systems.hpp"
#include <iostream>

class Scene
{
	entt::registry m_registry;
	std::vector<System*> m_systems;

public:
	Scene();
	~Scene();

	static void lua_openscene(lua_State* L, Scene* scene);

	int GetEntityCount();
	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);

	//Components
	template<typename...Args>
	bool HasComponents(int entity);
	template<typename T>
	T& GetComponent(int entity);
	template<typename T>
	void SetComponent(int entity, const T&);
	template<typename T, typename...Args>
	void SetComponent(int entity, Args...args);
	template<typename T>
	void RemoveComponent(int entity);

	//System
	template<typename T, typename...Args>
	void CreateSystem(Args... args);
	void UpdateSystems(float delta);

private:
	static Scene* lua_GetSceneUpValue(lua_State* L);
	static int lua_GetEntityCount(lua_State* L);
	static int lua_CreateEntity(lua_State* L);
	static int lua_IsEntity(lua_State* L);
	static int lua_RemoveEntity(lua_State* L);
	static int lua_HasComponent(lua_State* L);
	static int lua_GetComponent(lua_State* L);
	static int lua_SetComponent(lua_State* L);
	static int lua_RemoveComponent(lua_State* L);

	static int lua_SetPosition(lua_State* L);
	static int lua_RemoveTile(lua_State* L);
};

template<typename ...Args>
inline bool Scene::HasComponents(int entity)
{
	return m_registry.all_of<Args...>((entt::entity)entity);
}

template<typename T>
inline T& Scene::GetComponent(int entity)
{
	return m_registry.get<T>((entt::entity)entity);
}

template<typename T>
inline void Scene::SetComponent(int entity, const T& component)
{
	m_registry.emplace_or_replace<T>((entt::entity)entity, component);
}

template<typename T, typename ...Args>
inline void Scene::SetComponent(int entity, Args ...args)
{
	m_registry.emplace_or_replace<T>((entt::entity)entity, args...);
}

template<typename T>
inline void Scene::RemoveComponent(int entity)
{
	m_registry.remove<T>((entt::entity)entity);
}

template<typename T, typename ...Args>
inline void Scene::CreateSystem(Args ...args)
{
	this->m_systems.emplace_back(new T(args...));
}