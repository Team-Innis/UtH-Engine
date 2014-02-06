#pragma once
#ifndef VECTOR4_H_UMATH
#define VECTOR4_H_UMATH

#include <UtH/Math/Vector3.hpp>

namespace umath
{
	class vector4
	{
	public:
		vector4();
		vector4(const vector3 Vec3, const double W);
		vector4(const double X, const double Y, const double Z, const double W);
		~vector4();

		double getLenght();

		union
		{
			struct
			{
				double x,y,z,w;
			};
			struct
			{
				double r,g,b,a;
			};
		};

		const double& operator [](const unsigned int& index) const;
		double& operator [](const unsigned int& index);
	private:
	};
	

	vector4 operator -(const vector4& RightVal);

	vector4 operator +(const vector4& LeftVal,const vector4& RightVal);
	vector4 operator -(const vector4& LeftVal,const vector4& RightVal);

	const vector4& operator +=(vector4& LeftVal,const vector4& RightVal);
	const vector4& operator -=(vector4& LeftVal,const vector4& RightVal);

	vector4 operator /(const vector4& LeftVal,const double& RightVal);
	const vector4& operator /=(vector4& LeftVal,const double& RightVal);

	bool operator ==(const vector4& LeftVal,const vector4& RightVal);
	bool operator !=(const vector4& LeftVal,const vector4& RightVal);

	vector4 operator *(const vector4& LeftVal, const double& RightVal);
	vector4 operator *(const double& LeftVal, const vector4& RightVal);

	const vector4& operator *=(vector4& LeftVal, const double& RightVal);

}
#endif