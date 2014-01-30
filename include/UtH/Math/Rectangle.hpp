#pragma once
#ifndef RECTANGLE_H_UMATH
#define RECTANGLE_H_UMATH

#include <umath\Vector2.hpp>

namespace umath
{
	class Rectangle
	{
	public:

		Rectangle();
		Rectangle(float Left, float Top, float Width, float Height);
		Rectangle(vector2 Position, float Width, float Height);
		Rectangle(vector2 Position, vector2 Size);

		bool intersects(Rectangle rectangle);
		bool contains(vector2 Position);

		~Rectangle();
		float width, height, left, top;

	private:

	};
}
#endif