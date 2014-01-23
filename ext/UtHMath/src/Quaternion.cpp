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

// Headers
#include <Quaternion.hpp>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace uth
{

    Quaternion::Quaternion()
        : x(0.0),
          y(0.0),
          z(0.0),
          w(1.0)
    {
        // Nothing more to do here.
    }

    Quaternion::Quaternion(const double& X, const double& Y, const double& Z, const double& W)
        : x(X),
          y(Y),
          z(Z),
          w(W)
    {
        // Nothing more to do here.
    }

    Quaternion::Quaternion(const Quaternion& q)
        : x(q.x),
          y(q.y),
          z(q.z),
          w(q.w)
    {
        // Nothing more to do here.
    }

    Quaternion::Quaternion(const Vector3F& rotation)
    {
        const double heading  = rotation.y,
                     attitude = rotation.z,
                     bank     = rotation.x;

        const double c1 = cos(heading / 2.0),
                     c2 = cos(attitude / 2.0),
                     c3 = cos(bank / 2.0),
                     s1 = sin(heading / 2.0),
                     s2 = sin(attitude / 2.0),
                     s3 = sin(bank / 2.0);

        *this = Quaternion((c1 * c2 * c3) - (s1 * s2 * s3),
                           (s1 * s2 * c3) + (c1 * c2 * s3),
                           (s1 * c2 * c3) + (c1 * s2 * s3),
                           (c1 * s2 * c3) - (s1 * c2 * s3));
    }

    Quaternion::~Quaternion()
    {
        // Nothing to do here.
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////


    Quaternion& Quaternion::multiply(const Quaternion& q)
    {
        *this = Quaternion((w * q.w) - (x * q.x) - (y * q.y) - (z * q.z),
                           (w * q.x) + (x * q.w) + (y * q.z) - (z * q.y),
                           (w * q.y) - (x * q.z) + (y * q.w) + (z * q.x),
                           (w * q.z) + (x * q.y) - (y * q.x) + (z * q.w));

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    Quaternion& Quaternion::combine(const Quaternion& q)
    {
        const double angSin = sin(q.w / 2.0);

        Quaternion temp(q.x * angSin,
                        q.y * angSin,
                        q.z * angSin,
                        cos(q.w / 2.0));

        return multiply(temp);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    const Quaternion Quaternion::getNormal() const
    {
        const double magnitude = getMagnitude();

        return Quaternion(x / magnitude,
                          y / magnitude,
                          z / magnitude,
                          w / magnitude);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    Quaternion& Quaternion::normalize()
    {
        const double magnitude = getMagnitude();

        *this = Quaternion(x / magnitude,
                           y / magnitude,
                           z / magnitude,
                           w / magnitude);

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    const double Quaternion::getMagnitude() const
    {
        return sqrt(pow(w, 2.0) +
                    pow(x, 2.0) +
                    pow(y, 2.0) +
                    pow(z, 2.0));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    const double Quaternion::getMagnitudeSq() const
    {
        return pow(w, 2.0) +
               pow(x, 2.0) +
               pow(y, 2.0) +
               pow(z, 2.0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    const Quaternion operator *(const Quaternion& left, const Quaternion& right)
    {
        const Quaternion a = left;
        const Quaternion b = right;

        Quaternion quaternion((a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
                              (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y),
                              (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x),
                              (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w));

        return quaternion;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    Quaternion& operator *=(Quaternion& left, Quaternion& right)
    {
        return left.multiply(right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    bool operator ==(Quaternion& left, Quaternion& right)
    {
        return (left.w == right.w) &&
               (left.x == right.x) &&
               (left.y == right.y) &&
               (left.z == right.z);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    bool operator !=(Quaternion& left, Quaternion& right)
    {
        return (left.w != right.w) &&
               (left.x != right.x) &&
               (left.y != right.y) &&
               (left.z != right.z);
    }

} // namespace uth