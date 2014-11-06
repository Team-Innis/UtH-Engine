#include "../Vector3.hpp"
#include "../Util.hpp"

#include <cassert>
#include <cmath>
#include <sstream>

namespace pmath
{
    template<typename T>
    inline Vector3<T>::Vector3()
        : x(T()),
          y(T()),
          z(T())
    { }

    template<typename T>
    inline Vector3<T>::Vector3(const T& x, const T& y, const T& z)
        : x(x),
          y(y),
          z(z)
    { }

    template<typename T>
    inline Vector3<T>::Vector3(const T& value)
        : x(value),
          y(value),
          z(value)
    { }

    template<typename T>
    inline Vector3<T>::Vector3(const Vector2<T>& vector, const T& z)
        : x(vector.x),
          y(vector.y),
          z(z)
    { }

    template<typename T>
    inline Vector3<T>::Vector3(const Vector3<T>& vector3)
        : x(vector3.x),
          y(vector3.y),
          z(vector3.z)
    { }

    template<typename T>
    template<typename T2>
    inline Vector3<T>::Vector3(const Vector3<T2>& vector3)
        : x(static_cast<T>(vector3.x)),
          y(static_cast<T>(vector3.y)),
          z(static_cast<T>(vector3.z))
    { }

    template<typename T>
    inline Vector3<T>::~Vector3()
    { }


    // Public
    template<typename T>
    inline Vector3<T>& Vector3<T>::scale(const Vector3<T>& scaleVector)
    {
        return scale(scaleVector.x, scaleVector.y, scaleVector.z);
    }


    template<typename T>
    inline Vector3<T>& Vector3<T>::scale(const T& x, const T& y, const T& z)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;

        return *this;
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::scale(const T& s)
    {
        return scale(s, s, s);
    }

    template<typename T>
    inline T Vector3<T>::dot(const Vector3<T>& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    template<typename T>
    inline T Vector3<T>::dot(const Vector3<T>& vec1, const Vector3<T>& vec2)
    {
        return vec1.dot(vec2);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::cross(const Vector3<T>& other) const
    {
        return Vector3<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::cross(const Vector3<T>& vec1, const Vector3<T>& vec2)
    {
        return vec1.cross(vec2);
    }

    template<typename T>
    inline double Vector3<T>::lengthSquared() const
    {
        const double xd = static_cast<double>(x);
        const double yd = static_cast<double>(y);
        const double zd = static_cast<double>(z);
        return xd*xd + yd*yd + zd*zd;
    }

    template<typename T>
    inline double Vector3<T>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template<typename T>
    inline double Vector3<T>::distance(const Vector3<T>& vec1, const Vector3<T>& vec2)
    {
        return (vec2 - vec1).length();
    }


    template<typename T>
    inline Vector3<T>& Vector3<T>::normalize()
    {
        return *this = normalized();
    }


    template<typename T>
    inline Vector3<T> Vector3<T>::normalized() const
    {
        return *this / static_cast<T>(length());
    }


    template<typename T>
    inline Vector3<T> Vector3<T>::unitVector() const
    {
        return normalized();
    }

    template<typename T>
    inline bool Vector3<T>::isNormalized() const
    {
        // LengthSquared returns double.
        // Also sqrt(1) == 1 so we don't need to do that
        return equals<double>(this->lengthSquared(), 1);
    }

    template<typename T>
    inline bool Vector3<T>::isUnitVector() const
    {
        return isNormalized();
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::lerp(const Vector3<T>& vec1, const Vector3<T>& vec2, const T& t)
    {
        return (1 - t) * vec1 + t * vec2;
    }

    template<typename T>
    inline std::string pmath::Vector3<T>::toString() const
    {
        std::ostringstream stream;
        stream << *this;

        return stream.str();
    }

    // Operators
    #pragma region Operators
    // Comparison operators
    template<typename T>
    inline bool Vector3<T>::operator ==(const Vector3<T>& right) const
    {
        return equals<T>(x, right.x) && equals<T>(y, right.y) && equals<T>(z, right.z);
    }

    template<typename T>
    inline bool Vector3<T>::operator !=(const Vector3<T>& right) const
    {
        return !(*this == right);
    }

    template<typename T>
    inline bool Vector3<T>::operator >(const Vector3<T>& right) const
    {
        return lengthSquared() > right.lengthSquared();
    }

    template<typename T>
    inline bool Vector3<T>::operator <(const Vector3<T>& right) const
    {
        return lengthSquared() < right.lengthSquared();
    }

    template<typename T>
    inline bool Vector3<T>::operator >=(const Vector3<T>& right) const
    {
        return lengthSquared() >= right.lengthSquared();
    }

    template<typename T>
    inline bool Vector3<T>::operator <=(const Vector3<T>& right) const
    {
        return lengthSquared() <= right.lengthSquared();
    }


    // Assingment operators
    template<typename T>
    inline Vector3<T>& Vector3<T>::operator =(const Vector3<T>& right)
    {
        x = right.x;
        y = right.y;
        z = right.z;

        return *this;
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator +=(const Vector3<T>& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;

        return *this;
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;

        return *this;
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator *=(const T& right)
    {
        x *= right;
        y *= right;
        z *= right;

        return *this;
    }

    template<typename T>
    inline Vector3<T>& Vector3<T>::operator /=(const T& right)
    {
        x /= right;
        y /= right;
        z /= right;

        return *this;
    }


    // Arithmetic operators
    template<typename T>
    inline Vector3<T> Vector3<T>::operator +(const Vector3<T>& right) const
    {
        return Vector3<T>(x + right.x, y + right.y, z + right.z);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator -() const
    {
        return Vector3<T>(-x, -y, -z);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator -(const Vector3<T>& right) const
    {
        return Vector3<T>(x - right.x, y - right.y, z - right.z);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator *(const T& right) const
    {
        return Vector3<T>(x * right, y * right, z * right);
    }

    template<typename T>
    inline Vector3<T> Vector3<T>::operator /(const T& right) const
    {
        return Vector3<T>(x / right, y / right, z / right);
    }

    template<typename T>
    inline Vector3<T> operator *(const T& left, const Vector3<T>& right)
    {
        return right * left;
    }

    template<typename T>
    inline std::ostream& operator <<(std::ostream& out, const Vector3<T>& right)
    {
        out << "(" << right.x << ", " << right.y << ", " << right.z << ")";

        return out;
    }

    // Member access operators
    template<typename T>
    inline T& Vector3<T>::operator [](const unsigned int index)
    {
        assert(index < COMPONENTS);
        return (&x)[index];
    }

    template<typename T>
    inline const T& Vector3<T>::operator [](const unsigned int index) const
    {
        assert(index < COMPONENTS);
        return (&x)[index];
    }
    #pragma endregion
}