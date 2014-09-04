#pragma once
#ifndef UTIL_PMATH_H
#define UTIL_PMATH_H

namespace pmath
{
    // Test the equality of 2 variables
    // Mostly needed for floating point values

#if _MSC_VER > 1600
    template<typename T>
    bool equals(const T a, const T b, const T tolerance = T(0.001));
#elif _MSC_VER <= 1600
    // Tolerance has a default value of 0.001,
    // but it cannot be defined here because of a bug in VS2010
    template<typename T>
    bool equals(const T a, const T b, const T tolerance);
#endif

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


    template<typename T>
    T max(const T& a, const T& b);

    template<typename T>
    T min(const T& a, const T& b);

    template<typename T>
    T clamp(const T& value, const T& min, const T& max);
}

#include "inl/Util.inl"
#endif
