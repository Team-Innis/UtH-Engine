#include <UtH/Engine/GameObject.hpp>

using namespace uth;

GameObject::GameObject()
	: m_angle(0),
	  m_modelTransform(umath::matrix4::Identity)
{
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

void GameObject::Move(umath::vector2 offset)
{
	Move(offset.x, offset.y);
}

void GameObject::Move(int offsetX, int offsetY)
{
	m_dimensions.x += offsetX;
	m_dimensions.y += offsetY;
}

void GameObject::SetPosition(umath::vector2 position)
{
	SetPosition(position.x, position.y);
}

void GameObject::SetPosition(int posX, int posY)
{
	m_dimensions.x = posX;
	m_dimensions.y = posY;
}

const umath::vector2 GameObject::GetPosition() const
{
	return umath::vector2(m_dimensions.x, m_dimensions.y);
}

void GameObject::Resize(umath::vector2 size)
{
	Resize(size.x, size.y);
}

void GameObject::Resize(int width, int height)
{
	m_dimensions.width = width;
	m_dimensions.height = height;
}

const umath::vector2 GameObject::GetSize() const
{
	return umath::vector2(m_dimensions.width, m_dimensions.height);
}
		
void GameObject::SetRotation(float angle)
{
	m_angle = angle;
}

float GameObject::GetRotation()
{
	return m_angle;
}


void GameObject::Rotate(float angle)
{
	m_angle += angle;
}

void GameObject::Draw()
{
	
}

void GameObject::Update(float dt)
{

}

void GameObject::updateTransform()
{
	float angle  = -m_angle * PI / 180.f;
	float cosine = std::cos(angle);
	float sine = std::sin(angle);

	umath::matrix4 rotation(cosine, -sine, 0, 0,
							sine, cosine, 0, 0,
							0,   0,       0, 0,
							0,   0,       0, 1.0f);

	umath::matrix4 scale(m_dimensions.width, 0, 0, 0,
							0, m_dimensions.height, 0, 0,
							0,   0,       1.0f, 0,
							0,   0,       0, 1.0f);

	umath::matrix4 translation(1.0f, 0, 0, 0,
								0, 1.0f, 0, 0,
								0, 0, 1.0f, 1.0f,
								m_dimensions.x, m_dimensions.y, 1.0f, 1.0f);

	m_modelTransform = translation * rotation * scale; // Probably wrong
}