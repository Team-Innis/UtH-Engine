#include <cmath>
#include <UtH\Math\Math.hpp>

namespace umath
{
	rectangle::rectangle(){}
	rectangle::rectangle(float Left, float Top, float Width, float Height)
		: left(Left),
		  top(Top),
		  width(Width),
		  height(Height)
	{}
	rectangle::rectangle(vector2 Position, float Width, float Height)
		: position(Position),
		  width(Width),
		  height(Height)
	{}
	rectangle::rectangle(vector2 Position, vector2 Size)
		: position(Position),
		  size(Size)
	{}

	rectangle::~rectangle()
	{}
}