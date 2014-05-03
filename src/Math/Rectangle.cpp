#include <cmath>
#include <cassert>
#include <UtH/Math/Math.hpp>

namespace umath
{
	rectangle::rectangle(){}
	rectangle::rectangle(const rectangle& rect)
		: x(rect.x),
		y(rect.y),
		width(rect.width),
		height(rect.height)
	{
		assert(!(width<0||height<0));
	}
	rectangle::rectangle(float X, float Y, float Width, float Height)
		: x(X),
		y(Y),
		width(Width),
		height(Height)
	{
		assert(!(width<0||height<0));
	}
	rectangle::rectangle(vector2 Position, float Width, float Height)
		: x(Position.x),
		y(Position.y),
		width(Width),
		height(Height)
	{
		assert(!(width<0||height<0));
	}
	rectangle::rectangle(vector2 Position, vector2 Size)
		: x(Position.x),
		y(Position.y),
		width(Size.x),
		height(Size.y)
	{
		assert(!(width<0||height<0));
	}

	rectangle::~rectangle()
	{}

	float rectangle::getRight() const
	{
		return x + width;
	}
	float rectangle::getBottom() const
	{
		return y + height;
	}

	bool rectangle::Intersects(rectangle otherRectangle) const
	{
		if (otherRectangle.getRight() < x)
			return false;
		if (getRight() < otherRectangle.x)
			return false;
		if (otherRectangle.getBottom() < y)
			return false;
		if (getBottom() < otherRectangle.y)
			return false;
		return true;
	}
	bool rectangle::Contains(vector2 Position) const
	{
		return Intersects(rectangle(Position,0,0));
	}
}