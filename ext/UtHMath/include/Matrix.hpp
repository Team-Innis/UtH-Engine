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

/***********************************************************************************************/
/**/ #pragma once
/***********************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace uth
{

    /////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// A template class for storing a matrix.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////

    /// T = Type
    /// R = Rows
    /// C = Columns
    template<typename T, int R, int C>
    class Matrix
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Functions
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /// Default constructor.
        ///
        /**/ Matrix();

        /// Copy constructor.
        ///
        /**/ Matrix(const Matrix& other);

        /// Destructor.
        ///
        /**/ ~Matrix();


        /// Fill the matrix with the given value.
        ///
        /**/ Matrix& fill(const T value);


        /// Make diagonal.
        ///
        /**/ Matrix& makeDiagonal();


        /// Get the minor of the matrix.
        ///
        template<typename RT, int RR, int RC>
        /**/ Matrix<RT, RR, RC> getMinor(const int row, const int column);


        /// Get the number of rows.
        ///
        /**/ const int rows();


        /// Get the number of columns.
        ///
        /**/ const int columns();


        /// Invert the matrix.
        ///
        /// \return Reference to the matrix, allowing chaining functions.
        ///
        /**/ Matrix& invert();


        /// Get the determinant.
        ///
        /// \return Reference to the matrix, allowing chaining functions.
        ///
        /**/ const T determinant() const;


        /// Get the given element.
        ///
        /**/ const T& get(const int row, const int column);


    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Member data
        /////////////////////////////////////////////////////////////////////////////////////////////////

        T m_matrix[R][C];     ///< An array containing the elements.


    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Operators
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /// = (copy assignment)
        ///
        /**/ Matrix operator =(const Matrix& other);


        /// [] (access element)
        ///
        /**/ T* operator [](const int index);


        /// () (access element)
        ///
        /// This operator is one-based instead of zero-based.
        ///
        /**/ T& operator ()(const int row, const int column);


        /// *= (multiplication)
        ///
        /**/ Matrix& operator *=(const Matrix<T, R, C>& right);


        /// * (multiplication)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ Matrix<T, R, C> operator *(const Matrix<OT, C, OC>& right);


        /// += (addition)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ Matrix& operator +=(const Matrix<OT, OR, OC>& right);


        /// + (addition)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ Matrix operator +(const Matrix<OT, OR, OC>& right);


        /// -= (subtraction)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ Matrix& operator -=(const Matrix<OT, OR, OC>& right);


        /// - (subtraction)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ Matrix operator -(const Matrix<OT, OR, OC>& right);


        /// == (equality)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ bool operator ==(const Matrix<OT, OR, OC>& right);


        /// != (inequality)
        ///
        /**/ template<typename OT, int OR, int OC>
        /**/ bool operator !=(const Matrix<OT, OR, OC>& right);


    }; // class Matrix


    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Non-member functions
    /////////////////////////////////////////////////////////////////////////////////////////////////

    //multiply()
    //...

    
    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// Other
    /////////////////////////////////////////////////////////////////////////////////////////////////

    /// Include the implementation file.
    ///
    #include <Matrix4.tpp>


    /// Typedefs of the most common matrix types.
    ///
    typedef Matrix<float, 3, 3> Matrix3x3F;
    typedef Matrix<float, 4, 4> Matrix4x4F;


} // namespace uth