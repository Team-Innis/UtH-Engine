#pragma once
#ifndef VECTOR3_H_UMATH
#define VECTOR3_H_UMATH

namespace umath
{
	class vector3
	{
	public:
		vector3();
		vector3(double X, double Y, double Z);
		~vector3();

		double getLenght();
		
		union
		{
			struct
			{
				double x,y,z;
			};
			struct
			{
				double r,g,b;
			};
		};
			
		const double& operator [](const unsigned int& index) const;
		double& operator [](const unsigned int& index);
	private:

	};

	vector3 operator -(const vector3& RightVal);

	vector3 operator +(const vector3& LeftVal,const vector3& RightVal);
	vector3 operator -(const vector3& LeftVal,const vector3& RightVal);

	const vector3& operator +=(vector3& LeftVal,const vector3& RightVal);
	const vector3& operator -=(vector3& LeftVal,const vector3& RightVal);

	vector3 operator /(const vector3& LeftVal,const double& RightVal);
	const vector3& operator /=(vector3& LeftVal,const double& RightVal);

	bool operator ==(const vector3& LeftVal,const vector3& RightVal);
	bool operator !=(const vector3& LeftVal,const vector3& RightVal);

	vector3 operator *(const vector3& LeftVal, const double& RightVal);
	vector3 operator *(const double& LeftVal, const vector3& RightVal);

	const vector3& operator *=(vector3& LeftVal, const double& RightVal);
}
#endif