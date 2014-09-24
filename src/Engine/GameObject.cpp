#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/RenderTarget.hpp>

using namespace uth;

GameObject::GameObject()
    : transform(*(new Transform())),
      parent(nullptr),
      m_name(""),
      m_active(true)
	  
{
	AddComponent(&transform);
	transform.parent = this;
}

GameObject::GameObject(const std::string &name)
    : transform(*(new Transform())),
      parent(nullptr),
      m_name(name),
	  m_active(true)
{
	AddComponent(&transform);
	transform.parent = this;
}

uth::GameObject::GameObject(const GameObject& other)
    : transform(*(new Transform(other.transform))),
      parent(other.parent),
      m_components(),
      m_name(other.m_name),
      m_active(other.m_active)
{
    AddComponent(&transform);
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
    m_components.emplace_back(component);
	component->parent = this;
	component->Init();
}

const std::string GameObject::GetName() const
{
	return m_name;
}

void GameObject::RemoveComponent(Component* component)
{
    for (size_t i = 0; i < m_components.size(); ++i)
	{
        if (m_components.at(i).get() == component)
		{
            m_components.erase(m_components.begin() + i);
		}
	}
}

void GameObject::RemoveComponent(const std::string& name)
{
    for (size_t i = 0; i < m_components.size(); ++i)
	{
        if (m_components.at(i)->GetName() == name)
		{
            m_components.erase(m_components.begin() + i);
		}
	}
}

void GameObject::RemoveComponents()
{
    m_components.clear();
}

void GameObject::Draw(RenderTarget& target, RenderAttributes attributes)
{
	if(!m_active)
		return;

	target.Bind();

    Shader* tempShader = &target.GetShader();
    Camera* tempCamera = &target.GetCamera();

    Shader& shader = attributes.shader ? *attributes.shader : target.GetShader();
    Camera& camera = attributes.camera ? *attributes.camera : target.GetCamera();
    target.SetShader(&shader);
    target.SetCamera(&camera);

    shader.SetUniform("unifModel", transform.GetTransform());
    shader.SetUniform("unifProjection", target.GetCamera().GetProjectionTransform());

    draw(target);

    for (auto& i : m_components)
	{
		target.GetShader().Use();
		if (i->IsActive())
			i->Draw(target);
	}

    target.SetShader(tempShader);
    target.SetCamera(tempCamera);
}

void GameObject::Update(float dt)
{
	if(!m_active)
		return;

	update(dt);

	for (auto& i : m_components)
	{
		if (i->IsActive())
			i->Update(dt);
	}
}