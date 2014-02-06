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
		rectangle(double Left, double Top, double Width, double Height);
		rectangle(vector2 Position, double Width, double Height);
		rectangle(vector2 Position, vector2 Size);

		~rectangle();

		union
		{
			struct 
			{
				double left, top, width, height;
			};
			struct
			{
				double x, y;
			};
		};

		double getRight() const;
		double getBottom() const;

		bool Intersects(rectangle otherRectangle) const;
		bool Contains(vector2 Position) const;
	private:

	};
}
#endif