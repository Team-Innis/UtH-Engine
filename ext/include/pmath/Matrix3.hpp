#pragma once
#ifndef MATRIX3_PMATH_H
#define MATRIX3_PMATH_H

#include "Vector2.hpp"
#include "Vector3.hpp"

#include "Matrix2.hpp"

#include <iostream>

namespace pmath
{
    template<typename T>
    class Matrix3
    {
    public:
        Matrix3();
        Matrix3(const T& a11, const T& a12, const T& a13,
                const T& a21, const T& a22, const T& a23,
                const T& a31, const T& a32, const T& a33);
        Matrix3(const Vector3<T>& row1, const Vector3<T>& row2, const Vector3<T>& row3);
        explicit Matrix3(const Matrix2<T>& matrix);
        Matrix3(const Matrix3& matrix);
        template<typename T2>
        Matrix3(const Matrix3<T2>& matrix);
        ~Matrix3();

        static const Matrix3 identity;
        bool isIdentity() const;

        T determinant() const;

        Matrix3 transpose() const;
        static Matrix3 transpose(const Matrix3& matrix);

        Matrix3 cofactor() const;
        static Matrix3 cofactor(const Matrix3& matrix);

        Matrix3 inverse() const;
        static Matrix3 inverse(const Matrix3& matrix);

        Matrix2<T> getMatrix2(const unsigned int rowToRemove = 2, const unsigned int columnToRemove = 2) const;

        const T* ptr() const;

        static Matrix3 createRotationX(const T& angle);
        static Matrix3 createRotationY(const T& angle);
        // May also be used as homogeneous rotation for a 2 dimensional vector
        static Matrix3 createRotationZ(const T& angle);

        // Create scaling for a 3 dimensional vector
        static Matrix3 createScaling(const T& x, const T& y, const T& z);
        static Matrix3 createScaling(const Vector3<T>& scale);
        // Create homogeneous scaling for a 2 dimensional vector
        static Matrix3 createScaling(const T& x, const T& y);
        static Matrix3 createScaling(const Vector2<T>& scale);

        static Matrix3 createTranslation(const T& x, const T& y);
        static Matrix3 createTranslation(const Vector2<T>& translation);


        #pragma region Operators
        // Comparison
        bool operator ==(const Matrix3& right) const;
        bool operator !=(const Matrix3& right) const;


        // Assingment
        Matrix3& operator  =(const Matrix3& right);
        Matrix3& operator +=(const Matrix3& right);
        Matrix3& operator -=(const Matrix3& right);
        Matrix3& operator *=(const T& right);
        Matrix3& operator *=(const Matrix3& right);
        Matrix3& operator /=(const T& right);


        // Arithmetic
        Matrix3 operator +(const Matrix3& right) const;
        Matrix3 operator -(const Matrix3& right) const;
        Matrix3 operator *(const Matrix3& right) const;
        Matrix3 operator *(const T& right) const;
        Vector2<T> operator *(const Vector2<T>& right) const;
        Vector3<T> operator *(const Vector3<T>& right) const;
        Matrix3 operator /(const T& right) const;


        // Member access
        Vector3<T>& operator [](const unsigned int index);
        const Vector3<T>& operator [](const unsigned int index) const;
        #pragma endregion

        static const unsigned int COLUMNS = 3;
        static const unsigned int ROWS = 3;

    private:
        Vector3<T> r1, r2, r3;
    };

    template<typename T>
    Matrix3<T> operator *(const T& left, const Matrix3<T>& right);

    template<typename T>
    Vector2<T>& operator *=(Vector2<T>& left, const Matrix3<T>& right);

    template<typename T>
    Vector3<T>& operator *=(Vector3<T>& left, const Matrix3<T>& right);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix3<T>& right);

    typedef Matrix3<float>          Mat3;
    typedef Matrix3<double>         Mat3d;
    typedef Matrix3<int>            Mat3i;
    typedef Matrix3<unsigned int>   Mat3u;
}

#include "inl/Matrix3.inl"
#endif