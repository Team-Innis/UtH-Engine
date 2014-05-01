#include <cmath>
#include <UtH/Math/Math.hpp>

namespace umath
{
	vector3::vector3()
		: x(0), y(0),z(0)
	{}
	vector3::vector3(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{}
	vector3::~vector3(){}
	
	float vector3::getLengthSquared() const
	{	
		return pow(x,2) + pow(y,2) + pow(z,2);
	}
	float vector3::getLength() const
	{	
		return sqrt(getLengthSquared());
	}
	
	// Public
	// Operators
	
	const float& vector3::operator [](const unsigned int& index) const
	{
		return (&x)[index];
	}
	float& vector3::operator [](const unsigned int& index)
	{
		return (&x)[index];
	}

	vector3 operator -(const vector3& RightVal)
	{
		return vector3(-RightVal.x, -RightVal.y,-RightVal.z);
	}

	vector3 operator +(const vector3& LeftVal,const vector3& RightVal)
	{
		return vector3(LeftVal.x+RightVal.x,LeftVal.y+RightVal.y,LeftVal.z+RightVal.z);
	}
	vector3 operator -(const vector3& LeftVal,const vector3& RightVal)
	{
		return vector3(LeftVal.x-RightVal.x,LeftVal.y-RightVal.y,LeftVal.z-RightVal.z);
	}

	const vector3& operator +=(vector3& LeftVal,const vector3& RightVal)
	{
		LeftVal.x += RightVal.x;
		LeftVal.y += RightVal.y;
		LeftVal.z += RightVal.z;
		return LeftVal;
	}
	const vector3& operator -=(vector3& LeftVal,const vector3& RightVal)
	{
		LeftVal.x -= RightVal.x;
		LeftVal.y -= RightVal.y;
		LeftVal.z -= RightVal.z;
		return LeftVal;
	}

	vector3 operator /(const vector3& LeftVal, const float& RightVal)
	{
		return vector3(LeftVal.x / RightVal,LeftVal.y / RightVal, LeftVal.z / RightVal);
	}
	const vector3& operator /=(vector3& LeftVal, const float& RightVal)
	{
		LeftVal.x /= (float)RightVal;
		LeftVal.y /= (float)RightVal;
		LeftVal.z /= (float)RightVal;
		return LeftVal;
	}

	bool operator ==(const vector3& LeftVal,const vector3& RightVal)
	{
		if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y && LeftVal.z == RightVal.z)
			return true;
		return false;
	}
	bool operator !=(const vector3& LeftVal,const vector3& RightVal)
	{
		return !(LeftVal == RightVal);
	}

	vector3 operator *(const vector3& LeftVal, const float& RightVal)
	{
		return vector3(LeftVal.x * RightVal,LeftVal.y * RightVal, LeftVal.z * RightVal);
	}
	vector3 operator *(const float& LeftVal, const vector3& RightVal)
	{
		return vector3(LeftVal * RightVal.x,LeftVal * RightVal.y, LeftVal * RightVal.z);
	}

	const vector3& operator *=(vector3& LeftVal,const float& RightVal)
	{
		LeftVal.x *= RightVal;
		LeftVal.y *= RightVal;
		LeftVal.z *= RightVal;
		return LeftVal;
	}
}