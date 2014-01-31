#pragma once
#ifndef RECTANGLE_H_UMATH
#define RECTANGLE_H_UMATH

#include <UtH\Math\Vector2.hpp>

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
				vector2 position, size;
			};
			struct
			{
				float x, y;
			};
		};

		float getRight();
		float getBottom();

		bool Intersects(rectangle Rectangle);
		bool Contains(vector2 Position);
	private:

	};
}
#endif