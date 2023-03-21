#pragma once
#include "entt\entt.hpp"

struct Health
{
	float Value;
};

struct Poison
{
	float TickDamage;
};

class System
{
public:
	virtual bool OnUpdate(entt::registry& registry, float dt) = 0;
};

class PoisonSystem : public System
{
	int m_lifetime;
public:
	PoisonSystem(int lifetime) : m_lifetime(lifetime) {}
	bool OnUpdate(entt::registry& registry, float delta)
	{
		auto view = registry.view < Health, Poison >();
		view.each([](Health& health, const Poison& poison) {
			health.Value -= poison.TickDamage;
			});

		return (--m_lifetime) <= 0;
	}
};

class Scene
{
	entt::registry m_registry;

	std::vector<System*> m_systems;
public:
	Scene();
	~Scene();

	int getEntityCount();
	int createEntity();

	bool isEntity(int entity);
	void removeEntity(int entity);

	//Components

	template<typename ...Args>
	bool hasComponents(int entity);

	template<typename T>
	T& getComponents(int entity);

	template<typename T>
	void setComponent(int entity, const T& component);

	template<typename T, typename ...Args>
	void setComponent(int entity, Args...args);

	template<typename T>
	void removeComponent(int entity);

	//system

	template < typename T, typename ...Args >
	void CreateSystem(Args ... args);
	
	void UpdateSystems(float delta);
};