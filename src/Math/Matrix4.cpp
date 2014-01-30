#include <umath\Matrix4.hpp>
#include <umath\Math.hpp>

namespace umath
{
	const Matrix4 Matrix4::Identity;
	
	Matrix4::Matrix4()
		:
		r1(vector4(1.f,0.f,0.f,0.f)),
		r2(vector4(0.f,1.f,0.f,0.f)),
		r3(vector4(0.f,0.f,1.f,0.f)),
		r4(vector4(0.f,0.f,0.f,1.f))
	{}
	Matrix4::Matrix4(const float* fe)
		:
		r1(fe[0],fe[1],fe[2],fe[3]),
		r2(fe[4],fe[5],fe[6],fe[7]),
		r3(fe[8],fe[9],fe[10],fe[11]),
		r4(fe[12],fe[13],fe[14],fe[15])
	{}
	Matrix4::Matrix4(const Matrix3 mat3)
		:
		r1(mat3[0],0.f),
		r2(mat3[1],0.f),
		r3(mat3[2],0.f),
		r4(0.f,0.f,0.f,1.f)
	{}
	Matrix4::Matrix4(
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
	Matrix4::Matrix4(
		const float& c1r1,const float& c1r2,const float& c1r3,const float& c1r4,
		const float& c2r1,const float& c2r2,const float& c2r3,const float& c2r4,
		const float& c3r1,const float& c3r2,const float& c3r3,const float& c3r4,
		const float& c4r1,const float& c4r2,const float& c4r3,const float& c4r4)
		:
		r1(c1r1,c1r2,c1r3,c1r4),
		r2(c2r1,c2r2,c2r3,c2r4),
		r3(c3r1,c3r2,c3r3,c3r4),
		r4(c4r1,c4r2,c4r3,c4r4)
	{}
	Matrix4::~Matrix4()
	{}
	
	float* Matrix4::FirstElement() const
	{
		return (float*)&r1.x;
	}
	
	const vector4& Matrix4::operator [](const unsigned int& index) const
	{
		return (&r1)[index];
	}
	vector4& Matrix4::operator [](const unsigned int& index)
	{
		return (&r1)[index];
	}
	
	Matrix4 operator *(const Matrix4& RM, const Matrix4& LM)
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


		return Matrix4(
			L[0][0] * R[0][0] + L[1][0] * R[0][1] + L[2][0] * R[0][2] + L[3][0] * R[0][3],
			L[0][1] * R[0][0] + L[1][1] * R[0][1] + L[2][1] * R[0][2] + L[3][1] * R[0][3],
			L[0][2] * R[0][0] + L[1][2] * R[0][1] + L[2][2] * R[0][2] + L[3][2] * R[0][3],
			L[0][3] * R[0][0] + L[1][3] * R[0][1] + L[2][3] * R[0][2] + L[3][3] * R[0][3],
			L[0][0] * R[1][0] + L[1][0] * R[1][1] + L[2][0] * R[1][2] + L[3][0] * R[1][3],
			L[0][1] * R[1][0] + L[1][1] * R[1][1] + L[2][1] * R[1][2] + L[3][1] * R[1][3],
			L[0][2] * R[1][0] + L[1][2] * R[1][1] + L[2][2] * R[1][2] + L[3][2] * R[1][3],
			L[0][3] * R[1][0] + L[1][3] * R[1][1] + L[2][3] * R[1][2] + L[3][3] * R[1][3],
			L[0][0] * R[2][0] + L[1][0] * R[2][1] + L[2][0] * R[2][2] + L[3][0] * R[2][3],
			L[0][1] * R[2][0] + L[1][1] * R[2][1] + L[2][1] * R[2][2] + L[3][1] * R[2][3],
			L[0][2] * R[2][0] + L[1][2] * R[2][1] + L[2][2] * R[2][2] + L[3][2] * R[2][3],
			L[0][3] * R[2][0] + L[1][3] * R[2][1] + L[2][3] * R[2][2] + L[3][3] * R[2][3],
			L[0][0] * R[3][0] + L[1][0] * R[3][1] + L[2][0] * R[3][2] + L[3][0] * R[3][3],
			L[0][1] * R[3][0] + L[1][1] * R[3][1] + L[2][1] * R[3][2] + L[3][1] * R[3][3],
			L[0][2] * R[3][0] + L[1][2] * R[3][1] + L[2][2] * R[3][2] + L[3][2] * R[3][3],
			L[0][3] * R[3][0] + L[1][3] * R[3][1] + L[2][3] * R[3][2] + L[3][3] * R[3][3]
			);
	}
	const Matrix4 operator *=(Matrix4& LeftVal, const Matrix4& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}

	
	vector4 operator *(const vector4& R, const Matrix4& L)
	{
		return vector4(
			L[0][0] * R[0] + L[0][1] * R[1] + L[0][2] * R[2] + L[0][3] * R[3],
			L[1][0] * R[0] + L[1][1] * R[1] + L[1][2] * R[2] + L[1][3] * R[3],
			L[2][0] * R[0] + L[2][1] * R[1] + L[2][2] * R[2] + L[2][3] * R[3],
			L[3][0] * R[0] + L[3][1] * R[1] + L[3][2] * R[2] + L[3][3] * R[3]
			);
	}
	const vector4 operator *=(vector4& LeftVal, const Matrix4& RightVal)
	{
		LeftVal = LeftVal * RightVal;
		return LeftVal;
	}

}