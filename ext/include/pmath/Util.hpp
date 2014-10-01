#pragma once
#ifndef UTIL_PMATH_H
#define UTIL_PMATH_H

namespace pmath
{
    // Test the equality of 2 variables
    // Mostly needed for floating point values
#if _MSC_VER > 1600 || !defined(_MSC_VER)
    template<typename T>
    bool equals(const T a, const T b, const T tolerance = T(0.001));
#elif _MSC_VER <= 1600
    // Tolerance has a default value of 0.001,
    // but it cannot be defined here because of a bug in VS2010
    template<typename T>
    bool equals(const T a, const T b, const T tolerance);
#endif

    template<typename T>
    T abs(const T& value);

    template<typename T>
    T max(const T& a, const T& b);

    template<typename T>
    T min(const T& a, const T& b);

    template<typename T>
    T clamp(const T& value, const T& min, const T& max);

    double lerp(const double a, const double b, const double t);
}

#include "inl/Util.inl"
#endif
