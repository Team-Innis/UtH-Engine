#include <cmath>
#include <UtH/Math/Math.hpp>

namespace umath
{
	vector2::vector2()
			: x(0), y(0)
	{}
	vector2::vector2(float X, float Y)
		: x(X), y(Y)
	{}
	vector2::~vector2(){}

	float vector2::getLenght() const
	{	
		return sqrt(pow(x,2) + pow(y,2));
	}
	float vector2::getRadians() const
	{
		return atan2(y,x);
	}
	float vector2::getDegrees() const
	{
		return getRadians()*180.0/PI;
	}

	void vector2::Transform(const vector2 position)
	{
		x += position.x;
		y += position.y;
	}
	void vector2::RotateDegrees(const float degrees)
	{
		Rotate(degrees/180.0*PI);
	}
	void vector2::Rotate(const float radians)
	{
		if (radians == 0)
			return;

		const float cosA = cos(radians);
		const float sinA = sin(radians);
		const float oldX = x;
		x = oldX*cosA-y*sinA;
		y = oldX*sinA+y*cosA;
	}
	void vector2::Scale(const vector2 scale)
	{
		x*=scale.x;
		y*=scale.y;
	}

	vector2 operator -(const vector2& RightVal)
	{
		return vector2(-RightVal.x, -RightVal.y);
	}

	vector2 operator +(const vector2& LeftVal,const vector2& RightVal)
	{
		return vector2(LeftVal.x+RightVal.x,LeftVal.y+RightVal.y);
	}
	vector2 operator -(const vector2& LeftVal,const vector2& RightVal)
	{
		return vector2(LeftVal.x-RightVal.x,LeftVal.y-RightVal.y);
	}

	const vector2& operator +=(vector2& LeftVal,const vector2& RightVal)
	{
		LeftVal.x += RightVal.x;
		LeftVal.y += RightVal.y;
		return LeftVal;
	}
	const vector2& operator -=(vector2& LeftVal,const vector2& RightVal)
	{
		LeftVal.x -= RightVal.x;
		LeftVal.y -= RightVal.y;
		return LeftVal;
	}

	vector2 operator /(const vector2& LeftVal, const float& RightVal)
	{
		return vector2(LeftVal.x / RightVal,LeftVal.y / RightVal);
	}
	const vector2& operator /=(vector2& LeftVal, const float& RightVal)
	{
		LeftVal.x /= RightVal;
		LeftVal.y /= RightVal;
		return LeftVal;
	}

	bool operator ==(const vector2& LeftVal,const vector2& RightVal)
	{
		if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y)
			return true;
		return false;
	}
	bool operator !=(const vector2& LeftVal,const vector2& RightVal)
	{
		return !(LeftVal==RightVal);
	}

	vector2 operator *(const vector2& LeftVal, const float& RightVal)
	{
		return vector2(LeftVal.x * RightVal,LeftVal.y * RightVal);
	}
	vector2 operator *(const float& LeftVal, const vector2& RightVal)
	{
		return vector2(LeftVal * RightVal.x,LeftVal * RightVal.y);
	}

	const vector2& operator *=(vector2& LeftVal,const float& RightVal)
	{
		LeftVal.x *= RightVal;
		LeftVal.y *= RightVal;
		return LeftVal;
	}
}