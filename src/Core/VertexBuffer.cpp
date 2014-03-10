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

void VertexBuffer::addVertex(const umath::vector3 vertex, const umath::vector2 uv)
{
	m_vertexData.push_back(vertex.x);
	m_vertexData.push_back(vertex.y);
	m_vertexData.push_back(vertex.z);

	m_vertexData.push_back(uv.x);
	m_vertexData.push_back(uv.y);
}

void VertexBuffer::addVertices(const std::vector<umath::vector3>& vertices,
	const std::vector<umath::vector2>& uvs)
{
	assert(vertices.size() == uvs.size());

	// Just to be double sure
	for(int i = 0; i < vertices.size() && i < uvs.size(); ++i)
	{
		m_vertexData.push_back(vertices.at(i).x);
		m_vertexData.push_back(vertices.at(i).y);
		m_vertexData.push_back(vertices.at(i).z);

		m_vertexData.push_back(uvs.at(i).x);
		m_vertexData.push_back(uvs.at(i).y);
	}
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
	uthGraphics.setBufferData(ARRAY_BUFFER, m_vertexData.size()*sizeof(float),
		&m_vertexData.front(), drawMode);

	uthGraphics.bindBuffer(ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	uthGraphics.setBufferData(ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned short),
		&m_indices.front(), drawMode);
}