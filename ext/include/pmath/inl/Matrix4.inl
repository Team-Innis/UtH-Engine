#include "../Matrix4.hpp"
#include "../Trigonometry.hpp"

#include <cassert>
#include <sstream>

namespace pmath
{
    template<typename T>
    const Matrix4<T> Matrix4<T>::identity = Matrix4<T>();

    template<typename T>
    inline Matrix4<T>::Matrix4()
        : r1(T(1), T(0), T(0), T(0)),
          r2(T(0), T(1), T(0), T(0)),
          r3(T(0), T(0), T(1), T(0)),
          r4(T(0), T(0), T(0), T(1))
    { }

    template<typename T>
    inline Matrix4<T>::Matrix4(const T& a11, const T& a12, const T& a13, const T& a14,
                               const T& a21, const T& a22, const T& a23, const T& a24,
                               const T& a31, const T& a32, const T& a33, const T& a34,
                               const T& a41, const T& a42, const T& a43, const T& a44)
        : r1(a11, a12, a13, a14),
          r2(a21, a22, a23, a24),
          r3(a31, a32, a33, a34),
          r4(a41, a42, a43, a44)
    { }

    template<typename T>
    inline Matrix4<T>::Matrix4(const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3, const Vector4<T>& row4)
        : r1(row1),
          r2(row2),
          r3(row3),
          r4(row4)
    { }

    template<typename T>
    inline Matrix4<T>::Matrix4(const Matrix2<T>& matrix)
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
    inline Matrix4<T>::Matrix4(const Matrix3<T>& matrix)
    {
        *this = identity;

        for (unsigned int i = 0; i < Matrix3<T>::ROWS; ++i)
        {
            for (unsigned int j = 0; j < Matrix3<T>::COLUMNS; ++j)
            {
                (*this)[i][j] = matrix[i][j];
            }
        }
    }

    template<typename T>
    inline Matrix4<T>::Matrix4(const Matrix4<T>& matrix)
        : r1(matrix.r1),
          r2(matrix.r2),
          r3(matrix.r3),
          r4(matrix.r4)
    { }

    template<typename T>
    template<typename T2>
    inline Matrix4<T>::Matrix4(const Matrix4<T2>& matrix)
        : r1(matrix[0]),
          r2(matrix[1]),
          r3(matrix[2]),
          r4(matrix[3])
    { }

    template<typename T>
    inline Matrix4<T>::~Matrix4()
    { }


    // Public

    template<typename T>
    inline bool Matrix4<T>::isIdentity() const
    {
        return (*this) == identity;
    }

