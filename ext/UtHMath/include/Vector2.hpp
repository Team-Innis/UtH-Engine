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
    /// A template class for storing and manipulating a two-dimensional vector.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class Vector2
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Functions
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /// Default constructor.
        ///
        /// Sets the values of all the member variables to 0.
        ///
        /**/ Vector2();

        /// Overloaded constructor for intialization.
        ///
        /// Sets the values of the components according to the arguments.
        ///
        /**/ Vector2(const T _x, const T _y);

        /// Overloaded constructor for initialization from another Vector2 of any type.
        ///
        /// Copies the values from the given vector into this one.
        ///
        /**/ template<typename O>
        /**/ Vector2(const Vector2<O>& vector);

        /// Destructor.
        ///
        /**/ ~Vector2();


        /// Addition operation.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector2& add(const Vector2& vector);


        /// Subtraction operation.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector2& subtract(const Vector2& vector);


        /// Scaling operation.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector2& scale(const T scalar);


        /// Get the normalized vector.
        ///
        /// \return Vector whose magnitude is 1.
        ///
        /**/ const Vector2 getNormal() const;


        /// Normalize the internal vector.
        ///
        /// This causes the loss of the current values and replaces
        /// them with the normal of the vector.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector2& normalize();


        /// Get the magnitude of the vector.
        ///
        /// \return Magnitude of the vector.
        ///
        /**/ const T getMagnitude() const;


        /// Get the squared magnitude of the vector.
        ///
        /// Used mainly for optimization reasons, as the rooting operation
        /// doesn't have to be performed here.
        ///
        /// \return Magnitude^2 of the vector.
        ///
        /**/ const T getMagnitudeSq() const;


        /// Get the vector with the given magnitude applied.
        /// No changes are made to the internal values.
        ///
        /// \return Vector2 with the given magnitude.
        ///
        /**/ const Vector2 getWithMagnitude(const T magnitude) const;


        /// Transform this vector to the given magnitude.
        /// This function will replace the existing vector with the new one.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector2& setMagnitude(const T magnitude);


        /// Get the vector component product.
        /// No changes are made to the internal values.
        ///
        /// \return Vector with the calculations applied.
        ///
        /**/ const Vector2 getComponentProduct(const Vector2& vector) const;


        /// Transform this vector into its component product.
        /// This function will replace the existing vector with the new one.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector2& setComponentProduct(const Vector2& vector);


        /// Get the vector scalar product. This is the same as dot product.
        ///
        /// \return Scalar product of the vector.
        ///
        /**/ const T getScalarProduct(const Vector2& vector) const;


    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Functions
        /////////////////////////////////////////////////////////////////////////////////////////////////

        T x, y;     ///< the X and Y components.


    }; // class Vector2


    // ADDITION
    // + (addition)
    template<typename T>
    const Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);
    // += (addition)
    template<typename T>
    Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);


    // SUBTRACTION
    // - (opposite vector)
    template<typename T>
    const Vector2<T> operator -(const Vector2<T>& right);
    // - (subtraction)
    template<typename T>
    const Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);
    // -= (subtraction)
    template<typename T>
    Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);


    // MULTIPLICATION
    // * (multiplication)
    template<typename T>
    const Vector2<T> operator *(const T left, const Vector2<T>& right);
    // * (multiplication)
    template<typename T>
    const Vector2<T> operator *(const Vector2<T>& left, const T right);
    // *= (multiplication - scale)
    template<typename T>
    Vector2<T>& operator *=(Vector2<T>& left, const T right);
    // * (multiplication - scalar product)
    template<typename T>
    const T operator *(const Vector2<T>& left, const Vector2<T>& right);


    // EQUALITY
    // ==
    template<typename T>
    const bool operator ==(const Vector2<T>& left, const Vector2<T>& right);


    // INEQUALITY
    // !=
    template<typename T>
    const bool operator !=(const Vector2<T>& left, const Vector2<T>& right);


    /// Include implementation file.
    ///
    #include <GP\Math\Vector2.inl>
    

    /// Typedefs of most common data types.
    ///
    typedef Vector2<int>    Vector2I;
    typedef Vector2<float>  Vector2F;
    typedef Vector2<double> Vector2D;


} // namespace uth