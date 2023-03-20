#pragma once
#include "entt\entt.hpp"

class Scene
{
	entt::registry m_registry;

public:
	Scene();
	~Scene();

	int getEntityCount();
	int createEntity();


	bool isEntity(int entity);
	void removeEntity(int entity);



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


};

class system
{
public:
	system();
	~system();

	virtual void onUpdate(entt::registry& registry, float delta) = 0;
private:

};
