#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>
#include <UtH/Math/Vector.hpp>
#include <UtH/Core/Vertex.hpp>
#include <UtH/Core/Shader.hpp>

namespace uth
{
	class VertexBuffer
	{

        friend class SpriteBatch;

	public:
		VertexBuffer();
		~VertexBuffer();

		void addVertex(const Vertex& vertex);
		// Add vector of Vertices at the end of current vector, doesn't modify input data
		void addVertices(const std::vector<Vertex>& vertices);

		void addIndex(const unsigned short index);
		// Add vector of indexes at the end of current index vector, offsets indices with already added indices
		void addIndices(const std::vector<unsigned short>& indices);

        const std::vector<Vertex>& getVertices() const;
        const std::vector<unsigned short>& getIndices() const;

		void clear(const bool arrayBuffer = true, const bool elementBuffer = true);

        void bindArrayBuffer() const;
        void bindElementBuffer() const;

	private:
		void init();
		void setData() const;

        std::vector<Vertex> m_vertexData;

		unsigned int m_arrayBuffer;
		unsigned int m_elementBuffer;

		std::vector<unsigned short> m_indices;
	};
}
#endif