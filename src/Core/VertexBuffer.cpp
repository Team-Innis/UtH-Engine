#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <cassert>

using namespace uth;

//static std::unordered_set<VertexBuffer*> VertexBuffer::VERTEXBUFFERS;

VertexBuffer::VertexBuffer()
    : m_arrayBufferNeedsUpdate(false),
      m_elementBufferNeedsUpdate(false)
{
//#ifdef UTH_SYSTEM_ANDROID
	VERTEXBUFFERS.emplace(this);
//#endif
	init();
}

VertexBuffer::~VertexBuffer()
{
//#ifdef UTH_SYSTEM_ANDROID
	VERTEXBUFFERS.erase(this);
//#endif

	clear();
	uth::Graphics::DeleteBuffers(1, &m_arrayBuffer);
	uth::Graphics::DeleteBuffers(1, &m_elementBuffer);
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

void VertexBuffer::changeBufferData(const unsigned int offset, const std::vector<Vertex>& vertices) const
{
    unsigned int size = vertices.size() * sizeof(Vertex);
    uth::Graphics::BindBuffer(ARRAY_BUFFER, m_arrayBuffer);
    Graphics::SetBufferSubData(ARRAY_BUFFER, offset, size, &vertices.front());
}

void VertexBuffer::changeElementData(const unsigned int offset, const std::vector<unsigned int>& indices)
{
    unsigned int size = indices.size() * sizeof(unsigned int);
    uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    Graphics::SetBufferSubData(ELEMENT_ARRAY_BUFFER, offset, size, &indices.front());
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
