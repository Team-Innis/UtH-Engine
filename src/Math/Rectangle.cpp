#include <cmath>
#include <cassert>
#include <UtH/Math/Math.hpp>

namespace umath
{
	rectangle::rectangle(){}
	rectangle::rectangle(double Left, double Top, double Width, double Height)
		: left(Left),
		  top(Top),
		  width(Width),
		  height(Height)
	{
		assert(!(width<0||height<0));
	}
	rectangle::rectangle(vector2 Position, double Width, double Height)
		: left(Position.x),
		  top(Position.y),
		  width(Width),
		  height(Height)
	{
		assert(!(width<0||height<0));
	}
	rectangle::rectangle(vector2 Position, vector2 Size)
		: left(Position.x),
		  top(Position.y),
		  width(Size.x),
		  height(Size.y)
	{
		assert(!(width<0||height<0));
	}

	rectangle::~rectangle()
	{}
	
	double rectangle::getRight() const
	{
		return left + width;
	}
	double rectangle::getBottom() const
	{
		return top + height;
	}
	
	bool rectangle::Intersects(rectangle otherRectangle) const
	{
		if (otherRectangle.getRight() < left)
			return false;
		if (getRight() < otherRectangle.left)
			return false;
		if (otherRectangle.getBottom() < top)
			return false;
		if (getBottom() < otherRectangle.top)
			return false;
		return true;
	}
	bool rectangle::Contains(vector2 Position) const
	{
		return Intersects(rectangle(Position,0,0));
	}
}