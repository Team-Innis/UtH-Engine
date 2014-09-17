#include <UtH/Engine/Object.hpp>

uth::Object::Object(Object* p)
	: parent(p),
	inWorld(false)
{

}

uth::Object::~Object()
{

}

void uth::Object::Update(float dt)
{

}

void uth::Object::Draw(RenderTarget& target)
{

}

