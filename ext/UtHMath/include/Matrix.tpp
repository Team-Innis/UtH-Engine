/*
 * Copyright (c) 2014 Team-Innis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

template<typename T, int R, int C>
Matrix<T, R, C>::Matrix()
{
    // Nothing to do here.
}

template<typename T, int R, int C>
Matrix<T, R, C>::Matrix(const Matrix<T, R, C>& other)
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            m_matrix[i][j] = other[i][j];
        }
    }
}

template<typename T, int R, int C>
Matrix<T, R, C>::~Matrix()
{
    // Nothing to do here.
}


/////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::fill(const T value)
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            m_matrix[i][j] = value;
        }
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::makeDiagonal()
{
    fill(0);

    for (int i = 0; (i < R && i < C); i++)
    {
        m_matrix[i][i] = 1;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename RT, int RR, int RC>
Matrix<RT, RT, RC> Matrix<T, R, C>::getMinor(const int row, const int column)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
const int Matrix<T, R, C>::rows()
{
    return R;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
const int Matrix<T, R, C>::columns()
{
    return C;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::invert()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
const T Matrix<T, R, C>::determinant() const
{
    if (R != C) return 0;

    double det = 0;


    if (R == 1)
    {
        det = m_matrix[0][0];
    }
    else if (R == 2)
    {
        det = m_matrix[0][0] * m_matrix[1][1] - m_matrix[1][0] * m_matrix[0][1];
    }
    else
    {
        for (int i = 1; i <= C; i++)
        {
            Matrix<T, R, C> M = minor(1, i);

            det += ((i % 2) + (i % 2) - 1) * m_matrix[0][i - 1] * M.determinant();
        }
    }

    return det;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator =(const Matrix<T, R, C>& other)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
T* Matrix<T, R, C>::operator [](const int index)
{
    return m_matrix[index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
T& Matrix<T, R, C>::operator ()(const int row, const int column)
{
    if (row > R || column > C || row <= 0 || column <= 0) return m_matrix[0][0];

    return m_matrix[row - 1][column - 1];
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::operator *=(const Matrix<T, C, C>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C> Matrix<T, R, C>::operator *(const Matrix<OT, C, OC>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C>& Matrix<T, R, C>::operator +=(const Matrix<OT, OR, OC>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C> Matrix<T, R, C>::operator +(const Matrix<OT, OR, OC>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C>& Matrix<T, R, C>::operator -=(const Matrix<OT, OR, OC>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C> Matrix<T, R, C>::operator -(const Matrix<OT, OR, OC>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
bool Matrix<T, R, C>::operator ==(const Matrix<OT, OR, OC>& right);

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
bool Matrix<T, R, C>::operator !=(const Matrix<OT, OR, OC>& right);