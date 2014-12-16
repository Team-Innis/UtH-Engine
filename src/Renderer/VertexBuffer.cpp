#include <UtH/Renderer/VertexBuffer.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <cassert>

using namespace uth;

std::unordered_set<VertexBuffer*> VertexBuffer::VERTEXBUFFERS;

VertexBuffer::VertexBuffer()
    : m_arrayBufferNeedsUpdate(false),
      m_elementBufferNeedsUpdate(false)
{
	VERTEXBUFFERS.emplace(this);
	init();
}

VertexBuffer::~VertexBuffer()
{
	VERTEXBUFFERS.erase(this);

	clear();
	uth::Graphics::DeleteBuffers(1, &m_arrayBuffer);
	uth::Graphics::DeleteBuffers(1, &m_elementBuffer);
}

template<typename T>
bool Replace(std::vector<T>& target, const unsigned int offset, const std::vector<T>& source)
{
	const int extraItems = source.size() + offset - target.size();
	if (extraItems > 0)
	{
		target.insert(target.end(), source.end() - extraItems, source.end());
		memcpy(target.data(), source.data(),
			(source.size() - extraItems) * sizeof(T));
		return false;
	}
	else
	{
		memcpy(target.data(), source.data(),
			(source.size()) * sizeof(T));
		return true;
	}
}

// Public

void VertexBuffer::addVertex(const Vertex& vertex)
{
	m_vertexData.push_back(vertex);

    m_arrayBufferNeedsUpdate = true;
}

void VertexBuffer::addVertices(const std::vector<Vertex>& vertices)
{
	m_vertexData.insert(m_vertexData.end(), vertices.begin(), vertices.end());

    m_arrayBufferNeedsUpdate = true;
}

void VertexBuffer::addIndex(const unsigned short index)
{
	m_indices.push_back(index);

    m_elementBufferNeedsUpdate = true;
}

void VertexBuffer::addIndices(const std::vector<unsigned short>& indices)
{
	std::vector<unsigned short> input = indices;

	if (m_indices.size() > 0)
	{
		short lastIndex = m_indices.at(m_indices.size() - 1) + 1;

		for (auto it = input.begin(); it != input.end(); ++it)
		{
			(*it) += lastIndex;
		}
	}

	m_indices.insert(m_indices.end(), input.begin(), input.end());

    m_elementBufferNeedsUpdate = true;
}

void VertexBuffer::changeBufferData(const unsigned int vertexOffset, const std::vector<Vertex>& vertices)
{
	const unsigned int size = vertices.size() * sizeof(Vertex);

	if (Replace(m_vertexData, vertexOffset, vertices))
	{
		uth::Graphics::BindBuffer(ARRAY_BUFFER, m_arrayBuffer);
		Graphics::SetBufferSubData(ARRAY_BUFFER,
			vertexOffset * sizeof(Vertex), size, &vertices.front());
	}
	else
		setData();
}

void VertexBuffer::changeElementData(const unsigned int indexOffset, const std::vector<unsigned short>& indices)
{
	const unsigned int size = indices.size() * sizeof(unsigned int);

	if (Replace(m_indices, indexOffset, indices))
	{
		uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
		Graphics::SetBufferSubData(ELEMENT_ARRAY_BUFFER,
			indexOffset * sizeof(unsigned int), size, &indices.front());
	}
	else
		setData();
}

const std::vector<Vertex>& VertexBuffer::getVertices() const
{
    return m_vertexData;
}

const std::vector<unsigned short>& VertexBuffer::getIndices() const
{
    return m_indices;
}

void VertexBuffer::clear(const bool arrayBuffer, const bool elementBuffer)
{
    if (arrayBuffer)
    {
	    m_vertexData.clear();
        m_arrayBufferNeedsUpdate = true;
    }
    if (elementBuffer)
    {
	    m_indices.clear();
        m_elementBufferNeedsUpdate = true;
    }
}

void VertexBuffer::bindArrayBuffer() const
{
    setData();

    uth::Graphics::BindBuffer(ARRAY_BUFFER, m_arrayBuffer);
}

void VertexBuffer::bindElementBuffer() const
{
    setData();

    uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}

// Private

void VertexBuffer::init()
{
	uth::Graphics::GenerateBuffers(1, &m_arrayBuffer);
	uth::Graphics::GenerateBuffers(1, &m_elementBuffer);
}

void VertexBuffer::setData() const
{
	UsageType drawMode = STATIC_DRAW;

    if (m_arrayBufferNeedsUpdate)
    {
        uth::Graphics::BindBuffer(ARRAY_BUFFER, m_arrayBuffer);
	    uth::Graphics::SetBufferData(ARRAY_BUFFER, m_vertexData.size()*sizeof(Vertex),
		&m_vertexData.front(), drawMode);
        m_arrayBufferNeedsUpdate = false;
    }

    if (m_elementBufferNeedsUpdate)
    {
	    uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	    uth::Graphics::SetBufferData(ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned short),
		&m_indices.front(), drawMode);
        m_elementBufferNeedsUpdate = false;
    }
}

bool VertexBuffer::ClearOpenGLContext()
{
	uth::Graphics::DeleteBuffers(1, &m_arrayBuffer);
	uth::Graphics::DeleteBuffers(1, &m_elementBuffer);
	return true;
}
bool VertexBuffer::RecreateOpenGLContext()
{
	uth::Graphics::GenerateBuffers(1, &m_arrayBuffer);
	uth::Graphics::GenerateBuffers(1, &m_elementBuffer);
	m_arrayBufferNeedsUpdate = true;
	m_elementBufferNeedsUpdate = true;
	setData();
	return true;
}
