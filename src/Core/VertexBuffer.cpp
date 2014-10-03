#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <cassert>

using namespace uth;

VertexBuffer::VertexBuffer()
    : m_arrayBufferNeedsUpdate(false),
      m_elementBufferNeedsUpdate(false)
{
	init();
}

VertexBuffer::~VertexBuffer()
{
	clear();
	uth::Graphics::DeleteBuffers(1, &m_arrayBuffer);
	uth::Graphics::DeleteBuffers(1, &m_elementBuffer);
}


template<typename T>
Replace(std::vector<T> target, unsigned int offset, std::vector<T> source)
{
	const int extraItems = target.size() - offset - source.size();
	if (extraItems > 0)
	{
		target.insert(target.end(), source.end() - extraItems, source.end());
		std::memcpy(target.data(), source.data(),
			(source.size() - extraItems) * sizeof(T));
	}
	else
	{
		std::memcpy(m_vertexData.data(), vertices.data(),
			(source.size()) * sizeof(T));
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

void VertexBuffer::changeBufferDataUV(const unsigned int vertexOffset,
	const std::vector<pmath::Vec2> uvs)
{

}
void VertexBuffer::changeBufferDataPos(const unsigned int vertexOffset,
	const std::vector<pmath::Vec3> positions)
{

}
void VertexBuffer::changeBufferDataColor(const unsigned int vertexOffset,
	const std::vector<pmath::Vec4> colors)
{

}
void VertexBuffer::changeBufferData(const unsigned int vertexOffset,
	const std::vector<Vertex>& vertices)
{
    const unsigned int size = vertices.size() * sizeof(Vertex);

	const int extraVertices = m_vertexData.size() - vertexOffset - vertices.size();
	if (extraVertices > 0)
	{
		m_vertexData.insert(m_vertexData.end(), vertices.end() - extraVertices, vertices.end());
		std::memcpy(m_vertexData.data(), vertices.data(),
			(vertices.size() - extraVertices) * sizeof(Vertex));
	}
	else
	{
		std::memcpy(m_vertexData.data(), vertices.data(),
			(vertices.size()) * sizeof(Vertex));
	}

    uth::Graphics::BindBuffer(ARRAY_BUFFER, m_arrayBuffer);
	Graphics::SetBufferSubData(ARRAY_BUFFER,
		vertexOffset * sizeof(Vertex), size, &vertices.front());
}
void VertexBuffer::changeElementData(const unsigned int indexOffset,
	const std::vector<unsigned int>& indices)
{
    const unsigned int size = indices.size() * sizeof(unsigned int);

	const int extraVertices = m_indices.size() - indexOffset - indices.size();
	if (extraVertices > 0)
	{
		m_indices.insert(m_indices.end(), indices.end() - extraVertices, indices.end());
		std::memcpy(m_indices.data(), indices.data(),
			(indices.size() - extraVertices) * sizeof(Vertex));
	}
	else
	{
		std::memcpy(m_indices.data(), indices.data(),
			(indices.size()) * sizeof(Vertex));
	}

    uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	Graphics::SetBufferSubData(ELEMENT_ARRAY_BUFFER,
		indexOffset * sizeof(unsigned int), size, &indices.front());
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
		const unsigned int size = m_vertexData.size() * sizeof(Vertex);
        uth::Graphics::BindBuffer(ARRAY_BUFFER, m_arrayBuffer);
	    uth::Graphics::SetBufferData(ARRAY_BUFFER, size,
		&m_vertexData.front(), drawMode);
        m_arrayBufferNeedsUpdate = false;
    }

    if (m_elementBufferNeedsUpdate)
	{
		const unsigned int size = m_indices.size() * sizeof(unsigned int);
	    uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	    uth::Graphics::SetBufferData(ELEMENT_ARRAY_BUFFER, size,
		&m_indices.front(), drawMode);
        m_elementBufferNeedsUpdate = false;
    }
}
