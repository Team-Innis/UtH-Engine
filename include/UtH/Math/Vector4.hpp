#pragma once
#ifndef VECTOR4_H_UMATH
#define VECTOR4_H_UMATH

#include <UtH\Math\Vector3.hpp>

namespace umath
{
	class vector4
	{
	public:
		vector4();
		vector4(const vector3 Vec3, const float W);
		vector4(const float X, const float Y, const float Z, const float W);
		~vector4();

		float getLenght();

		union
		{
			struct
			{
				float x,y,z,w;
			};
			struct
			{
				float r,g,b,a;
			};
		};

		const float& operator [](const unsigned int& index) const;
		float& operator [](const unsigned int& index);
	private:
	};
	

	vector4 operator -(const vector4& RightVal);

	vector4 operator +(const vector4& LeftVal,const vector4& RightVal);
	vector4 operator -(const vector4& LeftVal,const vector4& RightVal);

	const vector4& operator +=(vector4& LeftVal,const vector4& RightVal);
	const vector4& operator -=(vector4& LeftVal,const vector4& RightVal);

	vector4 operator /(const vector4& LeftVal,const float& RightVal);
	const vector4& operator /=(vector4& LeftVal,const float& RightVal);

	bool operator ==(const vector4& LeftVal,const vector4& RightVal);
	bool operator !=(const vector4& LeftVal,const vector4& RightVal);

	vector4 operator *(const vector4& LeftVal, const float& RightVal);
	vector4 operator *(const float& LeftVal, const vector4& RightVal);

	const vector4& operator *=(vector4& LeftVal, const float& RightVal);

}
#endif