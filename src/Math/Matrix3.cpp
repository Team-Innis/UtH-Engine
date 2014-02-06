#include <UtH/Math/Matrix3.hpp>
#include <UtH/Math/Math.hpp>

namespace umath
{
	matrix3::matrix3()
		:
		r1(vector3(1.f,0.f,0.f)),
		r2(vector3(0.f,1.f,0.f)),
		r3(vector3(0.f,0.f,1.f))
	{}
	matrix3::matrix3(const float* fe)
		:
		r1(fe[0],fe[1],fe[2]),
		r2(fe[3],fe[4],fe[5]),
		r3(fe[6],fe[7],fe[8])
	{}
	matrix3::matrix3(
		const vector3& Row1,
		const vector3& Row2,
		const vector3& Row3)
		: 
		r1(Row1),
		r2(Row2),
		r3(Row3)
	{}
	matrix3::matrix3(
		const float& r1c1,const float& r1c2,const float& r1c3,
		const float& r2c1,const float& r2c2,const float& r2c3,
		const float& r3c1,const float& r3c2,const float& r3c3)
		:
		r1(r1c1,r1c2,r1c3),
		r2(r2c1,r2c2,r2c3),
		r3(r3c1,r3c2,r3c3)
	{}
	matrix3::~matrix3()
	{}
	
	float* matrix3::FirstElement()
	{
		return (float*)&r1.x;
	}
	
	const vector3& matrix3::operator [](const unsigned int& index) const
	{
		return (&r1)[index];
	}
	vector3& matrix3::operator [](const unsigned int& index)
	{
		return (&r1)[index];
	}
	
	matrix3 operator *(const matrix3& LM, const matrix3& RM)
	{
		const float L[3][3] = 
		{
			LM[0][0],
			LM[0][1],
			LM[0][2],
			LM[1][0],
			LM[1][1],
			LM[1][2],
			LM[2][0],
			LM[2][1],
			LM[2][2]
		};
		const float R[3][3] = 
		{
			RM[0][0],
			RM[0][1],
			RM[0][2],
			RM[1][0],
			RM[1][1],
			RM[1][2],
			RM[2][0],
			RM[2][1],
			RM[2][2]
		};


		return matrix3(
			L[0][0] * R[0][0] + L[1][0] * R[0][1] + L[2][0] * R[0][2],
			L[0][1] * R[0][0] + L[1][1] * R[0][1] + L[2][1] * R[0][2],
			L[0][2] * R[0][0] + L[1][2] * R[0][1] + L[2][2] * R[0][2],
			L[0][0] * R[1][0] + L[1][0] * R[1][1] + L[2][0] * R[1][2],
			L[0][1] * R[1][0] + L[1][1] * R[1][1] + L[2][1] * R[1][2],
			L[0][2] * R[1][0] + L[1][2] * R[1][1] + L[2][2] * R[1][2],
			L[0][0] * R[2][0] + L[1][0] * R[2][1] + L[2][0] * R[2][2],
			L[0][1] * R[2][0] + L[1][1] * R[2][1] + L[2][1] * R[2][2],
			L[0][2] * R[2][0] + L[1][2] * R[2][1] + L[2][2] * R[2][2]
			);
	}
	const matrix3 operator *=(matrix3& LeftVal, const matrix3& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}
	
	vector3 operator *(const vector3& RV, const matrix3& LM)
	{
		const float L[3][3] = 
		{
			LM[0][0],
			LM[0][1],
			LM[0][2],
			LM[1][0],
			LM[1][1],
			LM[1][2],
			LM[2][0],
			LM[2][1],
			LM[2][2]
		};
		const float R[4] = 
		{
			RV[0],
			RV[1],
			RV[2]
		};

		return vector3(
			L[0][0] * R[0] + L[0][1] * R[1] + L[0][2] * R[2],
			L[1][0] * R[0] + L[1][1] * R[1] + L[1][2] * R[2],
			L[2][0] * R[0] + L[2][1] * R[1] + L[2][2] * R[2]
			);
	}
	const vector3 operator *=(vector3& LeftVal, const matrix3& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}
}