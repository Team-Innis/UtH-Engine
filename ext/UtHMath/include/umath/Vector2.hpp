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
			float getAngle() const;

			/*
			Transforms the current vector by given position vector.
			*/
			void transform(const vector2 position);
			/*
			Rotates the current vector by given amount of degrees.
			*/
			void rotateDegrees(const float degrees);
			/*
			Rotates the current vector by given amount of radians.
			*/
			void rotate(const float radians);
			/*
			Scales the current vector by given scale vector.
			*/
			void scale(const vector2 scale);

			float x,y;


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