#ifndef TRIGONOMETRY_PMATH_H
#define TRIGONOMETRY_PMATH_H

namespace pmath
{
	template<typename T>
	T degreesToRadians(const T& degrees);
	
	template<typename T>
	T radiansToDegrees(const T& radians);
	
	// Angle in degrees
	template<typename T>
	T cos(const T& angle);
	// Return value in degrees
	template<typename T>
	T acos(const T& value);
	
	// Angle in degrees
	template<typename T>
	T sin(const T& angle);
	// Return value in degrees
	template<typename T>
	T asin(const T& value);
	
	// Angle in degrees
	template<typename T>
	T tan(const T& angle);
	// Return value in degrees
	template<typename T>
	T atan(const T& value);
}

#include "inl/Trigonometry.inl"
#endif