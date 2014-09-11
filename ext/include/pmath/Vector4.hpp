#pragma once
#ifndef VECTOR4_PMATH_H
#define VECTOR4_PMATH_H

#include "Vector2.hpp"
#include "Vector3.hpp"

#include <iostream>

namespace pmath
{
    template<typename T>
    class Vector4
    {
    public:
        Vector4();
        Vector4(const T& x, const T& y, const T& z, const T& w);
        explicit Vector4(const T& value);
        Vector4(const Vector2<T>& vector, const T& z, const T& w);
        Vector4(const Vector3<T>& vector, const T& w);
        Vector4(const Vector4& vector);
        template<typename T2>
        Vector4(const Vector4<T2>& vector);
        ~Vector4();

        // Scales(multiplies) respective component with scaleVector component
        Vector4& scale(const Vector4& scaleVector);
        // Scales(multiplies) respective component with given component
        Vector4& scale(const T& x, const T& y, const T& z, const T& w);
        // Scales the whole vector with the number
        Vector4& scale(const T& scale);


        T dot(const Vector4& other) const;
        static T dot(const Vector4& vec1, const Vector4& vec2);

        double lengthSquared() const;
        double length() const;

        static double distance(const Vector4& vec1, const Vector4& vec2);

        // Normalizes the vector and returns the normalized vector
        Vector4& normalize();
        // Only returns the normalized vector. Doesn't modify the original
        Vector4 unitVector() const;
        bool isUnitVector() const;

        static Vector4 lerp(const Vector4& vec1, const Vector4& vec2, const T& t);

        #pragma region Operators
        // Comparison
        bool operator ==(const Vector4& right) const;
        bool operator !=(const Vector4& right) const;
        bool operator  >(const Vector4& right) const;
        bool operator  <(const Vector4& right) const;
        bool operator >=(const Vector4& right) const;
        bool operator <=(const Vector4& right) const;

        // Assignment
        Vector4& operator  =(const Vector4& right);
        Vector4& operator +=(const Vector4& right);
        Vector4& operator -=(const Vector4& right);
        Vector4& operator *=(const T& right);
        Vector4& operator /=(const T& right);

        // Arithmetic
        Vector4 operator +(const Vector4& right) const;
        Vector4 operator -() const;
        Vector4 operator -(const Vector4& right) const;
        Vector4 operator *(const T& right) const;
        Vector4 operator /(const T& right) const;

        // Member access
        T& operator [](const unsigned int index);
        const T& operator [](const unsigned int index) const;
        #pragma endregion

        union{ T x, r; };
        union{ T y, g; };
        union{ T z, b; };
        union{ T w, a; };

        static const unsigned int COMPONENTS = 4;
    };

    template<typename T>
    Vector4<T> operator*(const T& left, const Vector4<T>& right);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vector4<T>& right);

    typedef Vector4<float>          Vec4;
    typedef Vector4<float>          Vec4f;
    typedef Vector4<double>         Vec4d;
    typedef Vector4<int>            Vec4i;
    typedef Vector4<unsigned int>   Vec4u;
}

#include "inl/Vector4.inl"
#endif