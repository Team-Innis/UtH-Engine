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
inline Vector2<T>::Vector2()
    : x(0),
      y(0)
{
    // Nothing to do here.
}

template<typename T>
inline Vector2<T>::Vector2(const T _x, const T _y)
    : x(_x),
      y(_y)
{
    // Nothing more to do here.
}

template<typename T>
template<typename O>
inline Vector2<T>::Vector2(const Vector2<O>& vector)
    : x(static_cast<O>(vector.x)),
      y(static_cast<O>(vector.y))
{
    // Nothing more to do here.
}

template<typename T>
inline Vector2<T>::~Vector2()
{
    // Nothing to do here.
}


/////////////////////////////////////////////////////////////////////////////////////////////////


// Public
template<typename T>
inline Vector2<T>& Vector2<T>::add(const Vector2<T>& vector)
{
    x += vector.x;
    y += vector.y;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>& Vector2<T>::subtract(const Vector2<T>& vector)
{
    x -= vector.x;
    y -= vector.y;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>& Vector2<T>::scale(const T scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector2<T> Vector2<T>::getNormal() const
{
    const T magnitude = getMagnitude();

    Vector2<T> normal(1, 1);

    if (magnitude != 0)
    {
        normal.x = x / magnitude;
        normal.y = y / magnitude;
    }

    return normal;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>& Vector2<T>::normalize()
{
    const T magnitude = getMagnitude();

    if (magnitude != 0)
    {
        x /= magnitude;
        y /= magnitude;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const T Vector2<T>::getMagnitude() const
{
    return std::sqrt(x * x + y * y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const T Vector2<T>::getMagnitudeSq() const
{
    return x * x + y * y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector2<T> Vector2<T>::getWithMagnitude(const T magnitude) const
{
    const T m = getMagnitude();

    T ratio = 1;

    if (m != 0)
    {
        ratio = magnitude / m;
    }

    return Vector2<T>(x * ratio, y * ratio);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>& Vector2<T>::setMagnitude(const T magnitude)
{
    const T m = getMagnitude();

    T ratio = 1;

    if (m != 0)
    {
        ratio = magnitude / m;

        x * ratio;
        y * ratio;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const Vector2<T> Vector2<T>::getComponentProduct(const Vector2<T>& vector) const
{
    return Vector2<T>(x * vector.x, y * vector.y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>& Vector2<T>::setComponentProduct(const Vector2<T>& vector)
{
    x *= vector.x;
    y *= vector.y;

    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline const T Vector2<T>::getScalarProduct(const Vector2<T>& vector) const
{
    return (x * vector.x) + (y * vector.y);
}


/////////////////////////////////////////////////////////////////////////////////////////////////


// ADDITION
// + (addition)
template<typename T>
inline const Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}
// += (addition)
template<typename T>
inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
{
    return left.add(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// SUBTRACTION
// - (opposite vector)
template<typename T>
inline const Vector2<T> operator -(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}
// - (subtraction)
template<typename T>
inline const Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}
// -= (subtraction)
template<typename T>
inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
{
    return left.subtract(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// MULTIPLICATION
// * (multiplication)
template<typename T>
inline const Vector2<T> operator *(const T left, const Vector2<T>& right)
{
    return Vector2<T>(left * right.x, left * right.y);
}
// * (multiplication)
template<typename T>
inline const Vector2<T> operator *(const Vector2<T>& left, const T right)
{
    return Vector2<T>(right * left.x, right * left.y);
}
// *= (multiplication - scale)
template<typename T>
inline Vector2<T>& operator *=(Vector2<T>& left, const T right)
{
    return left.scale(right);
}
// * (multiplication - scalar product)
template<typename T>
inline const T operator *(Vector2<T>& left, const Vector2<T>& right)
{
    return left.getScalarProduct(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// EQUALITY
// ==
template<typename T>
inline const bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// INEQUALITY
// !=
template<typename T>
inline const bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x != right.x) && (left.y != right.y);
}