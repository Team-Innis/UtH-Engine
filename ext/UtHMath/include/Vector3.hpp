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

#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace uth
{

    /////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// A template class for storing and manipulating a three-dimensional vector.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class Vector3
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Functions
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /// Default constructor.
        ///
        /// Sets the values of all the member variables to 0.
        ///
        /**/ Vector3();

        /// Overloaded constructor for intialization.
        ///
        /// Sets the values of the components according to the arguments.
        ///
        /**/ Vector3(const T _x, const T _y, const T _z);

        /// Overloaded constructor for initialization from another Vector3 of any type.
        ///
        /// Copies the values from the given vector into this one.
        ///
        /**/ template<typename O>
        /**/ Vector3(const Vector3<O>& vector);

        /// Destructor.
        ///
        /**/ ~Vector3();


        /// Addition operation.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& add(const Vector3& vector);


        /// Subtraction operation.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& subtract(const Vector3& vector);


        /// Scaling operation.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& scale(const T scalar);


        /// Get the normalized vector.
        ///
        /// \return Vector whose magnitude is 1.
        ///
        /**/ const Vector3 getNormal() const;


        /// Normalize the internal vector.
        ///
        /// This causes the loss of the current values and replaces
        /// them with the normal of the vector.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& normalize();


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
        /**/ const Vector3 getWithMagnitude(const T magnitude) const;


        /// Transform the vector to the given magnitude.
        /// This function will replace the existing vector with the new one.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& setMagnitude(const T magnitude);


        /// Get the vector component product.
        /// No changes are made to the internal values.
        ///
        /// \return Vector with the calculations applied.
        ///
        /**/ const Vector3 getComponentProduct(const Vector3& vector) const;


        /// Transform this vector into its component product.
        /// This function will replace the existing vector with the new one.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& setComponentProduct(const Vector3& vector);


        /// Get the vector scalar product. This is the same as dot product.
        ///
        /// \return Scalar product of the vector.
        ///
        /**/ const T getScalarProduct(const Vector3& vector) const;


        /// Get the vector cross product.
        /// No changes are made to the internal values.
        ///
        /// \return Vector with the calculations applied.
        ///
        /**/ const Vector3 getCrossProduct(const Vector3& vector) const;


        /// Transform this vector into its component product.
        /// This function will replace the existing vector with the new one.
        ///
        /// \return Reference to this vector, allowing chaining functions.
        ///
        /**/ Vector3& setCrossProduct(const Vector3& vector);


    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Member data
        /////////////////////////////////////////////////////////////////////////////////////////////////

        T x, y, z;      ///< The X, Y and Z components.


    }; // class Vector3


    // ADDITION
    // + (addition)
    template<typename T>
    const Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right);
    // += (addition)
    template<typename T>
    Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right);


    // SUBTRACTION
    // - (opposite vector)
    template<typename T>
    const Vector3<T> operator -(const Vector3<T>& right);
    // - (subtraction)
    template<typename T>
    const Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);
    // -= (subtraction)
    template<typename T>
    Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right);


    // MULTIPLICATION
    // * (multiplication)
    template<typename T>
    const Vector3<T> operator *(const T left, const Vector3<T>& right);
    // * (multiplication)
    template<typename T>
    const Vector3<T> operator *(const Vector3<T>& left, const T right);
    // *= (multiplication - scale)
    template<typename T>
    Vector3<T>& operator *=(Vector3<T>& left, const T right);
    // * (multiplication - scalar product)
    template<typename T>
    const T operator *(const Vector3<T>& left, const Vector3<T>& right);


    // MODULUS
    // % (modulus - cross product)
    template<typename T>
    const Vector3<T> operator %(const Vector3<T>& left, const Vector3<T>& right);
    // %= (modulus - cross product)
    template<typename T>
    Vector3<T>& operator %=(Vector3<T>& left, const Vector3<T>& right);


    // EQUALITY
    // ==
    template<typename T>
    const bool operator ==(const Vector3<T>& left, const Vector3<T>& right);


    // INEQUALITY
    // !=
    template<typename T>
    const bool operator !=(const Vector3<T>& left, const Vector3<T>& right);



    /// Transform three vectors into their orthonormal basis.
    /// All internal values are replaced with new ones.
    ///
    /**/ template<typename T>
    /**/ void setOrthonormalBasis(Vector3<T>& a, Vector3<T>& b, Vector3<T>& c);


    /// Include implementation file.
    ///
    #include <Vector3.inl>


    /// Typedefs of most common data types.
    ///
    typedef Vector3<int>    Vector3I;
    typedef Vector3<float>  Vector3F;
    typedef Vector3<double> Vector3D;


} // namespace uth