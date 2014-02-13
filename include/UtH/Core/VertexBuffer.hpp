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
		//void addVertices(const std::vector<float>& vertices, const std::vector<float>& uvs);
		void addIndex(const unsigned short index);
		//void addIndices(const std::vector<unsigned int>& indices);

		void setVertices(Shader* shader) const;

	private:
		void init();

		unsigned int buffer;

		int vertexCount;
		std::vector<float> data;
		std::vector<unsigned short> indices;
	};
}
#endif