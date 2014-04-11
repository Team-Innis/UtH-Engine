#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Renderer/RenderTarget.hpp>


namespace uth
{
    void SpriteBatch::reserve(const unsigned int amount)
    {
        m_objects.reserve(amount);
        m_vertexData.reserve(amount);
        m_spriteBuffer.m_vertexData.reserve(amount);
        m_spriteBuffer.m_indices.reserve(amount);
    }


    SpriteBatch::SpriteBatch()
        : m_atlas(nullptr),
          m_texture(nullptr)
    {
        reserve(975);
    }



    bool SpriteBatch::AddSprite(GameObject* object, const std::string& atlasName)
    {
        if (!m_atlas && !m_texture)
            return false;

        unsigned short mod = static_cast<unsigned short>(m_objects.size()) * 4;

        m_objects.push_back(object);
        umath::rectangle tex = (atlasName.empty() || !m_atlas) ? umath::rectangle(0.f, 0.f, 1.f, 1.f) : m_atlas->getTextureCoords(atlasName.c_str());


        float width = ((m_atlas ? m_atlas->GetSize().x : m_texture->GetSize().x) * tex.width),
              height = ((m_atlas ? m_atlas->GetSize().y : m_texture->GetSize().y) * tex.height);

        m_vertexData.push_back(Vertex(
			umath::vector3(-width / 2.f, -height / 2.f, 1.f), 
			umath::vector2(tex.x, 1.f - tex.y)
			));
        m_vertexData.push_back(Vertex(
			umath::vector3(width / 2.f, -height / 2.f, 1.f), 
			umath::vector2(tex.getRight(), 1.f - tex.y)
			));
        m_vertexData.push_back(Vertex(
			umath::vector3(-width / 2.f, height / 2.f, 1.f), 
			umath::vector2(tex.x, 1.f - (tex.y + tex.height))
			));
        m_vertexData.push_back(Vertex(
			umath::vector3(width / 2.f, height / 2.f, 1.f), 
			umath::vector2(tex.getRight(), 1.f - (tex.y + tex.height))
			));
	    m_spriteBuffer.addIndex(0 + mod);
	    m_spriteBuffer.addIndex(1 + mod);
	    m_spriteBuffer.addIndex(2 + mod);
	    m_spriteBuffer.addIndex(1 + mod);
	    m_spriteBuffer.addIndex(3 + mod);
	    m_spriteBuffer.addIndex(2 + mod);

        return true;
    }

    void SpriteBatch::SetTextureAtlas(TextureAtlas* atlas)
    {
        m_atlas = atlas;
        m_texture = nullptr;
    }

    void SpriteBatch::SetTexture(Texture* texture)
    {
        m_texture = texture;
        m_atlas = nullptr;
    }

    void SpriteBatch::Clear()
    {
        m_objects.clear();
        m_vertexData.clear();
        m_spriteBuffer.clear();
    }

    void SpriteBatch::draw(RenderTarget& target)
    {
        if (!m_atlas && m_texture)
            return;

        m_spriteBuffer.clear(true, false);
        m_spriteBuffer.addVertices(m_vertexData);

        for (size_t i = 0; i < m_vertexData.size() / 4; ++i)
        {
            const umath::matrix4& m = m_objects[i]->transform.GetTransform();
            umath::matrix3 t_m;
            t_m[0][0] = m[0][0];
            t_m[0][1] = m[0][1];
            t_m[1][0] = m[1][0];
            t_m[1][1] = m[1][1];
            t_m[0][2] = m[0][3];
            t_m[1][2] = m[1][3];

            m_spriteBuffer.m_vertexData[0 + (i * 4)].position *= t_m;
            m_spriteBuffer.m_vertexData[1 + (i * 4)].position *= t_m;
            m_spriteBuffer.m_vertexData[2 + (i * 4)].position *= t_m;
            m_spriteBuffer.m_vertexData[3 + (i * 4)].position *= t_m;
        }
        
        m_spriteBuffer.setData();

        m_atlas ? m_atlas->Bind() : m_texture->Bind();

        Shader& shader = target.GetShader();

        shader.SetUniform("unifSampler", 0);
        shader.SetUniform("unifColor", 1, 1, 1, 1);


        uth::Graphics::BindBuffer(ARRAY_BUFFER, m_spriteBuffer.m_arrayBuffer);
        shader.setAttributeData("attrPosition", 3, FLOAT_TYPE, sizeof(Vertex), (void*)0);
        shader.setAttributeData("attrUV", 2, FLOAT_TYPE, sizeof(Vertex), (void*)(3 * sizeof(float)));

        uth::Graphics::BindBuffer(ELEMENT_ARRAY_BUFFER, m_spriteBuffer.m_elementBuffer);
        uth::Graphics::DrawElements(TRIANGLES, m_spriteBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);
    }
    
}