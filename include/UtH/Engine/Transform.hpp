#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <UtH/Engine/Component.hpp>
#include <UtH/Math/Vector.hpp>
#include <UtH/Math/Matrix4.hpp>

namespace uth
{
    namespace Origin
    {
        enum Point
        {
            BottomLeft = 1,
            BottomCenter,
            BottomRight,
            MidLeft,
            Center,
            MidRight,
            TopLeft,
            TopCenter,
            TopRight
        };
    }

	class Transform : public Component
	{
	public:
		Transform(const std::string& name = "Transform");
		~Transform();

		void Move(const umath::vector2& offset);
		void Move(const float offsetX, const float offsetY);

		void SetPosition(const umath::vector2& position);
		void SetPosition(const float posX, const float posY);
		const umath::vector2& GetPosition() const;

		void SetSize(const umath::vector2& size);
		void SetSize(const float width, const float height);
		const umath::vector2& GetSize() const;

		void SetOrigin(const umath::vector2& origin);
        void SetOrigin(const Origin::Point = Origin::Point::Center);
		const umath::vector2& GetOrigin() const;

		void SetScale(const umath::vector2& scale);
		void SetScale(const float xScale, const float yScale);
		void SetScale(const float scale);
		const umath::vector2& GetScale() const;

		void SetRotation(const float angle);
		const float GetRotation() const;
		void Rotate(const float angle);

		void SetDepth(const float depth);
		const float GetDepth() const;

		void SetTransform(const umath::matrix4& modelTransform);
		// Adds to the current transform(multiplies). Mostly needed for layer transformation
		void AddTransform(const umath::matrix4& modelTransform);
		const umath::matrix4& GetTransform();

		umath::vector2 position;
		umath::vector2 size;
		umath::vector2 scale;
		umath::vector2 origin;
		float angle;
		float depth;

	private:
		void updateTransform();

		umath::matrix4 m_modelTransform;
        bool m_transformNeedsUpdate;
	};
}

#endif