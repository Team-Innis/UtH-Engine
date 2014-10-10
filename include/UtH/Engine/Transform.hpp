#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <pmath/PMath.hpp>

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

	class Object;
	namespace TMX
	{
		class Tile;
	}
	class Transform
	{
	public:
		Transform(Object* parent);
		~Transform();

		void Move(const pmath::Vec2& offset);
		void Move(const float offsetX, const float offsetY);

		void SetPosition(const pmath::Vec2& position);
		void SetPosition(const float posX, const float posY);
		const pmath::Vec2& GetPosition() const;

		//[[deprecated("Has been replaced with ScaleToSize")]]
		void SetSize(const pmath::Vec2& size);
		//[[deprecated("Has been replaced with ScaleToSize")]]
		void SetSize(const float width, const float height);
		void ScaleToSize(const pmath::Vec2& size);
		void ScaleToSize(const float width, const float height);
		const pmath::Vec2& GetSize() const;

		void SetOrigin(const pmath::Vec2& origin);
		void SetOrigin(const int originPoint = Origin::Point::Center);
		const pmath::Vec2& GetOrigin() const;

		void SetScale(const pmath::Vec2& scale);
		void SetScale(const float xScale, const float yScale);
		void SetScale(const float scale);
		const pmath::Vec2& GetScale() const;

		void SetRotation(const float degrees);
		const float GetRotation() const;
		void Rotate(const float degrees);

        pmath::Rect GetBounds() const;
        pmath::Rect GetTransformedBounds() const;

		void SetTransform(const pmath::Mat4& modelTransform);
		// Adds to the current transform(multiplies). Mostly needed for layer transformation
		void AddTransform(const pmath::Mat4& modelTransform);
		const pmath::Mat4& GetTransform() const;

		Object* parent;

	private:
		// friends so they can alter transform size
		friend class AnimatedSprite;
		friend class Camera;
		friend class Sprite;
		friend class Text;
		friend class ParticleSystem;
		friend class TMX::Tile;

		void setSize(const pmath::Vec2& size);
		void setSize(const float width, const float height);

		pmath::Vec2 m_position;
		pmath::Vec2 m_size;
		pmath::Vec2 m_scale;
		pmath::Vec2 m_origin;
		float m_angle;

		void updateTransform() const;

		mutable pmath::Mat4 m_modelTransform;
        mutable pmath::Mat4 m_combinedTransform;
		mutable bool m_transformNeedsUpdate;
	};
}

#endif