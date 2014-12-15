#pragma once

#ifndef VERTEXBUFFER_H_UTH
#define VERTEXBUFFER_H_UTH

#include <vector>
#include <pmath/Vector.hpp>
#include <UtH/Renderer/Vertex.hpp>
#include <UtH/Resources/Shader.hpp>
#include <UtH/Platform/Configuration.hpp>
#include <unordered_set>

namespace uth
{
	class VertexBuffer
	{
		static std::unordered_set<VertexBuffer*> VERTEXBUFFERS;

		friend class ResourceManager;
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

		void changeBufferData(const unsigned int vertexOffset, const std::vector<Vertex>& vertices);
		void changeElementData(const unsigned int indexOffset, const std::vector<unsigned short>& indices);

        const std::vector<Vertex>& getVertices() const;
        const std::vector<unsigned short>& getIndices() const;

		void clear(const bool arrayBuffer = true, const bool elementBuffer = true);

        void bindArrayBuffer() const;
        void bindElementBuffer() const;

	// FIXME: put the private back as soon as spritebatch is fixed
	//private:
		void init();
		void setData() const;

		bool ClearOpenGLContext();
		bool RecreateOpenGLContext();

		std::vector<Vertex> m_vertexData;
		std::vector<unsigned short> m_indices;

        mutable bool m_arrayBufferNeedsUpdate,
                     m_elementBufferNeedsUpdate;

		unsigned int m_arrayBuffer;
		unsigned int m_elementBuffer;

	};
}
#endif