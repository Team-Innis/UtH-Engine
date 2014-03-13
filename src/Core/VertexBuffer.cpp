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
	m_vertexData.clear();
	m_indices.clear();
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
	m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

void VertexBuffer::draw(Shader* shader) const
{
	setData();

	uthGraphics.bindBuffer(ARRAY_BUFFER, m_arrayBuffer);
	const int posOffset = 5*sizeof(float);
	const int uvOffset = 5*sizeof(float);
	const int uvStart = 3*sizeof(float);

	// Attribute name, number of components, datatype, bytes between first elements,
	// offset of first element in buffer
	shader->setAttributeData("attrPosition", 3, FLOAT_TYPE, posOffset, (void*)0);
	shader->setAttributeData("attrUV", 2, FLOAT_TYPE, uvOffset, (void*)uvStart);

	uthGraphics.bindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	uthGraphics.drawElements(TRIANGLES, m_indices.size(), 
		UNSIGNED_SHORT_TYPE, (void*)0);

	uthGraphics.bindBuffer(ARRAY_BUFFER, 0);	
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