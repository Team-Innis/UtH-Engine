#include <UtH/Engine/GameObject.hpp>

using namespace uth;

GameObject::GameObject()
{
	transform.parent = this;
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* component)
{
	if(component->GetDynamic())
		updateComponents.push_back(component);
	if(component->GetDrawable())
		drawComponents.push_back(component);

	component->parent = this;
}

Component* GameObject::GetComponent(const std::string name)
{
	for (int i = 0; i < updateComponents.size(); ++i)
	{
		if (updateComponents.at(i)->GetName() == name)
		{
			return updateComponents.at(i);
		}
	}

	for (int i = 0; i < drawComponents.size(); ++i)
	{
		if (drawComponents.at(i)->GetName() == name)
		{
			return drawComponents.at(i);
		}
	}

	return NULL;
}

void GameObject::RemoveComponent(Component* component)
{
	for(int i = 0; i < updateComponents.size(); ++i)
	{
		if(updateComponents.at(i) == component)
		{
			updateComponents.erase(updateComponents.begin() + i);
		}
	}

	for(int i = 0; i < drawComponents.size(); ++i)
	{
		if(drawComponents.at(i) == component)
		{
			drawComponents.erase(drawComponents.begin() + i);
		}
	}
}

void GameObject::RemoveComponent(std::string name)
{
	for(int i = 0; i < updateComponents.size(); ++i)
	{
		if(updateComponents.at(i)->GetName() == name)
		{
			delete updateComponents.at(i);
			updateComponents.erase(updateComponents.begin() + i);
		}
	}

	for(int i = 0; i < drawComponents.size(); ++i)
	{
		if(drawComponents.at(i)->GetName() == name)
		{
			delete drawComponents.at(i);
			drawComponents.erase(drawComponents.begin() + i);
		}
	}
}

void GameObject::Draw(Shader* shader)
{
	shader->Use();
	shader->SetUniform("unifModel", transform.GetTransform());

	for (auto i = drawComponents.begin(); i != drawComponents.end(); ++i)
	{
		auto component = (*i);
		if (component->GetActive())
			component->Draw(shader);
	}
}

void GameObject::Update(float dt)
{
	for (auto i = updateComponents.begin(); i != updateComponents.end(); ++i)
	{
		auto component = (*i);
		if (component->GetActive())
			component->Update(dt);
	}
}