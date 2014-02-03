#pragma once
#ifndef MATRIX4_H_UMATH
#define MATRIX4_H_UMATH

#include <UtH/Math/Vector4.hpp>
#include <UtH/Math/Matrix3.hpp>

namespace umath
{
	class matrix4
	{
	public:
		/**
		Creates Identity Matrix
		*/
		matrix4();
		matrix4(const double* FirstElement);
		matrix4(const matrix3 mat3);
		matrix4(
			const vector4& Row1,
			const vector4& Row2,
			const vector4& Row3,
			const vector4& Row4);
		matrix4(
			const double& r1s1,const double& r1s2,const double& r1s3,const double& r1s4,
			const double& r2s1,const double& r2s2,const double& r2s3,const double& r2s4,
			const double& r3s1,const double& r3s2,const double& r3s3,const double& r3s4,
			const double& r4s1,const double& r4s2,const double& r4s3,const double& r4s4);
		static const matrix4 Identity;
		~matrix4();

		double* FirstElement() const;

		const vector4& operator [](const unsigned int& index) const;
		vector4& operator [](const unsigned int& index);

	private:
		vector4 r1,r2,r3,r4;

	};
	
	matrix4 operator *(const matrix4& LeftVal, const matrix4& RightVal);
	const matrix4 operator *=(matrix4& LeftVal, const matrix4& RightVal);

	vector4 operator *(const vector4& LeftVal, const matrix4& RightVal);
	const vector4 operator *=(vector4& LeftVal, const matrix4& RightVal);
	
}

#endif