#include "../Trigonometry.hpp"
#include "../Constants.hpp"

namespace pmath
{
    template<typename T>
    inline T degreesToRadians(const T& degrees)
    {
        return T(degrees / 180 * pi);
    }

    template<typename T>
    inline T radiansToDegrees(const T& radians)
    {
        return T(radians * 180 / pi);
    }

    template<typename T>
    inline T cos(const T& angle)
    {
        return std::cos(degreesToRadians<T>(angle));
    }

    template<typename T>
    inline T acos(const T& value)
    {
        return radiansToDegrees<T>(std::acos(value));
    }

    template<typename T>
    inline T sin(const T& angle)
    {
        return std::sin(degreesToRadians<T>(angle));
    }

    template<typename T>
    inline T asin(const T& value)
    {
        return radiansToDegrees<T>(std::asin(value));
    }

    template<typename T>
    inline T tan(const T& angle)
    {
        return std::tan(degreesToRadians<T>(angle));
    }

    template<typename T>
    inline T atan(const T& value)
    {
        return radiansToDegrees<T>(std::atan(value));
    }

    template<typename T>
    inline T atan2(const T& y, const T& x)
    {
        return radiansToDegrees(std::atan2(y, x));
    }
}