#pragma once
#ifndef MATRIX3_H_UMATH
#define MATRIX3_H_UMATH

#include <UtH\Math\Vector3.hpp>

namespace umath
{
	class matrix3
	{
	public:
		/**
		Creates Identity Matrix
		*/
		matrix3();
		matrix3(const float* FirstElement);
		matrix3(
			const vector3& Row1,
			const vector3& Row2,
			const vector3& Row3);
		matrix3(
			const float& c1r1,const float& c1r2,const float& c1r3,
			const float& c2r1,const float& c2r2,const float& c2r3,
			const float& c3r1,const float& c3r2,const float& c3r3);
		~matrix3();

		float* FirstElement();

		const vector3& operator [](const unsigned int& index) const;
		vector3& operator [](const unsigned int& index);

	private:
		vector3 r1,r2,r3;

	};

	matrix3 operator *(const matrix3& LeftVal, const matrix3& RightVal);
	const matrix3 operator *=(matrix3& LeftVal, const matrix3& RightVal);
	
	vector3 operator *(const vector3& LeftVal, const matrix3& RightVal);
	const vector3 operator *=(vector3& LeftVal, const matrix3& RightVal);
}

#endif