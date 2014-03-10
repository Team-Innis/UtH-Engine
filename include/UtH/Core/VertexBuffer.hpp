#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>
#include <UtH/Math/Vector.hpp>
#include <UtH/Core/Shader.hpp>

namespace uth
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void addVertex(const umath::vector3 vertex, const umath::vector2 uv);
		// Add vector of vertices and uvs to the end of current vectors, doesn't modify data
		void addVertices(const std::vector<umath::vector3>& vertices,
						 const std::vector<umath::vector2>& uvs);

		void addIndex(const unsigned short index);
		// Add vector of indexes at the end of current index vector, doesn't modify data
		void addIndices(const std::vector<unsigned short>& indices);

		void draw(Shader* shader) const;

	private:
		void init();
		void setData() const;

		unsigned int m_arrayBuffer;
		unsigned int m_elementBuffer;

		std::vector<float> m_vertexData;
		std::vector<unsigned short> m_indices;
	};
}
#endif