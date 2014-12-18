#include "UtH/Engine/Scene.hpp"
#include <UtH/Engine/Sprite.hpp>

#include <UtH/Platform/Debug.hpp>
#include <Box2D/Dynamics/b2World.h>

using namespace uth;

Scene::Scene()
{

}

Scene::~Scene()
{

}

void uth::Scene::Update(float dt)
{
	Object::Update(dt);
}

void uth::Scene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Object::Draw(target, attributes);
}

PhysicsWorld* uth::Scene::GetPhysicsWorld()
{
    return nullptr;
}
