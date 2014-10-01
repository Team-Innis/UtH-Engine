#include "../Rectangle.hpp"
#include <sstream>

namespace pmath
{
    template<typename T>
    inline Rectangle<T>::Rectangle()
        : position(0, 0),
          size(0, 0)
    { }

    template<typename T>
    inline Rectangle<T>::Rectangle(const T& x, const T& y, const T& width, const T& height)
        : position(x, y),
          size(width, height)
    { }

    template<typename T>
    inline Rectangle<T>::Rectangle(const Vector2<T>& position, const Vector2<T>& size)
        : position(position),
          size(size)
    { }

    template<typename T>
    inline Rectangle<T>::Rectangle(const Rectangle& rectangle)
        : position(rectangle.position),
          size(rectangle.size)
    { }

    template<typename T>
    template<typename T2>
    inline Rectangle<T>::Rectangle(const Rectangle<T2>& rectangle)
        : position(rectangle.position),
          size(rectangle.size)
    { }


    // Public

    template<typename T>
    inline T Rectangle<T>::area() const
    {
        return size.x * size.y;
    }


    template<typename T>
    inline Vector2<T> Rectangle<T>::center() const
    {
        return position + size / 2;
    }


    template<typename T>
    template<typename T2>
    inline Vector2<T2> Rectangle<T>::center() const
    {
        return Vector2<T2>(position) + Vector2<T2>(size) / T2(2);
    }

    template<typename T>
    inline T Rectangle<T>::getLeft() const
    {
        return position.x;
    }

    template<typename T>
    inline T Rectangle<T>::getRight() const
    {
        return getLeft() + size.x;
    }

    template<typename T>
    inline T Rectangle<T>::getBottom() const
    {
        return getTop() + size.y;
    }

    template<typename T>
    inline T Rectangle<T>::getTop() const
    {
        return position.y;
    }

    template<typename T>
    inline bool Rectangle<T>::intersects(const Rectangle& other) const
    {
        return
            !(getLeft() > other.getRight() ||
            getRight() < other.getLeft() ||
            getTop() > other.getBottom() ||
            getBottom() < other.getTop());
    }

    template<typename T>
    inline bool Rectangle<T>::intersects(const Rectangle& other, Rectangle& outIntersect) const
    {
        if (!intersects(other))
            return false;

        // We have intersection
        T x = max(position.x, other.position.x);
        T right = min(getRight(), other.getRight());
        T y = max(position.y, other.position.y);
        T bottom = min(getBottom(), other.getBottom());
        if (right >= x && bottom >= y)
            outIntersect = Rectangle(x, y, right - x, bottom - y);

        return true;
    }

    template<typename T>
    inline bool Rectangle<T>::contains(const Vector2<T>& point) const
    {
        return
            !(getLeft() > point.x ||
            getRight() < point.x ||
            getTop() > point.y ||
            getBottom() < point.y);
    }

    template<typename T>
    bool Rectangle<T>::contains(const Rectangle& other) const
    {
        return (getLeft() <= other.getLeft() &&
            getRight() >= other.getRight() &&
            getTop() <= other.getTop() &&
            getBottom() >= other.getBottom());
    }


    template<typename T>
    void Rectangle<T>::scale(const T& s)
    {
        size.scale(s);
    }

    template<typename T>
    inline std::string Rectangle<T>::toString() const
    {
        std::ostringstream stream;
        stream << *this;

        return stream.str();
    }

    // Operators
    #pragma region Operators
    // Comparison
    template<typename T>
    inline bool Rectangle<T>::operator ==(const Rectangle<T>& right) const
    {
        return position == right.position && size == right.size;
    }

    template<typename T>
    inline bool Rectangle<T>::operator !=(const Rectangle<T>& right) const
    {
        return !(*this == right);
    }

    // Assignment
    template<typename T>
    inline Rectangle<T>& Rectangle<T>::operator =(const Rectangle<T>& right)
    {
        position = right.position;
        size = right.size;

        return *this;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& out, const Rectangle<T>& right)
    {
        out << "Rect(" << "x: " << right.position.x << ", y: " << right.position.y
            << ", width: " << right.size.x << ", height: " << right.size.y << ")";

        return out;
    }
    #pragma endregion
}