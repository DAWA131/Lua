
#include "Scene.hpp"
int Scene::getEntityCount()
{
    return this->m_registry.alive();
}

int Scene::createEntity()
{
    return (int)this->m_registry.create();
}

bool Scene::isEntity(int entity)
{
    return this->m_registry.valid((entt::entity)entity);
}

void Scene::removeEntity(int entity)
{
    this->m_registry.destroy((entt::entity)entity);
}

