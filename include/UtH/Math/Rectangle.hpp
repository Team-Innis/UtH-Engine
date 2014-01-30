#pragma once
#ifndef RECTANGLE_H_UMATH
#define RECTANGLE_H_UMATH

#include <UtH\Math\Vector2.hpp>

namespace umath
{
	class rectangle
	{
	public:

		rectangle();
		rectangle(float Left, float Top, float Width, float Height);
		rectangle(vector2 Position, float Width, float Height);
		rectangle(vector2 Position, vector2 Size);
		~rectangle();

		vector2 position, size;


	private:
		void Resize(vector2 Size);
		

		bool Intersects(rectangle rectangle);
		bool Contains(vector2 Position);

	};
}
#endif