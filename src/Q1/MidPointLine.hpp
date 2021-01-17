#pragma once
#include "common.hpp"

/**
 * Recives two points and draws a line joinning the points using the mid-point line algorithm.
 */
// Args struct
struct __draw_line_args
{
    Point2<int> point_1, point_2;
};
void draw_line(__draw_line_args args)
{
    // expand args
    auto &[a, b] = args;
    // Calc. abs(dy) and abs(dx) in dp and sign(dx) and sign(dy) in dt
    auto dp = (b - a);
    auto dt = dp.sign();
    dp = dp.abs();
    // Check which value changes faster x or y and set the coresponding axis to draw along
    const auto isXMainAxis = (dp.x > dp.y);
    auto &iterate_axis = isXMainAxis ? a.x : a.y;
    auto &iterate_target = isXMainAxis ? b.x : b.y;
    auto &other_axis = isXMainAxis ? a.y : a.x;
    // Swap if drawing along y axis
    if (!isXMainAxis)
    {
        // swap loop iteration variables to draw along y axis
        std::swap(dp.x, dp.y);
        std::swap(dt.x, dt.y);
    }
    // Use normal Mid-Point Line Algo. from here.
    // Calc. init. value of decision var.
    int d = dp.y - (dp.x / 2);
    // Inital point is 'a'
    glBegin(GL_POINTS);
    glVertex2i(a.x, a.y);
    // Draw Loop
    while (iterate_axis < iterate_target)
    {
        iterate_axis += dt.x;
        if (d < 0)
        {
            // EAST
            d += dp.y;
        }
        else
        {
            // NORTH-EAST
            d += dp.y - dp.x;
            other_axis += dt.y;
        }
        glVertex2i(a.x, a.y);
    }
    glEnd();
    glFlush();
}