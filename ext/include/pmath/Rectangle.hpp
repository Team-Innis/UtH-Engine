#pragma once
#ifndef RECTANGLE_PMATH_H
#define RECTANGLE_PMATH_H

#include "Vector2.hpp"

#include <iostream>
#include <string>

namespace pmath
{
    // Basic implementation of an AABB with origin(i.e. position) in the top left
    template<typename T>
    class Rectangle
    {
    public:
        Rectangle();
        Rectangle(const T& x, const T& y, const T& width, const T& height);
        Rectangle(const Vector2<T>& position, const Vector2<T>& size);
        Rectangle(const Rectangle& rectangle);
        template<typename T2>
        Rectangle(const Rectangle<T2>& rectangle);

        T area() const;

        // Returns the position of the center of the rectangle
        Vector2<T> center() const;
        template<typename T2>
        Vector2<T2> center() const;

        T getLeft() const;
        T getRight() const;
        T getBottom() const;
        T getTop() const;

        // Checks intersection with other rectangle
        bool intersects(const Rectangle& other) const;
        // Checks intersection with other rectangle
        // outIntersect is the rectangle of the intersection
        bool intersects(const Rectangle& other, Rectangle& outIntersect) const;

        // Is the point inside the rectangle?
        bool contains(const Vector2<T>& point) const;
        // Does this rectangle contain the other rectangle?
        // Checking this on self should return true
        bool contains(const Rectangle& other) const;

        // Scales the size of the rectangle
        void scale(const T& scale);

        std::string toString() const;

        #pragma region Operators
        // Comparison
        bool operator ==(const Rectangle& right) const;
        bool operator !=(const Rectangle& right) const;

        // Assignment
        Rectangle& operator =(const Rectangle& right);
        #pragma endregion

        Vector2<T> position;
        Vector2<T> size;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Rectangle<T>& right);

    typedef Rectangle<float> Rect;
    typedef Rectangle<float> Rectf;
    typedef Rectangle<double> Rectd;
    typedef Rectangle<int> Recti;
}

#include "inl/Rectangle.inl"
#endif