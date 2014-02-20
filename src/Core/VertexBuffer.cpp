#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Platform/Graphics.hpp>

using namespace uth;

VertexBuffer::VertexBuffer()
	: vertexCount(0)
{
	init();
}

VertexBuffer::~VertexBuffer()
{
	data.clear();
	indices.clear();
	uthGraphics.deleteBuffers(1, &buffer);
}


// Public

void VertexBuffer::addVertex(const umath::vector3 vertex, const umath::vector2 uv)
{
	data.push_back(vertex.x);
	data.push_back(vertex.y);
	data.push_back(vertex.z);

	data.push_back(uv.x);
	data.push_back(uv.y);
	vertexCount++;
}

//void VertexBuffer::addVertices(const std::vector<float>& vertices, const std::vector<float>& uvs)
//{
//	// TODO
//}

void VertexBuffer::addIndex(const unsigned short index)
{
	indices.push_back(index);
}

//void VertexBuffer::addIndices(const std::vector<unsigned int>& indices)
//{
//	// TODO
//}

void VertexBuffer::setVertices(Shader* shader) const
{
	uthGraphics.bindBuffer(BufferType::ARRAY_BUFFER, buffer);
	uthGraphics.setBufferData(BufferType::ARRAY_BUFFER, data.size()*sizeof(float), &data.front(),
		UsageType::DYNAMIC_DRAW);

	const int posOffset = 5*sizeof(float);
	const int uvOffset = 5*sizeof(float);
	const int uvStart = 3*sizeof(float);

	// Attribute name, number of components, datatype, bytes between elements,
	// offset of first element in buffer
	shader->setAttributeData("attrPosition", 3, DataType::FLOAT_TYPE, posOffset, 0);
	shader->setAttributeData("attrUV", 2, DataType::FLOAT_TYPE, uvOffset, (void*)uvStart);
	// TODO: remove once done testing
	uthGraphics.drawElements(PrimitiveType::TRIANGLES, indices.size(), 
		DataType::UNSIGNED_SHORT_TYPE, &indices.front());

	uthGraphics.bindBuffer(BufferType::ARRAY_BUFFER, 0);	
}

// Private

void VertexBuffer::init()
{
	uthGraphics.generateBuffers(1, &buffer);
}