#pragma once
#ifndef MATRIX4_PMATH_H
#define MATRIX4_PMATH_H

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Matrix2.hpp"
#include "Matrix3.hpp"

#include <iostream>

namespace pmath
{
    template<typename T>
    class Matrix4
    {
    public:
        Matrix4();
        Matrix4(const T& a11, const T& a12, const T& a13, const T& a14,
                const T& a21, const T& a22, const T& a23, const T& a24,
                const T& a31, const T& a32, const T& a33, const T& a34,
                const T& a41, const T& a42, const T& a43, const T& a44);
        Matrix4(const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3, const Vector4<T>& row4);
        explicit Matrix4(const Matrix2<T>& matrix);
        explicit Matrix4(const Matrix3<T>& matrix);
        Matrix4(const Matrix4& matrix);
        template<typename T2>
        Matrix4(const Matrix4<T2>& matrix);
        ~Matrix4();

        static const Matrix4 identity;
        bool isIdentity() const;

        T determinant() const;

        Matrix4 transpose() const;
        static Matrix4 transpose(const Matrix4& matrix);

        Matrix4 cofactor() const;
        static Matrix4 cofactor(const Matrix4& matrix);

        Matrix4 inverse() const;
        static Matrix4 inverse(const Matrix4& matrix);
        
        Matrix3<T> getMatrix3(const unsigned int rowToRemove = 2, const unsigned int columnToRemove = 2) const;

        const T* ptr() const;

        // Create homogeneous rotation for a 3 dimensional or
        // a 4 dimensional homogeneous vector
        static Matrix4 createRotationX(const T& angle);
        static Matrix4 createRotationY(const T& angle);
        static Matrix4 createRotationZ(const T& angle);

        // Create homogeneous scaling for a 3 dimensional or
        // a 4 dimensional homogeneous vector
        static Matrix4 createScaling(const T& x, const T& y, const T& z);
        static Matrix4 createScaling(const Vector3<T>& scale);

        // Create homogeneous translation for a 3 dimensional or
        // a 4 dimensional homogeneous vector
        static Matrix4 createTranslation(const T& x, const T& y, const T& z);
        static Matrix4 createTranslation(const Vector3<T>& translation);


        #pragma region Operators
        // Comparison
        bool operator ==(const Matrix4& right) const;
        bool operator !=(const Matrix4& right) const;


        // Assignment
        Matrix4& operator  =(const Matrix4& right);
        Matrix4& operator +=(const Matrix4& right);
        Matrix4& operator -=(const Matrix4& right);
        Matrix4& operator *=(const T& right);
        Matrix4& operator *=(const Matrix4& right);
        Matrix4& operator /=(const T& right);


        // Arithmetic
        Matrix4 operator +(const Matrix4& right) const;
        Matrix4 operator -(const Matrix4& right) const;
        Matrix4 operator *(const Matrix4& right) const;
        Matrix4 operator *(const T& right) const;
        Vector2<T> operator *(const Vector2<T>& right) const;
        Vector3<T> operator *(const Vector3<T>& right) const;
        Vector4<T> operator *(const Vector4<T>& right) const;
        Matrix4 operator /(const T& right) const;


        // Member access
        Vector4<T>& operator [](const unsigned int index);
        const Vector4<T>& operator [](const unsigned int index) const;
        #pragma endregion

        static const unsigned int COLUMNS = 4;
        static const unsigned int ROWS = 4;

    private:
        Vector4<T> r1, r2, r3, r4;
    };

    template<typename T>
    Matrix4<T> operator *(const T& left, const Matrix4<T>& right);

    template<typename T>
    Vector2<T>& operator *=(Vector2<T>& left, const Matrix4<T>& right);

    template<typename T>
    Vector3<T>& operator *=(Vector3<T>& left, const Matrix4<T>& right);

    template<typename T>
    Vector4<T>& operator *=(Vector4<T>& left, const Matrix4<T>& right);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix4<T>& right);


    typedef Matrix4<float>          Mat4;
    typedef Matrix4<double>         Mat4d;
    typedef Matrix4<int>            Mat4i;
    typedef Matrix4<unsigned int>   Mat4u;
}

#include "inl/Matrix4.inl"
#endif