#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/RenderTarget.hpp>

using namespace uth;

GameObject::GameObject()
	: m_active(true),
	parent(nullptr)
{
	transform.parent = this;
}

GameObject::~GameObject()
{
	RemoveComponents();
}

void GameObject::SetActive(bool value)
{
	m_active = value;
}

const bool GameObject::IsActive() const
{
	return m_active;
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
	component->parent = this;
	component->Init();
}

void GameObject::RemoveComponent(Component* component)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components.at(i) == component)
		{
			delete components.at(i);
			components.erase(components.begin() + i);
		}
	}
}

void GameObject::RemoveComponent(const std::string& name)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components.at(i)->GetName() == name)
		{
			delete components.at(i);
			components.erase(components.begin() + i);
		}
	}
}

void GameObject::RemoveComponents()
{
	for(size_t i = 0; i < components.size(); ++i)
		delete components.at(i);

	components.clear();
}

void GameObject::Draw(RenderTarget& target)
{
	if(!m_active)
		return;

	target.Bind();

	draw(target);

	for (auto it = components.begin(); it != components.end(); ++it)
	{
		target.GetShader().Use();
		auto component = (*it);
		if (component->IsActive())
			component->Draw(target);
	}
}

void GameObject::Update(float dt)
{
	if(!m_active)
		return;

	update(dt);

	for (auto i = components.begin(); i != components.end(); ++i)
	{
		auto component = (*i);
		if (component->IsActive())
			component->Update(dt);
	}
}

void GameObject::draw(RenderTarget& target)
{
	Shader& shader = target.GetShader();

	shader.Use();
	shader.SetUniform("unifModel", transform.GetTransform());
	shader.SetUniform("unifProjection", target.GetCamera().GetProjectionTransform());
}