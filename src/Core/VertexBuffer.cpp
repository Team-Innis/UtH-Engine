#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <cassert>

using namespace uth;

VertexBuffer::VertexBuffer()
{
	init();
}

VertexBuffer::~VertexBuffer()
{
	clear();
	uthGraphics.deleteBuffers(1, &m_arrayBuffer);
	uthGraphics.deleteBuffers(1, &m_elementBuffer);
}


// Public

void VertexBuffer::addVertex(const Vertex& vertex)
{
	m_vertexData.push_back(vertex);
}

void VertexBuffer::addVertices(const std::vector<Vertex>& vertices)
{
	m_vertexData.insert(m_vertexData.end(), vertices.begin(), vertices.end());
}

void VertexBuffer::addIndex(const unsigned short index)
{
	m_indices.push_back(index);
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
}

const std::vector<Vertex>& VertexBuffer::getVertices() const
{
    return m_vertexData;
}

const std::vector<unsigned short>& VertexBuffer::getIndices() const
{
    return m_indices;
}

void VertexBuffer::clear()
{
	m_vertexData.clear();
	m_indices.clear();	
}

void VertexBuffer::bindArrayBuffer() const
{
    setData();

    uthGraphics.bindBuffer(ARRAY_BUFFER, m_arrayBuffer);
}

void VertexBuffer::bindElementBuffer() const
{
    setData();

    uthGraphics.bindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}

// Private

void VertexBuffer::init()
{
	uthGraphics.generateBuffers(1, &m_arrayBuffer);
	uthGraphics.generateBuffers(1, &m_elementBuffer);
}

void VertexBuffer::setData() const
{
	UsageType drawMode = STATIC_DRAW;

	uthGraphics.bindBuffer(ARRAY_BUFFER, m_arrayBuffer);
	uthGraphics.setBufferData(ARRAY_BUFFER, m_vertexData.size()*sizeof(Vertex),
		&m_vertexData.front(), drawMode);

	uthGraphics.bindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	uthGraphics.setBufferData(ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned short),
		&m_indices.front(), drawMode);
}