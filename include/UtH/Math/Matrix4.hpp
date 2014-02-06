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
		matrix4(const float* FirstElement);
		matrix4(const matrix3 mat3);
		matrix4(
			const vector4& Row1,
			const vector4& Row2,
			const vector4& Row3,
			const vector4& Row4);
		matrix4(
			const float& r1c1,const float& r1c2,const float& r1c3,const float& r1c4,
			const float& r2c1,const float& r2c2,const float& r2c3,const float& r2c4,
			const float& r3c1,const float& r3c2,const float& r3c3,const float& r3c4,
			const float& r4c1,const float& r4c2,const float& r4c3,const float& r4c4);
		static const matrix4 Identity;
		~matrix4();

		float* FirstElement() const;

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