    template<typename T>
    inline T Matrix4<T>::determinant() const
    {
        const T D[ROWS][COLUMNS] =
        {
            
            {
                (*this)[0][0],
                (*this)[0][1],
                (*this)[0][2],
                (*this)[0][3]
            },
            {
                (*this)[1][0],
                (*this)[1][1],
                (*this)[1][2],
                (*this)[1][3]
            },
            {
                (*this)[2][0],
                (*this)[2][1],
                (*this)[2][2],
                (*this)[2][3]
            },
            {
                (*this)[3][0],
                (*this)[3][1],
                (*this)[3][2],
                (*this)[3][3]
            }
        };

        return D[0][0] * (D[1][1] * (D[2][2] * D[3][3] - D[2][3] * D[3][2]) 
                        + D[1][2] * (D[2][3] * D[3][1] - D[2][1] * D[3][3]) 
                        + D[1][3] * D[2][1] * D[3][2] - D[1][3] * D[2][2] * D[3][1]) 

             + D[0][1] * (D[1][0] * (D[2][3] * D[3][2] - D[2][2] * D[3][3])
                        + D[3][0] * (D[1][3] * D[2][2] - D[1][2] * D[2][3])
                        + D[1][2] * D[2][0] * D[3][3] - D[1][3] * D[2][0] * D[3][2])

             + D[0][2] * (D[1][0] * (D[2][1] * D[3][3] - D[2][3] * D[3][1])
                        + D[3][0] * (D[1][1] * D[2][3] - D[1][3] * D[2][1]) 
                        - D[1][1] * D[2][0] * D[3][3] + D[1][3] * D[2][0] * D[3][1])

             + D[0][3] * (D[1][0] * (D[2][2] * D[3][1] - D[2][1] * D[3][2])
                        + D[1][1] * D[2][0] * D[3][2] - D[1][2] * D[2][0] * D[3][1])

             + D[0][3] * D[3][0] * (D[1][2] * D[2][1] - D[1][1] * D[2][2]);

    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::transpose() const
    {
        return Matrix4<T>
            (
                (*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0],
                (*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1],
                (*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2],
                (*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3]
            );
    }

    template<typename T>
    inline Matrix4<T> transpose(const Matrix4<T>& matrix)
    {
        return matrix.transpose();
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::cofactor() const
    {
        const T C[ROWS][COLUMNS] =
        {
            {
                (*this)[0][0],
                (*this)[0][1],
                (*this)[0][2],
                (*this)[0][3]
            },
            {
                (*this)[1][0],
                (*this)[1][1],
                (*this)[1][2],
                (*this)[1][3]
            },
            {
                (*this)[2][0],
                (*this)[2][1],
                (*this)[2][2],
                (*this)[2][3]
            },
            {
                (*this)[3][0],
                (*this)[3][1],
                (*this)[3][2],
                (*this)[3][3]
            }
        };

        // Yes it actually works. never edit this. ever
        return Matrix4<T>
            (
            C[1][1] * C[2][2] * C[3][3] - C[1][1] * C[2][3] * C[3][2] - C[1][2] * C[2][1] * C[3][3] + C[1][2] * C[2][3] * C[3][1] + C[1][3] * C[2][1] * C[3][2] - C[1][3] * C[2][2] * C[3][1],
            -C[1][0] * C[2][2] * C[3][3] + C[1][0] * C[2][3] * C[3][2] + C[1][2] * C[2][0] * C[3][3] - C[1][2] * C[2][3] * C[3][0] - C[1][3] * C[2][0] * C[3][2] + C[1][3] * C[2][2] * C[3][0],
            C[1][0] * C[2][1] * C[3][3] - C[1][0] * C[2][3] * C[3][1] - C[1][1] * C[2][0] * C[3][3] + C[1][1] * C[2][3] * C[3][0] + C[1][3] * C[2][0] * C[3][1] - C[1][3] * C[2][1] * C[3][0],
            -C[1][0] * C[2][1] * C[3][2] + C[1][0] * C[2][2] * C[3][1] + C[1][1] * C[2][0] * C[3][2] - C[1][1] * C[2][2] * C[3][0] - C[1][2] * C[2][0] * C[3][1] + C[1][2] * C[2][1] * C[3][0],

            -C[0][1] * C[2][2] * C[3][3] + C[0][1] * C[2][3] * C[3][2] + C[0][2] * C[2][1] * C[3][3] - C[0][2] * C[2][3] * C[3][1] - C[0][3] * C[2][1] * C[3][2] + C[0][3] * C[2][2] * C[3][1],
            C[0][0] * C[2][2] * C[3][3] - C[0][0] * C[2][3] * C[3][2] - C[0][2] * C[2][0] * C[3][3] + C[0][2] * C[2][3] * C[3][0] + C[0][3] * C[2][0] * C[3][2] - C[0][3] * C[2][2] * C[3][0],
            -C[0][0] * C[2][1] * C[3][3] + C[0][0] * C[2][3] * C[3][1] + C[0][1] * C[2][0] * C[3][3] - C[0][1] * C[2][3] * C[3][0] - C[0][3] * C[2][0] * C[3][1] + C[0][3] * C[2][1] * C[3][0],
            C[0][0] * C[2][1] * C[3][2] - C[0][0] * C[2][2] * C[3][1] - C[0][1] * C[2][0] * C[3][2] + C[0][1] * C[2][2] * C[3][0] + C[0][2] * C[2][0] * C[3][1] - C[0][2] * C[2][1] * C[3][0],

            C[0][1] * C[1][2] * C[3][3] - C[0][1] * C[1][3] * C[3][2] - C[0][2] * C[1][1] * C[3][3] + C[0][2] * C[1][3] * C[3][1] + C[0][3] * C[1][1] * C[3][2] - C[0][3] * C[1][2] * C[3][1],
            -C[0][0] * C[1][2] * C[3][3] + C[0][0] * C[1][3] * C[3][2] + C[0][2] * C[1][0] * C[3][3] - C[0][2] * C[1][3] * C[3][0] - C[0][3] * C[1][0] * C[3][2] + C[0][3] * C[1][2] * C[3][0],
            C[0][0] * C[1][1] * C[3][3] - C[0][0] * C[1][3] * C[3][1] - C[0][1] * C[1][0] * C[3][3] + C[0][1] * C[1][3] * C[3][0] + C[0][3] * C[1][0] * C[3][1] - C[0][3] * C[1][1] * C[3][0],
            -C[0][0] * C[1][1] * C[3][2] + C[0][0] * C[1][2] * C[3][1] + C[0][1] * C[1][0] * C[3][2] - C[0][1] * C[1][2] * C[3][0] - C[0][2] * C[1][0] * C[3][1] + C[0][2] * C[1][1] * C[3][0],

            -C[0][1] * C[1][2] * C[2][3] + C[0][1] * C[1][3] * C[2][2] + C[0][2] * C[1][1] * C[2][3] - C[0][2] * C[1][3] * C[2][1] - C[0][3] * C[1][1] * C[2][2] + C[0][3] * C[1][2] * C[2][1],
            C[0][0] * C[1][2] * C[2][3] - C[0][0] * C[1][3] * C[2][2] - C[0][2] * C[1][0] * C[2][3] + C[0][2] * C[1][3] * C[2][0] + C[0][3] * C[1][0] * C[2][2] - C[0][3] * C[1][2] * C[2][0],
            -C[0][0] * C[1][1] * C[2][3] + C[0][0] * C[1][3] * C[2][1] + C[0][1] * C[1][0] * C[2][3] - C[0][1] * C[1][3] * C[2][0] - C[0][3] * C[1][0] * C[2][1] + C[0][3] * C[1][1] * C[2][0],
            C[0][0] * C[1][1] * C[2][2] - C[0][0] * C[1][2] * C[2][1] - C[0][1] * C[1][0] * C[2][2] + C[0][1] * C[1][2] * C[2][0] + C[0][2] * C[1][0] * C[2][1] - C[0][2] * C[1][1] * C[2][0]
            );
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::cofactor(const Matrix4<T>& matrix)
    {
        return matrix.cofactor();
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::inverse() const
    {
        assert(determinant() != 0);
        return (1 / determinant()) * cofactor().transpose();
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::inverse(const Matrix4<T>& matrix)
    {
        return matrix.inverse();
    }

    template<typename T>
    inline Matrix3<T> Matrix4<T>::getMatrix3(const unsigned int rowToRemove, const unsigned int columnToRemove) const
    {
        Matrix3<T> out;
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
    inline const T* Matrix4<T>::ptr() const
    {
        return &(*this)[0][0];
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createRotationX(const T& angle)
    {
        return Matrix4<T>(1, 0,             0,              0,
                          0, cos<T>(angle), -sin<T>(angle), 0,
                          0, sin<T>(angle), cos<T>(angle),  0,
                          0, 0,             0,              1);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createRotationY(const T& angle)
    {
        return Matrix4<T>(cos<T>(angle),  0, sin<T>(angle), 0,
                          0,              1, 0,             0,
                          -sin<T>(angle), 0, cos<T>(angle), 0,
                          0,              0, 0,             1);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createRotationZ(const T& angle)
    {
        return Matrix4<T>(cos<T>(angle), -sin<T>(angle), 0, 0,
                          sin<T>(angle), cos<T>(angle),  0, 0,
                          0,             0,              1, 0,
                          0,             0,              0, 1);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createScaling(const T& x, const T& y, const T& z)
    {
        return Matrix4<T>(x, 0, 0, 0,
                          0, y, 0, 0,
                          0, 0, z, 0,
                          0, 0, 0, 1);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createScaling(const Vector3<T>& scale)
    {
        return createScaling(scale.x, scale.y, scale.z);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createTranslation(const T& x, const T& y, const T& z)
    {
        return Matrix4<T>(1, 0, 0, x,
                          0, 1, 0, y,
                          0, 0, 1, z,
                          0, 0, 0, 1);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::createTranslation(const Vector3<T>& translation)
    {
        return createTranslation(translation.x, translation.y, translation.z);
    }



    template<typename T>
    inline std::string pmath::Matrix4<T>::toString() const
    {
        std::ostringstream stream;
        stream << *this;

        return stream.str();
    }

    // Operators
    #pragma region Operators
    // Comparison
    template<typename T>
    inline bool Matrix4<T>::operator ==(const Matrix4<T>& right) const
    {
        return r1 == right.r1 && r2 == right.r2 && r3 == right.r3 && r4 == right.r4;
    }

    template<typename T>
    inline bool Matrix4<T>::operator !=(const Matrix4<T>& right) const
    {
        return !(*this == right);
    }


    // Assignment
    template<typename T>
    inline Matrix4<T>& Matrix4<T>::operator =(const Matrix4<T>& right)
    {
        r1 = right.r1;
        r2 = right.r2;
        r3 = right.r3;
        r4 = right.r4;

        return *this;
    }

    template<typename T>
    inline Matrix4<T>& Matrix4<T>::operator +=(const Matrix4<T>& right)
    {
        r1 += right.r1;
        r2 += right.r2;
        r3 += right.r3;
        r4 += right.r4;

        return *this;
    }

    template<typename T>
    inline Matrix4<T>& Matrix4<T>::operator -=(const Matrix4<T>& right)
    {
        r1 -= right.r1;
        r2 -= right.r2;
        r3 -= right.r3;
        r4 -= right.r4;

        return *this;
    }

    template<typename T>
    inline Matrix4<T>& Matrix4<T>::operator *=(const T& right)
    {
        r1 *= right;
        r2 *= right;
        r3 *= right;
        r4 *= right;

        return *this;
    }

    template<typename T>
    inline Matrix4<T>& Matrix4<T>::operator *=(const Matrix4& right)
    {
        *this = *this * right;

        return *this;
    }

    template<typename T>
    inline Matrix4<T>& Matrix4<T>::operator /=(const T& right)
    {
        r1 /= right;
        r2 /= right;
        r3 /= right;
        r4 /= right;

        return *this;
    }


    // Arithmetic
    template<typename T>
    inline Matrix4<T> Matrix4<T>::operator +(const Matrix4<T>& right) const
    {
        return Matrix4<T>(r1 + right.r1, r2 + right.r2, r3 + right.r3, r4 + right.r4);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::operator -(const Matrix4<T>& right) const
    {
        return Matrix4<T>(r1 - right.r1, r2 - right.r2, r3 - right.r3, r4 - right.r4);
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::operator *(const Matrix4<T>& right) const
    {
        // Using arrays is faster for some reason. works for me
        const T L[ROWS][COLUMNS] =
        {
            {
                (*this)[0][0],
                (*this)[0][1],
                (*this)[0][2],
                (*this)[0][3]
            },
            {
                (*this)[1][0],
                (*this)[1][1],
                (*this)[1][2],
                (*this)[1][3]
            },
            {
                (*this)[2][0],
                (*this)[2][1],
                (*this)[2][2],
                (*this)[2][3]
            },
            {
                (*this)[3][0],
                (*this)[3][1],
                (*this)[3][2],
                (*this)[3][3]
            }
        };

        const T R[ROWS][COLUMNS] =
        {
            {
                right[0][0],
                right[0][1],
                right[0][2],
                right[0][3]
            },
            {
                right[1][0],
                right[1][1],
                right[1][2],
                right[1][3]
            },
            {
                right[2][0],
                right[2][1],
                right[2][2],
                right[2][3]
            },
            {
                right[3][0],
                right[3][1],
                right[3][2],
                right[3][3]
            }
        };

        return Matrix4<T>
            (
                L[0][0] * R[0][0] + L[0][1] * R[1][0] + L[0][2] * R[2][0] + L[0][3] * R[3][0],
                L[0][0] * R[0][1] + L[0][1] * R[1][1] + L[0][2] * R[2][1] + L[0][3] * R[3][1],
                L[0][0] * R[0][2] + L[0][1] * R[1][2] + L[0][2] * R[2][2] + L[0][3] * R[3][2],
                L[0][0] * R[0][3] + L[0][1] * R[1][3] + L[0][2] * R[2][3] + L[0][3] * R[3][3],

                L[1][0] * R[0][0] + L[1][1] * R[1][0] + L[1][2] * R[2][0] + L[1][3] * R[3][0],
                L[1][0] * R[0][1] + L[1][1] * R[1][1] + L[1][2] * R[2][1] + L[1][3] * R[3][1],
                L[1][0] * R[0][2] + L[1][1] * R[1][2] + L[1][2] * R[2][2] + L[1][3] * R[3][2],
                L[1][0] * R[0][3] + L[1][1] * R[1][3] + L[1][2] * R[2][3] + L[1][3] * R[3][3],

                L[2][0] * R[0][0] + L[2][1] * R[1][0] + L[2][2] * R[2][0] + L[2][3] * R[3][0],
                L[2][0] * R[0][1] + L[2][1] * R[1][1] + L[2][2] * R[2][1] + L[2][3] * R[3][1],
                L[2][0] * R[0][2] + L[2][1] * R[1][2] + L[2][2] * R[2][2] + L[2][3] * R[3][2],
                L[2][0] * R[0][3] + L[2][1] * R[1][3] + L[2][2] * R[2][3] + L[2][3] * R[3][3],

                L[3][0] * R[0][0] + L[3][1] * R[1][0] + L[3][2] * R[2][0] + L[3][3] * R[3][0],
                L[3][0] * R[0][1] + L[3][1] * R[1][1] + L[3][2] * R[2][1] + L[3][3] * R[3][1],
                L[3][0] * R[0][2] + L[3][1] * R[1][2] + L[3][2] * R[2][2] + L[3][3] * R[3][2],
                L[3][0] * R[0][3] + L[3][1] * R[1][3] + L[3][2] * R[2][3] + L[3][3] * R[3][3]
            );
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::operator *(const T& right) const
    {
        return Matrix4<T>(r1 * right, r2 * right, r3 * right, r4 * right);
    }

    template<typename T>
    inline Vector2<T> Matrix4<T>::operator *(const Vector2<T>& right) const
    {
        const Vector4<T> result = (*this) * Vector4<T>(right.x, right.y, 0, 1);

        return Vector2<T>(result.x, result.y);
    }

    template<typename T>
    inline Vector3<T> Matrix4<T>::operator *(const Vector3<T>& right) const
    {
        const Vector4<T> result = (*this) * Vector4<T>(right.x, right.y, right.z, 1);

        return Vector3<T>(result.x, result.y, result.z);
    }


    template<typename T>
    inline Vector4<T> Matrix4<T>::operator *(const Vector4<T>& right) const
    {
        const T L[ROWS][COLUMNS] =
        {
            {
                (*this)[0][0],
                (*this)[0][1],
                (*this)[0][2],
                (*this)[0][3]
            },
            {
                (*this)[1][0],
                (*this)[1][1],
                (*this)[1][2],
                (*this)[1][3]
            },
            {
                (*this)[2][0],
                (*this)[2][1],
                (*this)[2][2],
                (*this)[2][3]
            },
            {
                (*this)[3][0],
                (*this)[3][1],
                (*this)[3][2],
                (*this)[3][3]
            }
        };

        const T R[4] =
        {
            right.x,
            right.y,
            right.z,
            right.w
        };

        return Vector4<T>
            (
            L[0][0] * R[0] + L[0][1] * R[1] + L[0][2] * R[2] + L[0][3] * R[3],
            L[1][0] * R[0] + L[1][1] * R[1] + L[1][2] * R[2] + L[1][3] * R[3],
            L[2][0] * R[0] + L[2][1] * R[1] + L[2][2] * R[2] + L[2][3] * R[3],
            L[3][0] * R[0] + L[3][1] * R[1] + L[3][2] * R[2] + L[3][3] * R[3]
            );
    }

    template<typename T>
    inline Matrix4<T> Matrix4<T>::operator /(const T& right) const
    {
        return Matrix4<T>(r1 / right, r2 / right, r3 / right, r4 / right);
    }


    // Member access
    template<typename T>
    inline Vector4<T>& Matrix4<T>::operator [](const unsigned int index)
    {
        assert(index < ROWS);
        return (&r1)[index];
    }

    template<typename T>
    inline const Vector4<T>& Matrix4<T>::operator [](const unsigned int index) const
    {
        assert(index < ROWS);
        return (&r1)[index];
    }


    // Friends
    template<typename T>
    inline Matrix4<T> operator *(const T& left, const Matrix4<T>& right)
    {
        return right * left;
    }

    template<typename T>
    inline Vector2<T>& operator *=(Vector2<T>& left, const Matrix4<T>& right)
    {
        left = right * left;

        return left;
    }

    template<typename T>
    inline Vector3<T>& operator *=(Vector3<T>& left, const Matrix4<T>& right)
    {
        left = right * left;

        return left;
    }

    template<typename T>
    inline Vector4<T>& operator *=(Vector4<T>& left, const Matrix4<T>& right)
    {
        left = right * left;

        return left;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& out, const Matrix4<T>& right)
    {
        for (size_t i = 0; i < Matrix4<T>::ROWS; ++i)
        {
            out << "|";
            for (size_t j = 0; j < Matrix4<T>::COLUMNS; ++j)
            {
                out << right[i][j];
                if (j < Matrix4<T>::COLUMNS - 1)
                    out << ", ";
            }
            out << "|" << std::endl;
        }

        return out;
    }
    #pragma endregion
}