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

//uth::GameObject::GameObject(const GameObject& other)
//    : transform(*(new Transform(other.transform))),
//      parent(other.parent),
//      components(),
//      m_name(other.m_name),
//      m_active(other.m_active)
//{
//    AddComponent(&transform);
//    transform.parent = this;
//}

GameObject::~GameObject()
{
	RemoveComponents();
}

void GameObject::AddComponent(Component* component)
{
    m_components.emplace_back(component);
	component->parent = this;
	component->Init();
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

tinyxml2::XMLNode* GameObject::save() const
{
    auto node = Object::save();

    if (!node)
        return nullptr;

    {
        auto compArray = new tinyxml2::XMLDocument();
        compArray->SetValue("components");

        for (auto& i : m_components)
        {
            std::unique_ptr<tinyxml2::XMLDocument> comp(i->save()->ToDocument());

            if (comp)
                compArray->InsertEndChild(comp.release());
        }

        node->InsertEndChild(compArray);
    }

    return node;
}

bool GameObject::load(const tinyxml2::XMLNode& doc)
{
    if (!Object::load(doc))
        return false;

    auto compArray = doc.FirstChild();

    for (auto itr = compArray; itr != nullptr; itr = itr->NextSibling())
    {
        if (itr->Value() == "components")
        {
            for (auto cItr = itr->FirstChild(); cItr != nullptr; cItr = cItr->NextSibling())
            {
                std::unique_ptr<Component> ptr;
                auto& funcs = uthSceneM.m_componentFuncs;

                for (size_t i = 0; i < funcs.size() && ptr == nullptr; ++i)
                    ptr.reset(funcs[i](cItr->Value()));

                if (ptr && ptr->load(*cItr))
                    AddComponent(ptr.release());
            }
        }
    }

    return true;
}