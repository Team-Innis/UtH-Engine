#pragma once
#ifndef MATRIX3_H_UMATH
#define MATRIX3_H_UMATH

#include <umath\Vector3.hpp>

namespace umath
{
	class Matrix3
	{
	public:
		/**
		Creates Identity Matrix
		*/
		Matrix3();
		Matrix3(const float* FirstElement);
		Matrix3(
			const vector3& Column1,
			const vector3& Column2,
			const vector3& Column3);
		Matrix3(
			const float& c1r1,const float& c1r2,const float& c1r3,
			const float& c2r1,const float& c2r2,const float& c2r3,
			const float& c3r1,const float& c3r2,const float& c3r3);
		~Matrix3();

		float* FirstElement();

		const vector3& operator [](const unsigned int& index) const;
		vector3& operator [](const unsigned int& index);

	private:
		vector3 c1,c2,c3;

	};

	Matrix3 operator *(const Matrix3& LeftVal, const Matrix3& RightVal);
	const Matrix3 operator *=(Matrix3& LeftVal, const Matrix3& RightVal);
	
}

#endif