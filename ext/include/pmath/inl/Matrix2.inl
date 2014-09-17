#include "../Matrix2.hpp"
#include "../Trigonometry.hpp"

#include <cassert>

namespace pmath
{
    template<typename T>
    const Matrix2<T> Matrix2<T>::identity = Matrix2<T>();

    template<typename T>
    inline Matrix2<T>::Matrix2()
        : r1(T(1), T(0)),
          r2(T(0), T(1))
    { }

    template<typename T>
    inline Matrix2<T>::Matrix2(const T& a11, const T& a12,
                               const T& a21, const T& a22)
        : r1(a11, a12),
          r2(a21, a22)
    { }

    template<typename T>
    inline Matrix2<T>::Matrix2(const Vector2<T>& row1, const Vector2<T>& row2)
        : r1(row1),
          r2(row2)
    { }

    template<typename T>
    inline Matrix2<T>::Matrix2(const Matrix2<T>& matrix)
        : r1(matrix.r1),
          r2(matrix.r2)
    { }

    template<typename T>
    template<typename T2>
    inline Matrix2<T>::Matrix2(const Matrix2<T2>& matrix)
        : r1(matrix[0]),
          r2(matrix[1])
    { }

    template<typename T>
    inline Matrix2<T>::~Matrix2()
    { }


    // Public

    template<typename T>
    inline bool Matrix2<T>::isIdentity() const
    {
        return (*this) == identity;
    }

    template<typename T>
    inline T Matrix2<T>::determinant() const
    {
        return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::transpose() const
    {
        return Matrix2<T>((*this)[0][0], (*this)[1][0], (*this)[0][1], (*this)[1][1]);
    }

    template<typename T>
    inline Matrix2<T> transpose(const Matrix2<T>& matrix)
    {
        return matrix.transpose();
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::cofactor() const
    {
        return Matrix2<T>((*this)[1][1], -(*this)[1][0], -(*this)[0][1], (*this)[0][0]);
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::cofactor(const Matrix2<T>& matrix)
    {
        return matrix.cofactor();
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::inverse() const
    {
        assert(determinant() != 0);
        return (1 / determinant()) * cofactor().transpose();
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::inverse(const Matrix2<T>& matrix)
    {
        return matrix.inverse();
    }

    template<typename T>
    inline const T* Matrix2<T>::ptr() const
    {
        return &(*this)[0][0];
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::createRotation(const T& angle)
    {
        return Matrix2<T>(cos<T>(angle), -sin<T>(angle),
                          sin<T>(angle), cos<T>(angle));
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::createScaling(const T& x, const T& y)
    {
        return Matrix2<T>(x, 0,
                          0, y);
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::createScaling(const Vector2<T>& scale)
    {
        return createScaling(scale.x, scale.y);
    }


    // Operators
    #pragma region Operators
    // Comparison
    template<typename T>
    inline bool Matrix2<T>::operator ==(const Matrix2<T>& right) const
    {
        return r1 == right.r1 && r2 == right.r2;
    }

    template<typename T>
    inline bool Matrix2<T>::operator !=(const Matrix2<T>& right) const
    {
        return !(*this == right);
    }


    // Assingment
    template<typename T>
    inline Matrix2<T>& Matrix2<T>::operator =(const Matrix2<T>& right)
    {
        r1 = right.r1;
        r2 = right.r2;

        return *this;
    }

    template<typename T>
    inline Matrix2<T>& Matrix2<T>::operator +=(const Matrix2<T>& right)
    {
        r1 += right.r1;
        r2 += right.r2;

        return *this;
    }

    template<typename T>
    inline Matrix2<T>& Matrix2<T>::operator -=(const Matrix2<T>& right)
    {
        r1 -= right.r1;
        r2 -= right.r2;

        return *this;
    }

    template<typename T>
    inline Matrix2<T>& Matrix2<T>::operator *=(const T& right)
    {
        r1 *= right;
        r2 *= right;

        return *this;
    }

    template<typename T>
    inline Matrix2<T>& Matrix2<T>::operator *=(const Matrix2& right)
    {
        *this = *this * right;

        return *this;
    }

    template<typename T>
    inline Matrix2<T>& Matrix2<T>::operator /=(const T& right)
    {
        r1 /= right;
        r2 /= right;

        return *this;
    }


    // Arithmetic
    template<typename T>
    inline Matrix2<T> Matrix2<T>::operator +(const Matrix2<T>& right) const
    {
        return Matrix2<T>(r1 + right.r1, r2 + right.r2);
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::operator -(const Matrix2<T>& right) const
    {
        return Matrix2<T>(r1 - right.r1, r2 - right.r2);
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::operator *(const Matrix2<T>& right) const
    {
        const T L[ROWS][COLUMNS] =
        {
            {
                (*this)[0][0],
                (*this)[0][1]
            },
            {
                (*this)[1][0],
                (*this)[1][1]
            }
        };

        const T R[ROWS][COLUMNS] =
        {
            {
                right[0][0],
                right[0][1]
            },
            {
                right[1][0],
                right[1][1]
            }
        };

        return Matrix2<T>
            (
                L[0][0] * R[0][0] + L[0][1] * R[1][0],
                L[0][0] * R[0][1] + L[0][1] * R[1][1],

                L[1][0] * R[0][0] + L[1][1] * R[1][0],
                L[1][0] * R[0][1] + L[1][1] * R[1][1]
            );
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::operator *(const T& right) const
    {
        return Matrix2<T>(r1 * right, r2 * right);
    }

    template<typename T>
    inline Vector2<T> Matrix2<T>::operator *(const Vector2<T>& right) const
    {
        return Vector2<T>
            (
                (*this)[0][0] * right.x + (*this)[0][1] * right.y,
                (*this)[1][0] * right.x + (*this)[1][1] * right.y
            );
    }

    template<typename T>
    inline Matrix2<T> Matrix2<T>::operator /(const T& right) const
    {
        return Matrix2<T>(r1 / right, r2 / right);
    }


    // Member access
    template<typename T>
    inline Vector2<T>& Matrix2<T>::operator [](const unsigned int index)
    {
        assert(index < ROWS);
        return (&r1)[index];
    }

    template<typename T>
    inline const Vector2<T>& Matrix2<T>::operator [](const unsigned int index) const
    {
        assert(index < ROWS);
        return (&r1)[index];
    }


    // Friends
    template<typename T>
    inline Matrix2<T> operator *(const T& left, const Matrix2<T>& right)
    {
        return right * left;
    }

    template<typename T>
    inline Vector2<T>& operator *=(Vector2<T>& left, const Matrix2<T>& right)
    {
        left = right * left;

        return left;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& out, const Matrix2<T>& right)
    {
        for (size_t i = 0; i < Matrix2<T>::ROWS; ++i)
        {
            out << "|";
            for (size_t j = 0; j < Matrix2<T>::COLUMNS; ++j)
            {
                out << right[i][j];
                if (j < Matrix2<T>::COLUMNS - 1)
                    out << ", ";
            }
            out << "|" << std::endl;
        }

        return out;
    }
    #pragma endregion
}