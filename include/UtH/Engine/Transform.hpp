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
		Transform(const std::string name = "Transform");
		~Transform();

		void Move(umath::vector2 offset);
		void Move(float offsetX, float offsetY);

		void SetPosition(umath::vector2 position);
		void SetPosition(float posX, float posY);
		const umath::vector2& GetPosition() const;

		void SetSize(umath::vector2 size);
		void SetSize(float width, float height);
		const umath::vector2& GetSize() const;

		void SetRotation(float angle);
		const float GetRotation() const;
		void Rotate(float angle);

		void SetDepth(float depth);
		const float GetDepth() const;

		const umath::matrix4& GetTransform();

		umath::vector2 position;
		umath::vector2 size;
		float angle;
		float depth;

	private:
		void updateTransform();

		bool transformNeedsUpdate;

		umath::matrix4 m_modelTransform;

	};
}

#endif