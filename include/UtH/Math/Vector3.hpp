#pragma once
#ifndef VECTOR3_H_UMATH
#define VECTOR3_H_UMATH

namespace umath
{
	class vector3
	{
	public:
		vector3();
		vector3(float X, float Y, float Z);
		~vector3();

		float getLenght();
		//float getAngle();

		float x,y,z;
			
		const float& operator [](const unsigned int& index) const;
		float& operator [](const unsigned int& index);
	private:

	};

	vector3 operator -(const vector3& RightVal);

	vector3 operator +(const vector3& LeftVal,const vector3& RightVal);
	vector3 operator -(const vector3& LeftVal,const vector3& RightVal);

	const vector3& operator +=(vector3& LeftVal,const vector3& RightVal);
	const vector3& operator -=(vector3& LeftVal,const vector3& RightVal);

	vector3 operator /(const vector3& LeftVal,const float& RightVal);
	const vector3& operator /=(vector3& LeftVal,const float& RightVal);

	bool operator ==(const vector3& LeftVal,const vector3& RightVal);
	bool operator !=(const vector3& LeftVal,const vector3& RightVal);

	vector3 operator *(const vector3& LeftVal, const float& RightVal);
	vector3 operator *(const float& LeftVal, const vector3& RightVal);

	const vector3& operator *=(vector3& LeftVal, const float& RightVal);
}
#endif