#include <UtH/Engine/TMX/TileHackBatch.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Core/VertexBuffer.hpp>

using namespace uth;
using namespace TMX;

namespace
{
	static uth::Shader hbatchShader;
}

TileHackBatch::TileHackBatch(const bool adoptPointers)
	: SpriteBatch(adoptPointers)
{ }

TileHackBatch::~TileHackBatch()
{ }

void TileHackBatch::draw(RenderTarget& target)
{
	// Copypaste from generic shader

	if ((!m_atlas && !m_texture) || m_objects.empty())
			return;

		static bool shaderLoaded = false;
		if (!shaderLoaded)
		{
			hbatchShader.LoadShader("Shaders/batchvertexshader.vert", "Shaders/batchfragmentshader.frag");
			shaderLoaded = true;
		}

		m_spriteBuffer.clear(true, false);
		m_spriteBuffer.addVertices(m_vertexData);

		for (size_t i = 0; i < m_vertexData.size() / 4; ++i)
		{
			umath::matrix3 m = m_objects[i]->transform.GetTransform().getMatrix3();
			// NOTE: this will cause the map to draw correctly.
			// TODO: figure out a real solution
			m[0][0] = m[0][0] > 0 ? 1 : -1;
			m[1][1] = m[1][1] > 0 ? 1 : -1;

			m_spriteBuffer.m_vertexData[0 + (i * 4)].position *= m;
			m_spriteBuffer.m_vertexData[1 + (i * 4)].position *= m;
			m_spriteBuffer.m_vertexData[2 + (i * 4)].position *= m;
			m_spriteBuffer.m_vertexData[3 + (i * 4)].position *= m;
		}

		m_spriteBuffer.setData();

		m_atlas ? m_atlas->Bind() : m_texture->Bind();

		hbatchShader.Use();

		hbatchShader.SetUniform("unifProjection", target.GetCamera().GetProjectionTransform());
		hbatchShader.SetUniform("unifSampler", 0);
		//batchShader.SetUniform("unifColor", 1, 1, 1, 1);


		uth::Graphics::BindBuffer(ARRAY_BUFFER, m_spriteBuffer.m_arrayBuffer);
		hbatchShader.setAttributeData("attrPosition", 3, FLOAT_TYPE, sizeof(Vertex), (void*)0);
		hbatchShader.setAttributeData("attrUV", 2, FLOAT_TYPE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		hbatchShader.setAttributeData("attrColor", 4, FLOAT_TYPE, sizeof(Vertex), (void*)(5 * sizeof(float)));

		uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_spriteBuffer.m_elementBuffer);
		uth::Graphics::DrawElements(TRIANGLES, m_spriteBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);

		target.SetShader(nullptr);
}