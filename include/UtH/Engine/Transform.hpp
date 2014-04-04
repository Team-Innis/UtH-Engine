#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <UtH/Engine/Component.hpp>
#include <UtH/Math/Vector.hpp>
#include <UtH/Math/Matrix4.hpp>

namespace uth
{
	class Transform : public Component
	{
	public:
		Transform(const std::string& name = "Transform");
		~Transform();

		void Move(const umath::vector2& offset);
		void Move(float offsetX, float offsetY);

		void SetPosition(const umath::vector2& position);
		void SetPosition(float posX, float posY);
		const umath::vector2& GetPosition() const;

		void SetSize(const umath::vector2& size);
		void SetSize(float width, float height);
		const umath::vector2& GetSize() const;

		void SetScale(const umath::vector2& scale);
		void SetScale(float xScale, float yScale);
		const umath::vector2& GetScale() const;

		void SetRotation(float angle);
		const float GetRotation() const;
		void Rotate(float angle);

		void SetDepth(float depth);
		const float GetDepth() const;

		void SetTransform(const umath::matrix4& modelTransform);
		// Adds to the current transform(multiplies). Mostly needed for layer transformation
		void AddTransform(const umath::matrix4& modelTransform);
		const umath::matrix4& GetTransform();

		umath::vector2 position;
		umath::vector2 size;
		umath::vector2 scale;
		float angle;
		float depth;

	private:
		void updateTransform();

		umath::matrix4 m_modelTransform;
        bool m_transformNeedsUpdate;
	};
}

#endif