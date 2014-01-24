#pragma once
#ifndef MATRIX4_H_UMATH
#define MATRIX4_H_UMATH

#include <umath\Vector4.hpp>
#include <umath\Matrix3.hpp>

namespace umath
{
	class Matrix4
	{
	public:
		/**
		Creates Identity Matrix
		*/
		Matrix4();
		Matrix4(const float* FirstElement);
		Matrix4(const Matrix3 mat3);
		Matrix4(
			const vector4& Row1,
			const vector4& Row2,
			const vector4& Row3,
			const vector4& Row4);
		Matrix4(
			const float& r1s1,const float& r1s2,const float& r1s3,const float& r1s4,
			const float& r2s1,const float& r2s2,const float& r2s3,const float& r2s4,
			const float& r3s1,const float& r3s2,const float& r3s3,const float& r3s4,
			const float& r4s1,const float& r4s2,const float& r4s3,const float& r4s4);
		static const Matrix4 Identity;
		~Matrix4();

		float* FirstElement() const;

		const vector4& operator [](const unsigned int& index) const;
		vector4& operator [](const unsigned int& index);

	private:
		vector4 r1,r2,r3,r4;

	};
	
	Matrix4 operator *(const Matrix4& LeftVal, const Matrix4& RightVal);
	const Matrix4 operator *=(Matrix4& LeftVal, const Matrix4& RightVal);

	vector4 operator *(const vector4& LeftVal, const Matrix4& RightVal);
	const vector4 operator *=(vector4& LeftVal, const Matrix4& RightVal);
	
}

#endif