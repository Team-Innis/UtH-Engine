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

        void clear(const bool vertices = true, const bool indices = true);
		void addVertex(const Vertex& vertex);
		// Add vector of vertices and uvs to the end of current vectors, doesn't modify existing data
		void addVertices(const std::vector<Vertex>& vertices);

		void addIndex(const unsigned short index);
		// Add vector of indexes at the end of current index vector, doesn't modify data
		void addIndices(const std::vector<unsigned short>& indices);

        const std::vector<Vertex>& getVertices() const;
        const std::vector<unsigned short>& getIndices() const;

        unsigned int getArrayBufferID() const;
        unsigned int getElementBufferID() const;

		void draw(Shader* shader) const;

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