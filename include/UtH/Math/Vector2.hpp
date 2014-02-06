#pragma once
#ifndef VECTOR2_H_UMATH
#define VECTOR2_H_UMATH

namespace umath
{
	class vector2
		{
		public:
			vector2();
			vector2(float X, float Y);
			~vector2();

			float getLenght() const;
			/*
			Returns the angle of the vector in radians ranging from -PI to PI
			*/
			float getRadians() const;
			/*
			Returns the angle of the vector in degrees ranging from -180 to 180
			*/
			float getDegrees() const;

			/*
			Transforms the current vector by given position vector.
			*/
			void Transform(const vector2 Position);
			/*
			Rotates the current vector by given amount of degrees.
			*/
			void RotateDegrees(const float Degrees);
			/*
			Rotates the current vector by given amount of radians.
			*/
			void Rotate(const float Radians);
			/*
			Scales the current vector by given scale vector.
			*/
			void Scale(const vector2 Scale);

			union
			{
				struct
				{
					float x,y;
				};
				struct
				{
					float w,h;
				};
			};

		private:

		};

	vector2 operator -(const vector2& RightVal);

	vector2 operator +(const vector2& LeftVal,const vector2& RightVal);
	vector2 operator -(const vector2& LeftVal,const vector2& RightVal);

	const vector2& operator +=(vector2& LeftVal,const vector2& RightVal);
	const vector2& operator -=(vector2& LeftVal,const vector2& RightVal);

	vector2 operator /(const vector2& LeftVal,const float& RightVal);
	const vector2& operator /=(vector2& LeftVal,const float& RightVal);

	bool operator ==(const vector2& LeftVal,const vector2& RightVal);
	bool operator !=(const vector2& LeftVal,const vector2& RightVal);

	vector2 operator *(const vector2& LeftVal, const float& RightVal);
	vector2 operator *(const float& LeftVal, const vector2& RightVal);

	const vector2& operator *=(vector2& LeftVal, const float& RightVal);
		/*std::ostream& operator <<(std::ostream& Ostr, const vector& RightVal);*/
}
#endif