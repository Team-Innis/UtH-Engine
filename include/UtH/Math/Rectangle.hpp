#pragma once
#ifndef RECTANGLE_H_UMATH
#define RECTANGLE_H_UMATH

#include <UtH/Math/Vector2.hpp>

namespace umath
{
	class rectangle
	{
	public:
		rectangle();
		rectangle(float Left, float Top, float Width, float Height);
		rectangle(vector2 Position, float Width, float Height);
		rectangle(vector2 Position, vector2 Size);

		~rectangle();

		union
		{
			struct 
			{
				float left, top, width, height;
			};
			struct
			{
				float x, y;
			};
		};

		float getRight() const;
		float getBottom() const;

		bool Intersects(rectangle otherRectangle) const;
		bool Contains(vector2 Position) const;
	private:

	};
}
#endif