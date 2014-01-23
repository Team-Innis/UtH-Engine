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

// Headers
#include <Vector3.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace uth
{

    /////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// A class for storing and manipulating a quaternion.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////
    class Quaternion
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Functions
        /////////////////////////////////////////////////////////////////////////////////////////////////

        /// Default constructor.
        ///
        /// Sets the values of all the member variables to 0.
        ///
        /**/ Quaternion();

        /// Overloaded constructor for intialization.
        ///
        /// Sets the values of the components according to the arguments.
        ///
        /**/ Quaternion(const double& X, const double& Y, const double& Z, const double& W);

        /// Overloaded constructor for initialization from another Quaternion.
        ///
        /// Copies the values from the given quaternion into this one.
        ///
        /**/ Quaternion(const Quaternion& q);

        /// Overloaded constructor for initialization from euler angles.
        ///
        /**/ Quaternion(const Vector3F& rotation);

        /// Destructor.
        ///
        /**/ ~Quaternion();


        /// Multiply this quaternion by another.
        ///
        /// \return Reference to this quaternion, allowing chaining functions.
        ///
        /**/ Quaternion& multiply(const Quaternion& q);


        /// Combine this quaternion with another.
        ///
        /// \return Reference to this quaternion, allowing chaining functions.
        ///
        /**/ Quaternion& combine(const Quaternion& q);


        /// Get the normalized quaternion.
        ///
        /// \return A quaternion whose magnitude is 1.
        ///
        /**/ const Quaternion getNormal() const;


        /// \brief Normalize the internal quaternion.
        ///
        /// This causes the loss of the current values and replaces
        /// them with the normal of the quaternion.
        ///
        /// \return Reference to this quaternion, allowing chaining functions.
        ///
        /**/ Quaternion& normalize();


        /// \brief Get the magnitude of the quaternion.
        ///
        /// \return Magnitude of the quaternion.
        ///
        /**/ const double getMagnitude() const;


        /// \brief Get the squared magnitude of the quaternion.
        ///
        /// Used mainly for optimization reasons, as the rooting operation
        /// doesn't have to be performed here.
        ///
        /// \return Magnitude^2 of the quaternion.
        ///
        /**/ const double getMagnitudeSq() const;


    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////
        /// Member data.
        /////////////////////////////////////////////////////////////////////////////////////////////////
        
        double  x,  ///< The X component.
                y,  ///< The Y component.
                z,  ///< The Z component.
                w;  ///< The W component.


    }; // class Quaternion


    // * (multiplication)
    const Quaternion operator *(const Quaternion& left, const Quaternion& right);
    // *= (multiplication)
    Quaternion& operator *=(Quaternion& left, const Quaternion& right);


    // ==
    const bool operator ==(const Quaternion& left, const Quaternion& right);

    // !=
    const bool operator !=(const Quaternion& left, const Quaternion& right);
    

} // namespace uth