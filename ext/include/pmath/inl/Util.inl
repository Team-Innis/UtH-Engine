#include "../Util.hpp"

#include <cmath>

namespace pmath
{
    template<typename T>
#if _MSC_VER > 1600 || !defined(_MSC_VER)
    inline bool equals(const T a, const T b, const T tolerance)
#elif MSC_VER <= 1600
    inline bool equals(const T a, const T b, const T tolerance = T(0.001))
#endif
    {
        return std::abs(a - b) <= tolerance;
    }

    template<typename T>
    inline T max(const T& a, const T& b)
    {
        if (a > b)
            return a;

        return b;
    }

    template<typename T>
    inline T min(const T& a, const T& b)
    {
        if (a < b)
            return a;

        return b;
    }

    template<typename T>
    inline T clamp(const T& value, const T& min, const T& max)
    {
        if (value > max)
            return max;
        else if (value < min)
            return min;

        return value;
    }

    inline double lerp(const double a, const double b, const double t)
    {
        return (1 - t) * a + t * b;
    }
}
