#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <pmath/Vector3.hpp>

using namespace uth;

Sprite::Sprite(Texture* texture, const std::string& name)
	: Component(name),
	  m_texture(texture)
{
	defaults();
}

// Public

Sprite::Sprite(const std::string& filePath, const std::string& name)
	: Component(name)
{
	SetTexture(uthRS.LoadTexture(filePath));

	defaults();
}

Sprite::Sprite(const pmath::Vec4& fillColor, const pmath::Vec2& size, const std::string& name)
	: Component(name),
	  m_texture(nullptr)
{
	m_size = size;
    m_color = fillColor;
	Init();
}


Sprite::~Sprite()
{
	m_texture = nullptr;
}

void Sprite::Init()
{
	generateBuffer(true);
	if (parent)
		parent->transform.setSize(m_size);
}

void Sprite::Draw(RenderTarget& target)
{
	Shader& shader = target.GetShader();

	if (m_texture)
	{
		m_texture->Bind();
		shader.SetUniform("useTexture", 1.f);
		shader.SetUniform("unifSampler", 0);
	}
	else
	{
		shader.SetUniform("useTexture", 0.f);
	}

	m_vertexBuffer.bindArrayBuffer();
	// (position + uv + color) * sizeof(float)
	const int posOffset = (3 + 2 + 4)*sizeof(float);
	// position * sizeof(float)
	const int uvStart = 3*sizeof(float);
	// (position + uv) * sizeof(float)
	const int colorStart = (3 + 2)*sizeof(float);

	// Attribute name, number of components, datatype, bytes between first elements,
	// offset of first element in buffer
	shader.setAttributeData("attrPosition", 3, FLOAT_TYPE, posOffset, (void*)0);
	shader.setAttributeData("attrUV", 2, FLOAT_TYPE, posOffset, (void*)uvStart);
	shader.setAttributeData("attrColor", 4, FLOAT_TYPE, posOffset, (void*)colorStart);

	m_vertexBuffer.bindElementBuffer();
	uth::Graphics::DrawElements(TRIANGLES, m_vertexBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);

	uth::Graphics::BindBuffer(ARRAY_BUFFER, 0);
}

void Sprite::SetTexture(Texture* texture)
{
    if (texture)
    {
        m_texture = texture;
        m_size = texture->GetSize();
        Init();
    }
}

Texture* Sprite::GetTexture() const
{
	return m_texture;
}

const pmath::Vec2& Sprite::GetSize() const
{
	return m_size;
}

void Sprite::SetColor(const pmath::Vec4& color)
{
	m_color = color;
	generateBuffer();
}

void Sprite::SetColor(float r, float g, float b, float a)
{
	SetColor(pmath::Vec4(r,g,b,a));
}


const pmath::Vec4& Sprite::GetColor() const
{
	return m_color;
}


// Private
void Sprite::defaults()
{
    if (m_texture)
	    m_size = m_texture->GetSize();
    else
        m_size = pmath::Vec2();

	m_color = pmath::Vec4(1.f, 1.f, 1.f, 1.f);
}



void Sprite::generateBuffer(bool init)
{
    if (init) // Create the buffer for the first time
    {
        m_vertexBuffer.clear();

        m_vertexBuffer.addVertex(Vertex(pmath::Vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0),
            pmath::Vec2(0.0f, 1.0f), m_color));
        m_vertexBuffer.addVertex(Vertex(pmath::Vec3(0.5f * m_size.x, -0.5f * m_size.y, 0),
            pmath::Vec2(1.0f, 1.0f), m_color));
        m_vertexBuffer.addVertex(Vertex(pmath::Vec3(-0.5f * m_size.x, 0.5f * m_size.y, 0),
            pmath::Vec2(0.0f, 0.0f), m_color));
        m_vertexBuffer.addVertex(Vertex(pmath::Vec3(0.5f * m_size.x, 0.5f * m_size.y, 0),
            pmath::Vec2(1.0f, 0.0f), m_color));


        m_vertexBuffer.addIndex(0);
        m_vertexBuffer.addIndex(1);
        m_vertexBuffer.addIndex(2);
        m_vertexBuffer.addIndex(1);
        m_vertexBuffer.addIndex(3);
        m_vertexBuffer.addIndex(2);

        m_vertexBuffer.setData();
    }
    else // We are updating the buffer
    {
        std::vector<Vertex> vertices;
        vertices.reserve(4);
        vertices.push_back(Vertex(pmath::Vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0),
        pmath::Vec2(0.0f, 1.0f), m_color));
        vertices.push_back(Vertex(pmath::Vec3(0.5f * m_size.x, -0.5f * m_size.y, 0),
        pmath::Vec2(1.0f, 1.0f), m_color));
        vertices.push_back(Vertex(pmath::Vec3(-0.5f * m_size.x, 0.5f * m_size.y, 0),
        pmath::Vec2(0.0f, 0.0f), m_color));
        vertices.push_back(Vertex(pmath::Vec3(0.5f * m_size.x, 0.5f * m_size.y, 0),
        pmath::Vec2(1.0f, 0.0f), m_color));

        m_vertexBuffer.changeBufferData(0, vertices);
    }
}

namespace rj = rapidjson;

rj::Value uth::Sprite::save(rj::MemoryPoolAllocator<>& alloc) const
{
    rj::Value val(Component::save(alloc));

    val.AddMember(rj::StringRef("properties"), rj::kArrayType, alloc);
    rj::Value& props = val["properties"];

    props.PushBack(m_size.w, alloc);
    props.PushBack(m_size.h, alloc);
    props.PushBack(m_color.r, alloc);
    props.PushBack(m_color.g, alloc);
    props.PushBack(m_color.b, alloc);
    props.PushBack(m_color.a, alloc);

    if (m_texture)
    // TODO: need to extract texture path somehow
    val.AddMember(rj::StringRef("texture"), rj::kStringType, alloc);

    return val;
}

bool uth::Sprite::load(const rj::Value& doc)
{
    if (!Component::load(doc))
        return false;

    const rj::Value& props = doc["properties"];

    m_size.w = props[0u].GetDouble();
    m_size.h = props[1].GetDouble();
    m_color.r = props[2].GetDouble();
    m_color.g = props[3].GetDouble();
    m_color.b = props[4].GetDouble();
    m_color.a = props[5].GetDouble();

    if (doc.HasMember("texture") && doc["texture"].IsString())
        SetTexture(uthRS.LoadTexture(doc["texture"].GetString()));

    return false;
}

const char* uth::Sprite::getIdentifier() const
{
    return "Sprite";
}
