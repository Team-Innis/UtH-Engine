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
	
}

template<typename T, int R, int C>
Matrix<T, R, C>::Matrix(const Matrix<T, R, C>& other)
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            m_matrix[i][j] = other(i + 1, j + 1);
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
template<typename OT, int OR, int OC>
Matrix<T, R, OC> Matrix<T, R, C>::multiply(const Matrix<OT, C, OC>& matrix)
{
	Matrix<T, R, OC> result;

	for (int i = 0; i < R; i++)
	{
		for (int res = 0; res < OC; res++)
		{
			for (int j = 0; j < C; j++)
			{
				result[i][res] += (result[i][j] * matrix[j][res]);
			}
		}
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::multiply(const T scalar)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			m_matrix[i][j] *= scalar;
		}
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R - 1, C - 1> Matrix<T, R, C>::getMinor(const int row, const int column)
{
	Matrix<T, R - 1, C - 1> result;

	if (row < 0		||
		column < 0	||
		row >= R	||
		column >= C ||
		R < 2		||
		C < 2)
		return result;


	for (int i = 1; i <= (R - (row >= R)); i++)
	{
		for (int j = 1; i <= (C - (column >= C)); j++)
		{
			result(i - (i > row), j - (j > column)) = m_matrix[i - 1][j - 1];
		}
	}

	return result;
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
	*this = getInverse();

	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::getInverse() const
{
	Matrix<T, R, C> result;

	const T det = determinant();

	if (det == 0) return *this;

	if (R == 1)
	{
		result(1, 1) = 1 / m_matrix[0][0];
	}
	else if (R == 2)
	{
		result(1, 1) = m_matrix[1][1];
		result(1, 2) = -m_matrix[0][1];
		result(2, 1) = -m_matrix[1][0];
		result(2, 2) = m_matrix[0][0];

		result = (1 / det) * result;
	}
	else
	{
		result.makeDiagonal();

		Matrix<T, R, C> temp(*this);

		for (int c = 1; c <= C; c++)
		{
			for (int r = c; r <= R && temp(r, c) == 0; r++)
			{
				if (r != c)
				{
					for (int s = 1; s <= C; s++)
					{
						std::swap(temp(c, s), temp(r, s));
						std::swap(result(c, s), result(r, s));
					}
				}
			}

			for (int r = 1; r <= R; r++)
			{
				if (r != c)
				{
					if (temp(r, c) != 0)
					{
						const T f = -temp(r, c) / temp(c, c);

						for (int s = 1; s <= C; s++)
						{
							temp(r, s) += f * temp(c, s);
							result(r, s) += f * result(c, s);
						}
					}
				}
				else
				{
					const T f = temp(c, c);

					for (int s = 1; s <= C; s++)
					{
						temp(r, s) /= f;
						result(r, s) /= f;
					}
				}
			}
		}
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
const T Matrix<T, R, C>::determinant() const
{
    if (R != C) return 0;

    T det = 0;


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
            Matrix<T, R - 1, C - 1> temp = minor(1, i);

            det += ((i % 2) + (i % 2) - 1) * m_matrix[0][i - 1] * temp.determinant();
        }
    }

    return det;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
T& Matrix<T, R, C>::get(const int row, const int column)
{
	if (row > R || column > C || row <= 0 || column <= 0) return m_matrix[0][0];

    return m_matrix[row - 1][column - 1];
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator =(const Matrix<T, R, C>& other)
{
	for (int i = 1; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            m_matrix[i][j] = other(i + 1, j + 1);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
const T& Matrix<T, R, C>::operator ()(const int row, const int column) const
{
    if (row > R || column > C || row <= 0 || column <= 0) return m_matrix[0][0];

    return m_matrix[row - 1][column - 1];
}


template<typename T, int R, int C>
T& Matrix<T, R, C>::operator [](const int index)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::operator *=(const Matrix<T, R, C>& right)
{
	return multiply(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, OC> Matrix<T, R, C>::operator *(const Matrix<OT, C, OC>& right)
{
	Matrix<T, R, OC> result;

	for (int i = 0; i < R; i++)
	{
		for (int res = 0; res < OC; res++)
		{
			for (int j = 0; j < C; j++)
			{
				result[i][res] += (result[i][j] * matrix[j][res]);
			}
		}
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::operator *=(const T scalar)
{
	return multiply(scalar);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C> Matrix<T, R, C>::operator *(const T scalar)
{
	Matrix<T, R, OC> result(*this);

	return result.multiply(scalar);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C>& Matrix<T, R, C>::operator +=(const Matrix<OT, OR, OC>& right)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C> Matrix<T, R, C>::operator +(const Matrix<OT, OR, OC>& right)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C>& Matrix<T, R, C>::operator -=(const Matrix<OT, OR, OC>& right)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
template<typename OT, int OR, int OC>
Matrix<T, R, C> Matrix<T, R, C>::operator -(const Matrix<OT, OR, OC>& right)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
bool Matrix<T, R, C>::operator ==(const Matrix<T, R, C>& right)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (m_matrix[i][j] != right[i][j])
				return false;
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
bool Matrix<T, R, C>::operator !=(const Matrix<T, R, C>& right)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (m_matrix[i][j] != right[i][j])
				return true;
		}
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, int R, int C>
Matrix<T, R, C> operator *(const T scalar, Matrix<T, R, C>& matrix)
{
	Matrix<T, R, C> result(matrix);

	return result.multiply(scalar);
}