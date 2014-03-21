#include <UtH/Renderer/SpriteBatch.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH\Platform\Debug.hpp>


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
        : m_atlas(nullptr)
    {
        reserve(975);
    }



    void SpriteBatch::AddSprite(GameObject* object, const std::string& atlasName)
    {
        //WriteLog("mark");
        int mod = m_objects.size() * 4;

        m_objects.push_back(object);
        umath::rectangle tex = m_atlas->getTextureCoords(atlasName.c_str());


        float width = (m_atlas->GetSize().x * tex.width),
              height = (m_atlas->GetSize().y * tex.height);

        m_vertexData.push_back(Vertex(umath::vector3(-width / 2.f, -height / 2.f, 1.f), umath::vector2(tex.left, 1.f - tex.top))); // vasen alakulma
        m_vertexData.push_back(Vertex(umath::vector3(width / 2.f, -height / 2.f, 1.f), umath::vector2(tex.getRight(), 1.f - tex.top))); // oikea alakulma
        m_vertexData.push_back(Vertex(umath::vector3(-width / 2.f, height / 2.f, 1.f), umath::vector2(tex.left, 1.f - (tex.top + tex.height)))); // vasen yläkulma
        m_vertexData.push_back(Vertex(umath::vector3(width / 2.f, height / 2.f, 1.f), umath::vector2(tex.getRight(), 1.f - (tex.top + tex.height)))); // oikea yläkulma
	    m_spriteBuffer.addIndex(0 + mod);
	    m_spriteBuffer.addIndex(1 + mod);
	    m_spriteBuffer.addIndex(2 + mod);
	    m_spriteBuffer.addIndex(1 + mod);
	    m_spriteBuffer.addIndex(3 + mod);
	    m_spriteBuffer.addIndex(2 + mod);
    }

    void SpriteBatch::SetTextureAtlas(TextureAtlas* atlas)
    {
        m_atlas = atlas;
    }

    void SpriteBatch::Draw(Shader* shader)
    {
        //m_vertexData.clear();
        //m_vertexData = m_spriteBuffer.getVertices();

        m_spriteBuffer.clear(true, false);
        m_spriteBuffer.addVertices(m_vertexData);

        for (int i = 0; i < m_vertexData.size() / 4; ++i)
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

        m_atlas->Bind();
        shader->SetUniform("unifSampler", 0);
        shader->SetUniform("unifColor", 1, 1, 1, 1);


        uthGraphics.bindBuffer(ARRAY_BUFFER, m_spriteBuffer.getArrayBufferID());
        shader->setAttributeData("attrPosition", 3, FLOAT_TYPE, sizeof(Vertex), (void*)0);
        shader->setAttributeData("attrUV", 2, FLOAT_TYPE, sizeof(Vertex), (void*)(3 * sizeof(float)));

        uthGraphics.bindBuffer(ELEMENT_ARRAY_BUFFER, m_spriteBuffer.getElementBufferID());
        uthGraphics.drawElements(TRIANGLES, m_spriteBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);
    }
    
}