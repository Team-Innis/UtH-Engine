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

template<typename T>
inline Vector3<T>::Vector3()
    : x(0),
      y(0),
      z(0)
{
    // Nothing more to do here.
}

template<typename T>
inline Vector3<T>::Vector3(const T _x, const T _y, const T _z)
    : x(_x),
      y(_y),
      z(_z)
{
    // Nothing more to do here.
}

template<typename T>
template<typename O>
inline Vector3<T>::Vector3(const Vector3<O>& vector)
    : x(static_cast<O>(vector.x)),
      y(static_cast<O>(vector.y)),
      z(static_cast<O>(vector.z))
{
    // Nothing more to do here.
}

template<typename T>
inline Vector3<T>::~Vector3()
{
    // Nothing to do here.
}


/////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
inline Vector3<T>& Vector3<T>::add(const Vector3<T>& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>& Vector3<T>::subtract(const Vector3<T>& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>& Vector3<T>::scale(const T scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector3<T> Vector3<T>::getNormal() const
{
    const T magnitude = getMagnitude();

    Vector3<T> normal(1, 1, 1);

    if (magnitude != 0.f)
    {
        normal.x = x / magnitude;
        normal.y = y / magnitude;
        normal.z = z / magnitude;
    }

    return normal;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>& Vector3<T>::normalize()
{
    const T magnitude = getMagnitude();

    if (magnitude != 0.f)
    {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const T Vector3<T>::getMagnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const T Vector3<T>::getMagnitudeSq() const
{
    return x * x + y * y + z * z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector3<T> Vector3<T>::getWithMagnitude(const T magnitude) const
{
    const T m = getMagnitude();

    T ratio = 1;

    if (m != 0)
    {
        ratio = magnitude / m;
    }

    return Vector3<T>(x * ratio, y * ratio, z * ratio);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>& Vector3<T>::setMagnitude(const T magnitude)
{
    const T m = getMagnitude();

    T ratio = 1;

    if (m != 0)
    {
        ratio = magnitude / m;

        x * ratio;
        y * ratio;
        z * ratio;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector3<T> Vector3<T>::getComponentProduct(const Vector3<T>& vector) const
{
    return Vector2<T>(x * vector.x, y * vector.y, z * vector.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>& Vector3<T>::setComponentProduct(const Vector3<T>& vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const T Vector3<T>::getScalarProduct(const Vector3<T>& vector) const
{
    return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector3<T> Vector3<T>::getCrossProduct(const Vector3<T>& vector) const
{
    return Vector3<T>((y * vector.z) - (z * vector.y),
                      (z * vector.x) - (x * vector.z),
                      (x * vector.y) - (y * vector.x));
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>& setCrossProduct(const Vector3<T>& vector)
{
    *this = getCrossProduct(vector);

    return *this;
}


/////////////////////////////////////////////////////////////////////////////////////////////////


// ADDITION
// + (addition)
template<typename T>
inline const Vector3<T> operator +(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}
// += (addition)
template<typename T>
inline Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right)
{
    return left.add(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// SUBTRACTION
// - (opposite vector)
template<typename T>
inline const Vector3<T> operator -(const Vector3<T>& right)
{
    return Vector3<T>(-right.x, -right.y, -right.z);
}
// - (subtraction)
template<typename T>
inline const Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}
// -= (subtraction)
template<typename T>
inline Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right)
{
    return left.subtract(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// MULTIPLICATION
// * (multiplication)
template<typename T>
inline const Vector3<T> operator *(const T left, const Vector3<T>& right)
{
    return Vector3<T>(left * right.x, left * right.y, left * right.z);
}
// * (multiplication)
template<typename T>
inline const Vector3<T> operator *(const Vector3<T>& left, const T right)
{
    return Vector3<T>(right * left.x, right * left.y, right * left.z);
}
// *= (multiplication - scale)
template<typename T>
inline Vector3<T>& operator *=(Vector3<T>& left, const T right)
{
    return left.scale(right);
}
// * (multiplication - scalar product)
template<typename T>
inline const T operator *(const Vector3<T>& left, const Vector3<T>& right)
{
    return left.getScalarProduct(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// MODULUS
// % (modulus - cross product)
template<typename T>
inline const Vector3<T> operator %(const Vector3<T>& left, const Vector3<T>& right)
{
    return left.getCrossProduct(right);
}
// %= (modulus - cross product)
template<typename T>
inline const Vector3<T>& operator %=(Vector3<T>& left, const Vector3<T>& right)
{
    return left.setCrossProduct(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// EQUALITY
// ==
template<typename T>
inline const bool operator ==(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// INEQUALITY
// !=
template<typename T>
inline const bool operator !=(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x != right.x) && (left.y != right.y) && (left.z != right.z);
}



// Non-member functions.

template<typename T>
inline void setOrthonormalBasis(Vector3<T>& a, Vector3<T>& b, Vector3<T>& c)
{
    a.normalize();

    c = a % b;
    if (c.getMagnitudeSq() == 0)
        return;

    c.normalize();

    b = c % a;
}