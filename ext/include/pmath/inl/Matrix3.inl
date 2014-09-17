#include "../Matrix3.hpp"
#include "../Trigonometry.hpp"

#include <cassert>

namespace pmath
{
    template<typename T>
    const Matrix3<T> Matrix3<T>::identity = Matrix3<T>();

    template<typename T>
    inline Matrix3<T>::Matrix3()
        : r1(T(1), T(0), T(0)),
          r2(T(0), T(1), T(0)),
          r3(T(0), T(0), T(1))
    { }

    template<typename T>
    inline Matrix3<T>::Matrix3(const T& a11, const T& a12, const T& a13,
                               const T& a21, const T& a22, const T& a23,
                               const T& a31, const T& a32, const T& a33)
        : r1(a11, a12, a13),
          r2(a21, a22, a23),
          r3(a31, a32, a33)
    { }

    template<typename T>
    inline Matrix3<T>::Matrix3(const Vector3<T>& row1, const Vector3<T>& row2, const Vector3<T>& row3)
        : r1(row1),
          r2(row2),
          r3(row3)
    { }

    template<typename T>
    inline Matrix3<T>::Matrix3(const Matrix2<T>& matrix)
    {
        *this = identity;

        for (unsigned int i = 0; i < Matrix2<T>::ROWS; ++i)
        {
            for (unsigned int j = 0; j < Matrix2<T>::COLUMNS; ++j)
            {
                (*this)[i][j] = matrix[i][j];
            }
        }
    }

    template<typename T>
    inline Matrix3<T>::Matrix3(const Matrix3<T>& matrix)
        : r1(matrix.r1),
          r2(matrix.r2),
          r3(matrix.r3)
    { }

    template<typename T>
    template<typename T2>
    inline Matrix3<T>::Matrix3(const Matrix3<T2>& matrix)
        : r1(matrix[0]),
          r2(matrix[1]),
          r3(matrix[2])
    { }

    template<typename T>
    inline Matrix3<T>::~Matrix3()
    { }


    // Public

    template<typename T>
    inline bool Matrix3<T>::isIdentity() const
    {
        return (*this) == identity;
    }

