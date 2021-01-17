#pragma once
#include "types.hpp"
#include "common.hpp"

// Args struct
template <typename T>
struct __is_points_same_side_args
{
    struct
    {
        Point2<T> line_a, line_b;
    } line;
    Point2<T> point_1, point_2;
};
/**
 * Given 2 points for a line and 2 ohter points x,y this functions returns true if x and y lie on the same side of the line.
 */
template <typename T>
bool is_points_on_same_side(__is_points_same_side_args<T> args)
{
    auto &[line, x, y] = args;
    auto &[a, b] = line;
    auto t = b - a;
    auto xz = t.cross_product_z(b - x);
    auto yz = t.cross_product_z(b - y);
    return sign(xz) * sign(yz) > 0;
}

// Args struct
template <typename T>
struct __is_point_in_triangle_args
{
    struct
    {
        Point2<T> a, b, c;
    } triangle;
    Point2<T> check_point;
};
/**
 * Given 2 points for a line and 2 ohter points x,y this functions returns true if x and y lie on the same side of the line.
 */
template <typename T>
bool is_point_in_triangle(__is_point_in_triangle_args<T> args)
{
    auto &[tri, p] = args;
    auto &[a, b, c] = tri;
    return is_points_on_same_side<T>({.line = {b, c}, p, a}) && is_points_on_same_side<T>({.line = {a, c}, p, b}) && is_points_on_same_side<T>({.line = {b, a}, p, c});
}

// Args struct
struct __draw_tri_args
{
    Point2<int> point_1, point_2, point_3;
    Color fill_color{0, 1, 0, 1};
    bool draw_bb = true;
};
/**
 * Recives three points and draws a triangle joinning the points.
 * This method uses the bounding box of the triangle to iterate through each point in the bb.
 */
void draw_triangle_bb(__draw_tri_args args)
{
    // expand args
    auto &[a, b, c, color, draw_bb] = args;
    // calc. the bounding box
    const BoundingBox2 bb(std::array<Point2<int>, 3>{a, b, c});
    if (draw_bb)
    {
        // draw bb outline
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glRectd(bb.x_range.min, bb.y_range.min, bb.x_range.max, bb.y_range.max);
    }
    // Iterate all points in bb
    glBegin(GL_POINTS);
    for (int x = bb.x_range.min; x <= bb.x_range.max; ++x)
    {
        for (int y = bb.y_range.min; y <= bb.y_range.max; ++y)
        {
            // check if point in triangle
            if (is_point_in_triangle<int>({.triangle = {a, b, c}, {x, y}}))
            {
                glVertex2i(x, y);
            }
        }
    }
    glEnd();
    glFlush();
}