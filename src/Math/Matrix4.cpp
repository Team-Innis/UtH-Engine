#include <UtH/Math/Matrix4.hpp>
#include <UtH/Math/Math.hpp>

namespace umath
{
	const matrix4 matrix4::Identity;
	
	matrix4::matrix4()
		:
		r1(vector4(1.f,0.f,0.f,0.f)),
		r2(vector4(0.f,1.f,0.f,0.f)),
		r3(vector4(0.f,0.f,1.f,0.f)),
		r4(vector4(0.f,0.f,0.f,1.f))
	{}
	matrix4::matrix4(const float* fe)
		:
		r1(fe[0],fe[1],fe[2],fe[3]),
		r2(fe[4],fe[5],fe[6],fe[7]),
		r3(fe[8],fe[9],fe[10],fe[11]),
		r4(fe[12],fe[13],fe[14],fe[15])
	{}
	matrix4::matrix4(const matrix3& mat3)
		:
		r1(mat3[0],0.f),
		r2(mat3[1],0.f),
		r3(mat3[2],0.f),
		r4(0.f,0.f,0.f,1.f)
	{}
	matrix4::matrix4(
		const vector4& Row1,
		const vector4& Row2,
		const vector4& Row3,
		const vector4& Row4)
		: 
		r1(Row1),
		r2(Row2),
		r3(Row3),
		r4(Row4)
	{}
	matrix4::matrix4(
		const float& r1c1,const float& r1c2,const float& r1c3,const float& r1c4,
		const float& r2c1,const float& r2c2,const float& r2c3,const float& r2c4,
		const float& r3c1,const float& r3c2,const float& r3c3,const float& r3c4,
		const float& r4c1,const float& r4c2,const float& r4c3,const float& r4c4)
		:
		r1(r1c1,r1c2,r1c3,r1c4),
		r2(r2c1,r2c2,r2c3,r2c4),
		r3(r3c1,r3c2,r3c3,r3c4),
		r4(r4c1,r4c2,r4c3,r4c4)
	{}
	matrix4::~matrix4()
	{}
	
	float* matrix4::FirstElement() const
	{
		return (float*)&r1.x;
	}
    
    const matrix3 matrix4::getMatrix3() const
    {
        return matrix3(
            r1[0], r1[1], r1[3],
            r2[0], r2[1], r2[3],
            r4[0], r4[1], r4[3]
        );
    }
	
	const vector4& matrix4::operator [](const unsigned int& index) const
	{
		return (&r1)[index];
	}
	vector4& matrix4::operator [](const unsigned int& index)
	{
		return (&r1)[index];
	}
	
	matrix4 operator *(const matrix4& LM, const matrix4& RM)
	{
		const float L[4][4] = 
		{
			LM[0][0],
			LM[0][1],
			LM[0][2],
			LM[0][3],
			LM[1][0],
			LM[1][1],
			LM[1][2],
			LM[1][3],
			LM[2][0],
			LM[2][1],
			LM[2][2],
			LM[2][3],
			LM[3][0],
			LM[3][1],
			LM[3][2],
			LM[3][3]
		};
		const float R[4][4] = 
		{
			RM[0][0],
			RM[0][1],
			RM[0][2],
			RM[0][3],
			RM[1][0],
			RM[1][1],
			RM[1][2],
			RM[1][3],
			RM[2][0],
			RM[2][1],
			RM[2][2],
			RM[2][3],
			RM[3][0],
			RM[3][1],
			RM[3][2],
			RM[3][3]
		};


		return matrix4(
			L[0][0] * R[0][0] + L[0][1] * R[1][0] + L[0][2] * R[2][0] + L[0][3] * R[3][0],
			L[0][0] * R[0][1] + L[0][1] * R[1][1] + L[0][2] * R[2][1] + L[0][3] * R[3][1],
			L[0][0] * R[0][2] + L[0][1] * R[1][2] + L[0][2] * R[2][2] + L[0][3] * R[3][2],
			L[0][0] * R[0][3] + L[0][1] * R[1][3] + L[0][2] * R[2][3] + L[0][3] * R[3][3],
			L[1][0] * R[0][0] + L[1][1] * R[1][0] + L[1][2] * R[2][0] + L[1][3] * R[3][0],
			L[1][0] * R[0][1] + L[1][1] * R[1][1] + L[1][2] * R[2][1] + L[1][3] * R[3][1],
			L[1][0] * R[0][2] + L[1][1] * R[1][2] + L[1][2] * R[2][2] + L[1][3] * R[3][2],
			L[1][0] * R[0][3] + L[1][1] * R[1][3] + L[1][2] * R[2][3] + L[1][3] * R[3][3],
			L[2][0] * R[0][0] + L[2][1] * R[1][0] + L[2][2] * R[2][0] + L[2][3] * R[3][0],
			L[2][0] * R[0][1] + L[2][1] * R[1][1] + L[2][2] * R[2][1] + L[2][3] * R[3][1],
			L[2][0] * R[0][2] + L[2][1] * R[1][2] + L[2][2] * R[2][2] + L[2][3] * R[3][2],
			L[2][0] * R[0][3] + L[2][1] * R[1][3] + L[2][2] * R[2][3] + L[2][3] * R[3][3],
			L[3][0] * R[0][0] + L[3][1] * R[1][0] + L[3][2] * R[2][0] + L[3][3] * R[3][0],
			L[3][0] * R[0][1] + L[3][1] * R[1][1] + L[3][2] * R[2][1] + L[3][3] * R[3][1],
			L[3][0] * R[0][2] + L[3][1] * R[1][2] + L[3][2] * R[2][2] + L[3][3] * R[3][2],
			L[3][0] * R[0][3] + L[3][1] * R[1][3] + L[3][2] * R[2][3] + L[3][3] * R[3][3]
			);
	}
	matrix4& operator *=(matrix4& LeftVal, const matrix4& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}

	
	vector4 operator *(const matrix4& LM, const vector4& RV)
	{
		const float L[4][4] = 
		{
			LM[0][0],
			LM[0][1],
			LM[0][2],
			LM[0][3],
			LM[1][0],
			LM[1][1],
			LM[1][2],
			LM[1][3],
			LM[2][0],
			LM[2][1],
			LM[2][2],
			LM[2][3],
			LM[3][0],
			LM[3][1],
			LM[3][2],
			LM[3][3]
		};
		const float R[4] = 
		{
			RV[0],
			RV[1],
			RV[2],
			RV[3]
		};

		return vector4(
			L[0][0] * R[0] + L[0][1] * R[1] + L[0][2] * R[2] + L[0][3] * R[3],
			L[1][0] * R[0] + L[1][1] * R[1] + L[1][2] * R[2] + L[1][3] * R[3],
			L[2][0] * R[0] + L[2][1] * R[1] + L[2][2] * R[2] + L[2][3] * R[3],
			L[3][0] * R[0] + L[3][1] * R[1] + L[3][2] * R[2] + L[3][3] * R[3]
			);
	}
	vector4& operator *=(vector4& LeftVal, const matrix4& RightVal)
	{
		LeftVal = RightVal * LeftVal;
		return LeftVal;
	}

}