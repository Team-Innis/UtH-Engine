#include "../Vector4.hpp"
#include "../Util.hpp"

#include <cassert>
#include <cmath>
#include <sstream>

namespace pmath
{
    template<typename T>
    inline Vector4<T>::Vector4()
        : x(T()),
          y(T()),
          z(T()),
          w(T())
    { }

    template<typename T>
    inline Vector4<T>::Vector4(const T& x, const T& y, const T& z, const T& w)
        : x(x),
          y(y),
          z(z),
          w(w)
    { }

    template<typename T>
    inline Vector4<T>::Vector4(const T& value)
        : x(value),
          y(value),
          z(value),
          w(value)
    { }

    template<typename T>
    inline Vector4<T>::Vector4(const Vector2<T>& vector, const T& z, const T& w)
        : x(vector.x),
          y(vector.y),
          z(z),
          w(w)
    { }


    template<typename T>
    inline Vector4<T>::Vector4(const Vector3<T>& vector, const T& w)
        : x(vector.x),
          y(vector.y),
          z(vector.z),
          w(w)
    { }


    template<typename T>
    inline Vector4<T>::Vector4(const Vector4<T>& vector4)
        : x(vector4.x),
          y(vector4.y),
          z(vector4.z),
          w(vector4.w)
    { }

    template<typename T>
    template<typename T2>
    inline Vector4<T>::Vector4(const Vector4<T2>& vector4)
        : x(static_cast<T>(vector4.x)),
          y(static_cast<T>(vector4.y)),
          z(static_cast<T>(vector4.z)),
          w(static_cast<T>(vector4.w))
    { }

    template<typename T>
    inline Vector4<T>::~Vector4()
    { }


    // Public
    template<typename T>
    inline Vector4<T>& Vector4<T>::scale(const Vector4<T>& scaleVector)
    {
        return scale(scaleVector.x, scaleVector.y, scaleVector.z, scaleVector.w);
    }


    template<typename T>
    inline Vector4<T>& Vector4<T>::scale(const T& x, const T& y, const T& z, const T& w)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        this->w *= w;

        return *this;
    }

    template<typename T>
    inline Vector4<T>& Vector4<T>::scale(const T& s)
    {
        return scale(s, s, s, s);
    }

    template<typename T>
    inline T Vector4<T>::dot(const Vector4<T>& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    template<typename T>
    inline T Vector4<T>::dot(const Vector4<T>& vec1, const Vector4<T>& vec2)
    {
        return vec1.dot(vec2);
    }

    template<typename T>
    inline double Vector4<T>::lengthSquared() const
    {
        const double xd = static_cast<double>(x);
        const double yd = static_cast<double>(y);
        const double zd = static_cast<double>(z);
        const double wd = static_cast<double>(w);
        return xd*xd + yd*yd + zd*zd + wd*wd;
    }

    template<typename T>
    inline double Vector4<T>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template<typename T>
    inline double Vector4<T>::distance(const Vector4<T>& vec1, const Vector4<T>& vec2)
    {
        return (vec2 - vec1).length();
    }

    template<typename T>
    inline Vector4<T>& Vector4<T>::normalize()
    {
        return *this = unitVector();
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::unitVector() const
    {
        return *this / static_cast<T>(length());
    }

    template<typename T>
    inline bool Vector4<T>::isUnitVector() const
    {
        // LengthSquared returns double.
        // Also sqrt(1) == 1 so we don't need to do that
        return equals<double>(this->lengthSquared(), 1);
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::lerp(const Vector4<T>& vec1, const Vector4<T>& vec2, const T& t)
    {
        return (1 - t) * vec1 + t * vec2;
    }

    template<typename T>
    inline std::string pmath::Vector4<T>::toString() const
    {
        std::ostringstream stream;
        stream << *this;

        return stream.str();
    }

    // Operators
    #pragma region Operators
    // Comparison operators
    template<typename T>
    inline bool Vector4<T>::operator ==(const Vector4<T>& right) const
    {
        return equals<T>(x, right.x) && equals(y, right.y) &&
            equals(z, right.z) && equals(w, right.w);
    }

    template<typename T>
    inline bool Vector4<T>::operator !=(const Vector4<T>& right) const
    {
        return !(*this == right);
    }

    template<typename T>
    inline bool Vector4<T>::operator >(const Vector4<T>& right) const
    {
        return lengthSquared() > right.lengthSquared();
    }

    template<typename T>
    inline bool Vector4<T>::operator <(const Vector4<T>& right) const
    {
        return lengthSquared() < right.lengthSquared();
    }

    template<typename T>
    inline bool Vector4<T>::operator >=(const Vector4<T>& right) const
    {
        return lengthSquared() >= right.lengthSquared();
    }

    template<typename T>
    inline bool Vector4<T>::operator <=(const Vector4<T>& right) const
    {
        return lengthSquared() <= right.lengthSquared();
    }


    // Assignment operators
    template<typename T>
    inline Vector4<T>& Vector4<T>::operator =(const Vector4<T>& right)
    {
        x = right.x;
        y = right.y;
        z = right.z;
        w = right.w;

        return *this;
    }

    template<typename T>
    inline Vector4<T>& Vector4<T>::operator +=(const Vector4<T>& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;

        return *this;
    }

    template<typename T>
    inline Vector4<T>& Vector4<T>::operator -=(const Vector4<T>& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;

        return *this;
    }

    template<typename T>
    inline Vector4<T>& Vector4<T>::operator *=(const T& right)
    {
        x *= right;
        y *= right;
        z *= right;
        w *= right;

        return *this;
    }

    template<typename T>
    inline Vector4<T>& Vector4<T>::operator /=(const T& right)
    {
        x /= right;
        y /= right;
        z /= right;
        w /= right;

        return *this;
    }


    // Arithmetic operators
    template<typename T>
    inline Vector4<T> Vector4<T>::operator +(const Vector4<T>& right) const
    {
        return Vector4<T>(x + right.x, y + right.y, z + right.z, w + right.w);
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::operator -() const
    {
        return Vector4<T>(-x, -y, -z, -w);
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::operator -(const Vector4<T>& right) const
    {
        return Vector4<T>(x - right.x, y - right.y, z - right.z, w - right.w);
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::operator *(const T& right) const
    {
        return Vector4<T>(x * right, y * right, z * right, w * right);
    }

    template<typename T>
    inline Vector4<T> Vector4<T>::operator /(const T& right) const
    {
        return Vector4<T>(x / right, y / right, z / right, w / right);
    }

    template<typename T>
    inline Vector4<T> operator *(const T& left, const Vector4<T>& right)
    {
        return right * left;
    }

    template<typename T>
    inline std::ostream& operator <<(std::ostream& out, const Vector4<T>& right)
    {
        out << "(" << right.x << ", " << right.y << ", " << right.z << ", " << right.w << ")";

        return out;
    }

    // Member access operators
    template<typename T>
    inline T& Vector4<T>::operator [](const unsigned int index)
    {
        assert(index < COMPONENTS);
        return (&x)[index];
    }

    template<typename T>
    inline const T& Vector4<T>::operator [](const unsigned int index) const
    {
        assert(index < COMPONENTS);
        return (&x)[index];
    }
    #pragma endregion
}