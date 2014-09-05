#include "../Rectangle.hpp"

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
    inline bool Rectangle<T>::contains(const Vector2<T>& point) const
    {
        return
            !(getLeft() > point.x ||
            getRight() < point.x ||
            getTop() > point.y ||
            getBottom() < point.y);
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