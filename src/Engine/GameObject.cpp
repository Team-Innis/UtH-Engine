#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/SceneManager.hpp>

using namespace uth;

GameObject::GameObject()
{

}

GameObject::GameObject(const std::string &tag)
	: Object(tag)
{
}

uth::GameObject::GameObject(const std::vector<std::string>& tags)
	: Object(tags)
{
}

GameObject::~GameObject()
{
	RemoveComponents();
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
	if (!m_active)
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
	Object::Draw(target);
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
	Object::Update(dt);
}

namespace rj = rapidjson;

rapidjson::Value GameObject::save(rapidjson::MemoryPoolAllocator<>& alloc) const
{
    rj::Value val = Object::save(alloc);

    if (!m_components.empty())
    {
        val.AddMember(rj::StringRef("components"), rj::kArrayType, alloc);
        rj::Value& compArray = val["components"];

        for (auto& i : m_components)
        {
            rj::Value compVal = i->save(alloc);
            compVal.AddMember(rj::StringRef("identifier"), rj::StringRef(typeid(*i.get()).name()), alloc);

            compArray.PushBack(compVal, alloc);
        }
    }

    return val;
}

bool GameObject::load(const rj::Value& doc)
{
    if (!Object::load(doc))
        return false;

    if (doc.HasMember("components") && doc["components"].IsArray())
    {
        const rj::Value& compArray = doc["components"];

        for (auto itr = compArray.Begin(); itr != compArray.End(); ++itr)
        {
            const std::string id(itr->FindMember("identifier")->value.GetString());
            
            std::unique_ptr<Component> ptr(static_cast<Component*>(uthSceneM.GetSaveable(id)));

            if (!ptr)
            {
                WriteError("Failed to cast loaded component with identifier %s", id.c_str());
                return false;
            }

            if (ptr->load(*itr))
                AddComponent(ptr.release());
            else
                return false;
        }
    }

    return true;
}