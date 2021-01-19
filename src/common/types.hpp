#pragma once
#include <tuple>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>

// Get sign
// https://stackoverflow.com/a/4609795/10027894
template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

// Defines a angular direction
enum AngularDirection
{
    CLOCKWISE, COUNTER_CLOCKWISE
};

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
    /**
     * Returns a hash for the octant that this point lies in w.r.t the origin.
     * This is a 4bit hash where each bit defines which side of the 4 octant axis this point lies in.
     */
    static short getOctantHash(T x, T y)
    {
        return ((x<=0)<<3) | ((y<=0)<<2) | ((y<=x)<<1) | ((-y<=x)<<0);
    }
    short getOctantHash()
    {
        return Point2<T>::getOctantHash(x, y);
    }
    // Returns the magnitude.
    double magnitude()
    {
        return sqrt(x * x + y * y);
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
        return *this / this->magnitude();
    }
    // To string
    std::string to_string()
    {
        std::ostringstream s;
        s << "(" << x << "," << y << ")";
        return s.str();
    }
    // Cast to new type
    template <typename Q>
    Point2<Q> cast()
    {
        return {Q(x), Q(y)};
    }
    // Products
    // Returns the z-axis value of the cross product of this point with the other.
    T cross_product_z(const Point2<T> &other)
    {
        return x * other.y - y * other.x;
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
    // To string
    std::string to_string()
    {
        std::ostringstream s;
        s << "(" << min << "," << max << ")";
        return s.str();
    }
};

// Defines the 2D bounding box of the given N points.
template <typename T, size_t N>
struct BoundingBox2
{
    Range<T> x_range{T(0), T(0)}, y_range{T(0), T(0)};
    BoundingBox2(std::array<Point2<T>, N> points)
    {
        x_range = {points[0].x, points[0].x};
        y_range = {points[0].y, points[0].y};
        for(const auto& p:points)
        {
            x_range.min = std::min(p.x, x_range.min);
            x_range.max = std::max(p.x, x_range.max);
            y_range.min = std::min(p.y, y_range.min);
            y_range.max = std::max(p.y, y_range.max);
        }
    }
    // Returns the vertices of this box in order,
    // bottom-left, top-left, top-right, bottom-right
    std::tuple<Point2<T>, Point2<T>, Point2<T>, Point2<T>> vertices()
    {
        return {
            Point2<T>{x_range.min, y_range.min},
            Point2<T>{x_range.min, y_range.max},
            Point2<T>{x_range.max, y_range.max},
            Point2<T>{x_range.max, y_range.min},
        };
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
