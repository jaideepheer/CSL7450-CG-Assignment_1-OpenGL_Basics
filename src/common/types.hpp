#pragma once
#include <tuple>
#include <string>
#include <sstream>
#include <math.h>

// Get sign
// https://stackoverflow.com/a/4609795/10027894
template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

// Defines a RGBA color
struct Color
{
    float R, G, B, Alpha;
    std::tuple<float, float, float, float> to_tuple()
    {
        return {R, G, B, Alpha};
    }
};

// Defines a 2D point
template <typename T>
struct Point2
{
    T x;
    T y;
    // Returns the magnitude.
    T magnitude()
    {
        return sqrt(x*x + y*y);
    }
    std::tuple<T, T> to_tuple()
    {
        return {x, y};
    }
    // Returns new point with absolute values.
    Point2<T> abs()
    {
        using std::abs;
        return {abs(x), abs(y)};
    }
    // Returns new point with sign values.
    Point2<T> sign()
    {
        using ::sign;
        return {sign(x), sign(y)};
    }
    // Returns new point with normalised values.
    Point2<T> norm()
    {
        return *this/this->magnitude();
    }
    // To string
    std::string to_string()
    {
        std::ostringstream s;
        s << "(" << x << "," << y << ")";
        return s.str();
    }
    // Cast to new type
    template<typename Q>
    Point2<Q> cast()
    {
        return {Q(x), Q(y)};
    }
    // Operators
    // https://en.cppreference.com/w/cpp/language/operators
    Point2<T> &operator/=(const T &rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }
    friend Point2<T> operator/(Point2<T> lhs, const T &rhs)
    {
        lhs /= rhs;
        return lhs;
    }
    Point2<T> &operator*=(const T &rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    friend Point2<T> operator*(Point2<T> lhs, const T &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    Point2<T> &operator+=(const Point2<T> &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    friend Point2<T> operator+(Point2<T> lhs, const Point2<T> &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    Point2<T> &operator-=(const Point2<T> &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    friend Point2<T> operator-(Point2<T> lhs, const Point2<T> &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};

// Defines a range with min/max values
template <typename T>
struct Range
{
    T min;
    T max;
    Range(T min, T max) : min(min), max(max)
    {
        if (min > max)
        {
            std::swap(this->min, this->max);
        }
    }
    std::tuple<T, T> to_tuple()
    {
        return {min, max};
    }
};

// Arguments for glOrtho
struct OrthoArgs
{
    Range<float> lr;
    Range<float> bt;
    std::tuple<float, float, float, float> to_tuple()
    {
        return std::tuple_cat(lr.to_tuple(), bt.to_tuple());
    }
};
