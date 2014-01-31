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
	
	float rectangle::getRight()
	{
		return left + width;
	}
	float rectangle::getBottom()
	{
		return top + height;
	}
	
	bool rectangle::Intersects(rectangle Rectangle)
	{
		if (Rectangle.getRight() < left)
			return false;
		if (getRight() < Rectangle.left)
			return false;
		if (Rectangle.getBottom() < top)
			return false;
		if (getBottom() < Rectangle.top)
			return false;
		return true;
	}
	bool rectangle::Contains(vector2 Position)
	{
		return Intersects(rectangle(Position,0,0));
	}
}