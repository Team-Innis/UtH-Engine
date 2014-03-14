#include <UtH/Renderer/SpriteBatch.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH\Platform\OpenGL.hpp>


namespace uth
{

    SpriteBatch::SpriteBatch()
        : m_atlas(nullptr)
    {

    }



    void SpriteBatch::AddSprite(GameObject* object, const umath::vector2& spriteSize, const std::string& atlasName)
    {
        int mod = m_objects.size() * 4;

        m_objects.push_back(object);
        umath::rectangle tex = m_atlas->getTextureCoords(atlasName.c_str());


        m_spriteBuffer.addVertex(Vertex(umath::vector3(-spriteSize.x/2, -spriteSize.y/2, 0), umath::vector2(tex.left, tex.getBottom()))); // vasen alakulma
        m_spriteBuffer.addVertex(Vertex(umath::vector3(spriteSize.x/2, -spriteSize.y/2, 0), umath::vector2(tex.getRight(), tex.getBottom()))); // oikea alakulma
        m_spriteBuffer.addVertex(Vertex(umath::vector3(-spriteSize.x/2, spriteSize.y/2, 0), umath::vector2(tex.left, tex.top))); // vasen yläkulma
        m_spriteBuffer.addVertex(Vertex(umath::vector3(spriteSize.x/2, spriteSize.y/2, 0), umath::vector2(tex.getRight(), tex.top))); // oikea yläkulma
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
        m_spriteBuffer.setData();

        updateMatrixData();

        m_atlas->Bind();
        //shader->SetUniform("unifSampler", 0);
        shader->SetUniform("unifColor", 1, 1, 1, 1);

        uthGraphics.bindBuffer(ARRAY_BUFFER, m_matrixBuffer.getArrayBufferID());
        uthGraphics.setBufferData(ARRAY_BUFFER, m_matrixData.size() * sizeof(umath::matrix4), &m_matrixData, STATIC_DRAW);

        int matLoc = uthGraphics.getAttributeLocation(shader->getShaderID(), "attrMat");

        uthGraphics.enableVertexAttribArray(matLoc);
        uthGraphics.enableVertexAttribArray(matLoc + 1);
        uthGraphics.enableVertexAttribArray(matLoc + 2);
        uthGraphics.enableVertexAttribArray(matLoc + 3);
        uthGraphics.setVertexAttribPointer(matLoc, 4, FLOAT_TYPE, sizeof(umath::matrix4), (void*)0);
        uthGraphics.setVertexAttribPointer(matLoc + 1, 4, FLOAT_TYPE, sizeof(umath::matrix4), (void*)(4 * sizeof(float)));
        uthGraphics.setVertexAttribPointer(matLoc + 2, 4, FLOAT_TYPE, sizeof(umath::matrix4), (void*)(8 * sizeof(float)));
        uthGraphics.setVertexAttribPointer(matLoc + 3, 4, FLOAT_TYPE, sizeof(umath::matrix4), (void*)(12 * sizeof(float)));


        uthGraphics.bindBuffer(ARRAY_BUFFER, m_spriteBuffer.getArrayBufferID());
        shader->setAttributeData("attrPosition", 3, FLOAT_TYPE, sizeof(Vertex), (void*)0);
        shader->setAttributeData("attrUV", 2, FLOAT_TYPE, sizeof(Vertex), (void*)(3 * sizeof(float)));

        uthGraphics.bindBuffer(ELEMENT_ARRAY_BUFFER, m_spriteBuffer.getElementBufferID());
        uthGraphics.drawElements(TRIANGLES, m_spriteBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);
    }

    void SpriteBatch::updateMatrixData()
    {
        m_matrixData.clear();
        m_matrixData.reserve(m_objects.size() * 4);

        for (unsigned int i = 0; i < m_objects.size(); ++i)
        {
            for (int i = 0; i < 4; ++i)
                m_matrixData.push_back(m_objects[i]->transform.GetTransform());
        }
    }
    
}