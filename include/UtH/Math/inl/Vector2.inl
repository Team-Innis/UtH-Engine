#include "../Vector2.hpp"
#include "../Util.hpp"

#include <cassert>
#include <cmath>

namespace pmath
{
    template<typename T>
    inline Vector2<T>::Vector2()
        : x(T()),
          y(T())
    { }

    template<typename T>
    inline Vector2<T>::Vector2(const T& x, const T& y)
        : x(x),
          y(y)
    { }

    template<typename T>
    inline Vector2<T>::Vector2(T value)
        : x(value),
          y(value)
    { }

    template<typename T>
    inline Vector2<T>::Vector2(const Vector2<T>& vector2)
        : x(vector2.x),
          y(vector2.y)
    { }

    template<typename T>
    template<typename T2>
    inline Vector2<T>::Vector2(const Vector2<T2>& vector2)
        : x(static_cast<T>(vector2.x)),
          y(static_cast<T>(vector2.y))
    { }

    template<typename T>
    inline Vector2<T>::~Vector2()
    { }


    // Public
    template<typename T>
    inline T Vector2<T>::dot(const Vector2<T>& other) const
    {
        return x * other.x + y * other.y;
    }
    template<typename T>
    inline T Vector2<T>::dot(const Vector2<T>& vec1, const Vector2<T>& vec2)
    {
        return vec1.dot(vec2);
    }

    template<typename T>
    inline T Vector2<T>::cross(const Vector2<T>& other) const
    {
        return (x * other.y) - (y * other.x);
    }

    template<typename T>
    inline T Vector2<T>::cross(const Vector2<T>& vec1, const Vector2<T>& vec2)
    {
        return vec1.cross(vec2);
    }

    template<typename T>
    inline double Vector2<T>::lengthSquared() const
    {
        const double xd = static_cast<double>(x);
        const double yd = static_cast<double>(y);
        return xd*xd + yd*yd;
    }

    template<typename T>
    inline double Vector2<T>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template<typename T>
    inline double Vector2<T>::distance(const Vector2<T>& vec1, const Vector2<T>& vec2)
    {
        return (vec2 - vec1).length();
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::normalize()
    {
        return *this = unitVector();
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::unitVector() const
    {
        return *this / static_cast<T>(length());
    }

    template<typename T>
    inline bool Vector2<T>::isUnitVector() const
    {
        // LengthSquared returns double.
        // Also sqrt(1) == 1 so we don't need to do that
        return equals<double>(this->lengthSquared(), 1);
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::lerp(const Vector2<T>& vec1, const Vector2<T>& vec2, const T& t)
    {
        return (1 - t) * vec1 + t * vec2;
    }

    // Operators
    #pragma region Operators
    // Comparison operators
    template<typename T>
    inline bool Vector2<T>::operator ==(const Vector2<T>& right) const
    {
        return equals<T>(x, right.x) && equals<T>(y, right.y);
    }

    template<typename T>
    inline bool Vector2<T>::operator !=(const Vector2<T>& right) const
    {
        return !(*this == right);
    }

    template<typename T>
    inline bool Vector2<T>::operator >(const Vector2<T>& right) const
    {
        return lengthSquared() > right.lengthSquared();
    }

    template<typename T>
    inline bool Vector2<T>::operator <(const Vector2<T>& right) const
    {
        return lengthSquared() < right.lengthSquared();
    }

    template<typename T>
    inline bool Vector2<T>::operator >=(const Vector2<T>& right) const
    {
        return lengthSquared() >= right.lengthSquared();
    }

    template<typename T>
    inline bool Vector2<T>::operator <=(const Vector2<T>& right) const
    {
        return lengthSquared() <= right.lengthSquared();
    }

    // Assingment operators
    template<typename T>
    inline Vector2<T>& Vector2<T>::operator =(const Vector2<T>& right)
    {
        x = right.x;
        y = right.y;

        return *this;
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator +=(const Vector2<T>& right)
    {
        x += right.x;
        y += right.y;

        return *this;
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator -=(const Vector2<T>& right)
    {
        x -= right.x;
        y -= right.y;

        return *this;
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator *=(const T& right)
    {
        x *= right;
        y *= right;

        return *this;
    }

    template<typename T>
    inline Vector2<T>& Vector2<T>::operator /=(const T& right)
    {
        x /= right;
        y /= right;

        return *this;
    }


    // Arithmetic operators
    template<typename T>
    inline Vector2<T> Vector2<T>::operator +(const Vector2<T>& right) const
    {
        return Vector2<T>(x + right.x, y + right.y);
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator -() const
    {
        return Vector2<T>(-x, -y);
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator -(const Vector2<T>& right) const
    {
        return Vector2<T>(x - right.x, y - right.y);
    }   

    template<typename T>
    inline Vector2<T> Vector2<T>::operator *(const T& right) const
    {
        return Vector2<T>(x * right, y * right);
    }

    template<typename T>
    inline Vector2<T> Vector2<T>::operator /(const T& right) const
    {
        return Vector2<T>(x / right, y / right);
    }

    template<typename T>
    inline Vector2<T> operator *(const T& left, const Vector2<T>& right)
    {
        return right * left;
    }
    
    template<typename T>
    inline std::ostream& operator <<(std::ostream& out, const Vector2<T>& right)
    {
        out << "(" << right.x << ", " << right.y << ")";

        return out;
    }

    // Member access operators
    template<typename T>
    inline T& Vector2<T>::operator [](const unsigned int index)
    {
        assert(index < COMPONENTS);
        return (&x)[index];
    }

    template<typename T>
    inline const T& Vector2<T>::operator [](const unsigned int index) const
    {
        assert(index < COMPONENTS);
        return (&x)[index];
    }
    #pragma endregion
}