#pragma once
#ifndef VECTOR3_PMATH_H
#define VECTOR3_PMATH_H

#include "Vector2.hpp"

#include <iostream>

namespace pmath
{
    template<typename T>
    class Vector3
    {
    public:
        Vector3();
        Vector3(const T& x, const T& y, const T& z);
        explicit Vector3(const T& value);
        Vector3(const Vector2<T>& vector, const T& z);
        Vector3(const Vector3& vector);
        template<typename T2>
        Vector3(const Vector3<T2>& vector);
        ~Vector3();

        // Scales(multiplies) respective component with scaleVector component
        Vector3& scale(const Vector3& scaleVector);
        // Scales(multiplies) respective component with given component
        Vector3& scale(const T& x, const T& y, const T& z);
        // Scales the whole vector with the number
        Vector3& scale(const T& scale);

        T dot(const Vector3& other) const;
        static T dot(const Vector3& vec1, const Vector3& vec2);

        Vector3 cross(const Vector3& other) const;
        static Vector3 cross(const Vector3& vec1, const Vector3& vec2);

        double lengthSquared() const;
        double length() const;

        static double distance(const Vector3& vec1, const Vector3& vec2);

        // Normalizes the vector and returns the normalized vector
        Vector3& normalize();
        // Only returns the normalized vector. Doesn't modify the original
        Vector3 unitVector() const;
        bool isUnitVector() const;

        static Vector3 lerp(const Vector3& vec1, const Vector3& vec2, const T& t);

        #pragma region Operators
        // Comparison
        bool operator ==(const Vector3& right) const;
        bool operator !=(const Vector3& right) const;
        bool operator  >(const Vector3& right) const;
        bool operator  <(const Vector3& right) const;
        bool operator >=(const Vector3& right) const;
        bool operator <=(const Vector3& right) const;

        // Assignment
        Vector3& operator  =(const Vector3& right);
        Vector3& operator +=(const Vector3& right);
        Vector3& operator -=(const Vector3& right);
        Vector3& operator *=(const T& right);
        Vector3& operator /=(const T& right);

        // Arithmetic
        Vector3 operator +(const Vector3& right) const;
        Vector3 operator -() const;
        Vector3 operator -(const Vector3& right) const;
        Vector3 operator *(const T& right) const;
        Vector3 operator /(const T& right) const;

        // Member access
        T& operator [](const unsigned int index);
        const T& operator [](const unsigned int index) const;
        #pragma endregion

        union{ T x, r; };
        union{ T y, g; };
        union{ T z, b; };

        static const unsigned int COMPONENTS = 3;
    };

    template<typename T>
    Vector3<T> operator*(const T& left, const Vector3<T>& right);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vector3<T>& right);

    typedef Vector3<float>          Vec3;
    typedef Vector3<float>          Vec3f;
    typedef Vector3<double>         Vec3d;
    typedef Vector3<int>            Vec3i;
    typedef Vector3<unsigned int>   Vec3u;
}

#include "inl/Vector3.inl"
#endif