    template<typename T>
    inline T Matrix3<T>::determinant() const
    {
        return (*this)[0][0] * (*this)[1][1] * (*this)[2][2] - 
            (*this)[0][0] * (*this)[1][2] * (*this)[2][1] -
            (*this)[0][1] * (*this)[1][0] * (*this)[2][2] +
            (*this)[0][1] * (*this)[1][2] * (*this)[2][0] +
            (*this)[0][2] * (*this)[1][0] * (*this)[2][1] -
            (*this)[0][2] * (*this)[1][1] * (*this)[2][0];

    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::transpose() const
    {
        return Matrix3<T>
            (
                (*this)[0][0], (*this)[1][0], (*this)[2][0],
                (*this)[0][1], (*this)[1][1], (*this)[2][1],
                (*this)[0][2], (*this)[1][2], (*this)[2][2]
            );
    }

    template<typename T>
    inline Matrix3<T> transpose(const Matrix3<T>& matrix)
    {
        return matrix.transpose();
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::cofactor() const
    {
        return Matrix3<T>
            (
                (*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1],
                (*this)[1][2] * (*this)[2][0] - (*this)[1][0] * (*this)[2][2],
                (*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0],

                (*this)[0][2] * (*this)[2][1] - (*this)[0][1] * (*this)[2][2],
                (*this)[0][0] * (*this)[2][2] - (*this)[0][2] * (*this)[2][0],
                (*this)[0][1] * (*this)[2][0] - (*this)[0][0] * (*this)[2][1],

                (*this)[0][1] * (*this)[1][2] - (*this)[0][2] * (*this)[1][1],
                (*this)[0][2] * (*this)[1][0] - (*this)[0][0] * (*this)[1][2],
                (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]
            );
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::cofactor(const Matrix3<T>& matrix)
    {
        return matrix.cofactor();
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::inverse() const
    {
        assert(determinant() != 0);
        return (1 / determinant()) * cofactor().transpose();
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::inverse(const Matrix3<T>& matrix)
    {
        return matrix.inverse();
    }

    template<typename T>
    inline Matrix2<T> Matrix3<T>::getMatrix2(const unsigned int rowToRemove, const unsigned int columnToRemove) const
    {
        Matrix2<T> out;
        for (unsigned int row = 0; row < ROWS; ++row)
        {
            if (row != rowToRemove)
            {
                for (unsigned int col = 0; col < COLUMNS; ++col)
                {
                    if (col != columnToRemove)
                        out[row - (row > rowToRemove)][col - (col > columnToRemove)] = (*this)[row][col];
                }
            }
        }

        return out;
    }

    template<typename T>
    inline const T* Matrix3<T>::ptr() const
    {
        return &(*this)[0][0];
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createRotationX(const T& angle)
    {
        return Matrix3<T>(1, 0,             0,
                          0, cos<T>(angle), -sin<T>(angle),
                          0, sin<T>(angle), cos<T>(angle));
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createRotationY(const T& angle)
    {
        return Matrix3<T>(cos<T>(angle),  0, sin<T>(angle),
                          0,              1, 0,
                          -sin<T>(angle), 0, cos<T>(angle));
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createRotationZ(const T& angle)
    {
        return Matrix3<T>(cos<T>(angle), -sin<T>(angle), 0,
                          sin<T>(angle), cos<T>(angle),  0,
                          0,             0,              1);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createScaling(const T& x, const T& y, const T& z)
    {
        return Matrix3<T>(x, 0, 0,
                          0, y, 0,
                          0, 0, z);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createScaling(const Vector3<T>& scale)
    {
        return createScaling(scale.x, scale.y, scale.z);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createScaling(const T& x, const T& y)
    {
        return createScaling(x, y, 1);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createScaling(const Vector2<T>& scale)
    {
        return createScaling(scale.x, scale.y);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createTranslation(const T& x, const T& y)
    {
        return Matrix3<T>(1, 0, x,
                          0, 1, y,
                          0, 0, 1);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::createTranslation(const Vector2<T>& translation)
    {
        return createTranslation(translation.x, translation.y);
    }


    // Operators
    #pragma region Operators
    // Comparison
    template<typename T>
    inline bool Matrix3<T>::operator ==(const Matrix3<T>& right) const
    {
        return r1 == right.r1 && r2 == right.r2 && r3 == right.r3;
    }

    template<typename T>
    inline bool Matrix3<T>::operator !=(const Matrix3<T>& right) const
    {
        return !(*this == right);
    }


    // Assingment
    template<typename T>
    inline Matrix3<T>& Matrix3<T>::operator =(const Matrix3<T>& right)
    {
        r1 = right.r1;
        r2 = right.r2;
        r3 = right.r3;

        return *this;
    }

    template<typename T>
    inline Matrix3<T>& Matrix3<T>::operator +=(const Matrix3<T>& right)
    {
        r1 += right.r1;
        r2 += right.r2;
        r3 += right.r3;

        return *this;
    }

    template<typename T>
    inline Matrix3<T>& Matrix3<T>::operator -=(const Matrix3<T>& right)
    {
        r1 -= right.r1;
        r2 -= right.r2;
        r3 -= right.r3;

        return *this;
    }

    template<typename T>
    inline Matrix3<T>& Matrix3<T>::operator *=(const T& right)
    {
        r1 *= right;
        r2 *= right;
        r3 *= right;

        return *this;
    }

    template<typename T>
    inline Matrix3<T>& Matrix3<T>::operator *=(const Matrix3& right)
    {
        *this = *this * right;

        return *this;
    }

    template<typename T>
    inline Matrix3<T>& Matrix3<T>::operator /=(const T& right)
    {
        r1 /= right;
        r2 /= right;
        r3 /= right;

        return *this;
    }


    // Arithmetic
    template<typename T>
    inline Matrix3<T> Matrix3<T>::operator +(const Matrix3<T>& right) const
    {
        return Matrix3<T>(r1 + right.r1, r2 + right.r2, r3 + right.r3);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::operator -(const Matrix3<T>& right) const
    {
        return Matrix3<T>(r1 - right.r1, r2 - right.r2, r3 - right.r3);
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::operator *(const Matrix3<T>& right) const
    {
        const T L[ROWS][COLUMNS] =
        {
            {
                (*this)[0][0],
                (*this)[0][1],
                (*this)[0][2]
            },
            {
                (*this)[1][0],
                (*this)[1][1],
                (*this)[1][2]
            },
            {
                (*this)[2][0],
                (*this)[2][1],
                (*this)[2][2]
            }
        };

        const T R[ROWS][COLUMNS] =
        {
            {
                right[0][0],
                right[0][1],
                right[0][2]
            },
            {
                right[1][0],
                right[1][1],
                right[1][2]
            },
            {
                right[2][0],
                right[2][1],
                right[2][2]
            }
        };

        return Matrix3<T>
            (
                L[0][0] * R[0][0] + L[0][1] * R[1][0] + L[0][2] * R[2][0],
                L[0][0] * R[0][1] + L[0][1] * R[1][1] + L[0][2] * R[2][1],
                L[0][0] * R[0][2] + L[0][1] * R[1][2] + L[0][2] * R[2][2],

                L[1][0] * R[0][0] + L[1][1] * R[1][0] + L[1][2] * R[2][0],
                L[1][0] * R[0][1] + L[1][1] * R[1][1] + L[1][2] * R[2][1],
                L[1][0] * R[0][2] + L[1][1] * R[1][2] + L[1][2] * R[2][2],

                L[2][0] * R[0][0] + L[2][1] * R[1][0] + L[2][2] * R[2][0],
                L[2][0] * R[0][1] + L[2][1] * R[1][1] + L[2][2] * R[2][1],
                L[2][0] * R[0][2] + L[2][1] * R[1][2] + L[2][2] * R[2][2]
            );
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::operator *(const T& right) const
    {
        return Matrix3<T>(r1 * right, r2 * right, r3 * right);
    }

    template<typename T>
    inline Vector2<T> Matrix3<T>::operator *(const Vector2<T>& right) const
    {
        const Vector3<T> result = (*this) * Vector3<T>(right.x, right.y, 1);

        return Vector2<T>(result.x, result.y);
    }

    template<typename T>
    inline Vector3<T> Matrix3<T>::operator *(const Vector3<T>& right) const
    {
        return Vector3<T>
            (
                (*this)[0][0] * right.x + (*this)[0][1] * right.y + (*this)[0][2] * right.z,
                (*this)[1][0] * right.x + (*this)[1][1] * right.y + (*this)[1][2] * right.z,
                (*this)[2][0] * right.x + (*this)[2][1] * right.y + (*this)[2][2] * right.z
            );
    }

    template<typename T>
    inline Matrix3<T> Matrix3<T>::operator /(const T& right) const
    {
        return Matrix3<T>(r1 / right, r2 / right, r3 / right);
    }


    // Member access
    template<typename T>
    inline Vector3<T>& Matrix3<T>::operator [](const unsigned int index)
    {
        assert(index < ROWS);
        return (&r1)[index];
    }

    template<typename T>
    inline const Vector3<T>& Matrix3<T>::operator [](const unsigned int index) const
    {
        assert(index < ROWS);
        return (&r1)[index];
    }


    // Friends
    template<typename T>
    inline Matrix3<T> operator *(const T& left, const Matrix3<T>& right)
    {
        return right * left;
    }

    template<typename T>
    inline Vector2<T>& operator *=(Vector2<T>& left, const Matrix3<T>& right)
    {
        left = right * left;
        
        return left;
    }

    template<typename T>
    inline Vector3<T>& operator *=(Vector3<T>& left, const Matrix3<T>& right)
    {
        left = right * left;
        
        return left;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& out, const Matrix3<T>& right)
    {
        for (size_t i = 0; i < Matrix3<T>::ROWS; ++i)
        {
            out << "|";
            for (size_t j = 0; j < Matrix3<T>::COLUMNS; ++j)
            {
                out << right[i][j];
                if (j < Matrix3<T>::COLUMNS - 1)
                    out << ", ";
            }
            out << "|" << std::endl;
        }

        return out;
    }
    #pragma endregion
}