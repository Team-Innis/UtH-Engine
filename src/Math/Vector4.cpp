#include <cmath>
#include <UtH/Math/Math.hpp>


namespace umath
{
	vector4::vector4()
			: x(0), y(0),z(0),w(0)
	{}
	vector4::vector4(const vector3 Vec3, const double W)
		: 
		x(Vec3[0]),
		y(Vec3[1]),
		z(Vec3[2]),
		w(W)
	{}
	vector4::vector4(const double X, const double Y, const double Z, const double W)
		: x(X), y(Y), z(Z), w(W)
	{}
	vector4::~vector4(){}

	double vector4::getLenght()
	{	
		return sqrt(pow(x,2) + pow(y,2) + pow(z,2) + pow(w,2));
	}

	// Public
	// Operators
	
	const double& vector4::operator [](const unsigned int& index) const
	{
		return (&x)[index];
	}
	double& vector4::operator [](const unsigned int& index)
	{
		return (&x)[index];
	}


	vector4 operator -(const vector4& RightVal)
	{
		return vector4(-RightVal.x, -RightVal.y,-RightVal.z, -RightVal.w);
	}

	vector4 operator +(const vector4& LeftVal,const vector4& RightVal)
	{
		return vector4(LeftVal.x+RightVal.x,LeftVal.y+RightVal.y,LeftVal.z+RightVal.z,LeftVal.w+RightVal.w);
	}
	vector4 operator -(const vector4& LeftVal,const vector4& RightVal)
	{
		return vector4(LeftVal.x-RightVal.x,LeftVal.y-RightVal.y,LeftVal.z-RightVal.z,LeftVal.w-RightVal.w);
	}

	const vector4& operator +=(vector4& LeftVal,const vector4& RightVal)
	{
		LeftVal.x += RightVal.x;
		LeftVal.y += RightVal.y;
		LeftVal.z += RightVal.z;
		LeftVal.w += RightVal.w;
		return LeftVal;
	}
	const vector4& operator -=(vector4& LeftVal,const vector4& RightVal)
	{
		LeftVal.x -= RightVal.x;
		LeftVal.y -= RightVal.y;
		LeftVal.z -= RightVal.z;
		LeftVal.w -= RightVal.w;
		return LeftVal;
	}

	vector4 operator /(const vector4& LeftVal, const double& RightVal)
	{
		return vector4(LeftVal.x / RightVal,LeftVal.y / RightVal, LeftVal.z / RightVal, LeftVal.w / RightVal);
	}
	const vector4& operator /=(vector4& LeftVal, const double& RightVal)
	{
		LeftVal.x /= (double)RightVal;
		LeftVal.y /= (double)RightVal;
		LeftVal.z /= (double)RightVal;
		LeftVal.w /= (double)RightVal;
		return LeftVal;
	}

	bool operator ==(const vector4& LeftVal,const vector4& RightVal)
	{
		if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y && LeftVal.z == RightVal.z && LeftVal.w == RightVal.w)
			return true;
		return false;
	}
	bool operator !=(const vector4& LeftVal,const vector4& RightVal)
	{
		return !(LeftVal == RightVal);
	}

	vector4 operator *(const vector4& LeftVal, const double& RightVal)
	{
		return vector4(LeftVal.x * RightVal,LeftVal.y * RightVal, LeftVal.z * RightVal, LeftVal.w * RightVal);
	}
	vector4 operator *(const double& LeftVal, const vector4& RightVal)
	{
		return vector4(LeftVal * RightVal.x,LeftVal * RightVal.y, LeftVal * RightVal.z, LeftVal * RightVal.w);
	}

	const vector4& operator *=(vector4& LeftVal,const double& RightVal)
	{
		LeftVal.x *= RightVal;
		LeftVal.y *= RightVal;
		LeftVal.z *= RightVal;
		LeftVal.w *= RightVal;
		return LeftVal;
	}
}