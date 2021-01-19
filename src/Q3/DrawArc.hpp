#pragma once
#include "types.hpp"
#include "common.hpp"
#include <cmath>
#include <math.h>
#include <GL/freeglut.h>

// Defines circle octants in counter clockwise order.
enum CircleOctant
{
    TopRight_X = 0,
    TopRight_Y,
    TopLeft_Y,
    TopLeft_X,
    BottomLeft_X,
    BottomLeft_Y,
    BottomRight_Y,
    BottomRight_X
};
/**
 * Recieves an angle in radians and returns the octant for that angle.
 */
CircleOctant getAngleOctant(double angle)
{
    CircleOctant oc = TopRight_X;
    angle -= M_PI_4;
    while (angle > 0)
    {
        angle -= M_PI_4;
        oc = static_cast<CircleOctant>(static_cast<int>(oc) + 1);
    }
    return oc;
}

// Args struct
struct __draw_octant_partial_args
{
    const Point2<int> &centre, &end_point;
    Point2<int> draw_start;
    const int radius;
    const int iter_delta, other_delta;
    const bool is_iteraxis_X;
};
/**
 * This function draws an octant in counter-clockwise direction until the octant ends or it hits the end_point.
 * 
 * This uses the concept of an iterating axis and an other axis,
 *      Iterating axis is one that changes with every iteration.
 *      Other axis can remain same for multiple iterations.
 * 
 * While drawing there are 2 cases,
 *      1) Iterating axis is moving towards one of X/Y axis. (eg. x=x-1 in 1st quadrant)
 *      2) Iterating axis is moving away from one of X/Y axis. (eg. x=x-1 in 2nd quadrant)
 * In both the above cases, the behaviour of both axis is opposite.
 * In general the one of the axis tries to push the pointer outwards while the other axis pushes pointer inward.
 * This behaviour flips for both the axis depending on the above cases.
 * 
 * Each octant is drawn by the same function using,
 *  P_k = (iteraxis_k + iterdelta_k)^2 + (otheraxis_k + (other_delta_k / 2))^2 - radius^2
 * By using the above formula for two cases,
 *      case 1: P_k <= 0,
 *                  Here only the iter axis changes and the other axis remains same.
 *                  Thus, iteraxis_{k+1} = iteraxis_k + iterdelta
 *                        otheraxis_{k+1} = other_axis_k
 *              Therefore, P_{k+1} = P_k + iterdelta^2 + 2*iterdelta*iteraxis_{k+1}
 *      case 2: P_k > 0,
 *                  Here both the iter axis and the other axis change.
 *                  Thus, iteraxis_{k+1} = iteraxis_k + iterdelta
 *                        otheraxis_{k+1} = other_axis_k + otherdelta
 *              Therefore, P_{k+1} = P_k + iterdelta^2 + 2*iterdelta*iteraxis_{k+1} + otherdelta^2 + 2*otherdelta*otheraxis_{k+1}
 * The draw octant function runs until it draws the edge of the octant.
 */
Point2<int> draw_octant_partial(__draw_octant_partial_args args)
{
    auto &[centre, end_point, draw_start, radius, iter_delta, other_delta, is_iteraxis_X] = args;
    // Set axis proxy
    auto &iter_porxy = is_iteraxis_X ? draw_start.x : draw_start.y;
    auto &other_porxy = is_iteraxis_X ? draw_start.y : draw_start.x;
    // Relocate drawing centre at origin
    draw_start -= centre;
    // Calc. constants
    const auto end_line = end_point - centre;
    const auto start_octant_hash = draw_start.getOctantHash();
    const bool is_iter_moving_to_axis = iter_porxy * iter_delta < 0;
    // Calc. P
    int P = iter_porxy + iter_delta;
    // other_delta*other_delta/4 will always be +ve and since other_delta will be small (=1/-1) we can ignore this value
    P = P * P - radius * radius;
    P += other_porxy * other_porxy + other_porxy * other_delta;
    // Iterate
    glBegin(GL_POINTS);
    while (draw_start.getOctantHash() == start_octant_hash)
    {
        // We do not calc. draw_start-centre since we have already done that before loop
        if (draw_start.cross_product_z(end_line) == 0)
        {
            // collided with centre<->end_point line
            break;
        }
        draw_start += centre;
        glVertex2i(draw_start.x, draw_start.y);
        draw_start -= centre;
        // next point
        iter_porxy += iter_delta;
        P += 1 + 2 * iter_delta * iter_porxy;
        if ((P > 0) ^ is_iter_moving_to_axis)
        {
            // Moving out of circle range, fix movement
            other_porxy += other_delta;
            P += 1 + 2 * other_delta * other_porxy;
        }
    }
    glEnd();
    glFlush();
    // Return final point
    return draw_start + centre;
}

// Args struct
struct __draw_arc_args
{
    Point2<int> centre;
    int radius;
    // Rsadian angles measured counter-clockwise from x-axis.
    double angle_start, angle_end;
};
/**
 * Recives the centre point, the radius and two angles to draw a circle arc between the angles.
 * This algorithm draws by breaking down the arc into octants.
 * This always draws in the counter-clockwise direction.
 * This uses a modified the midpoint circle drawing algorithm.
 * 
 * The arc is drawn by dividing it into octants.
 */
void draw_arc(__draw_arc_args args)
{
    auto &[centre, radius, start_angle, end_angle] = args;
    // Resolve start/end points
    Point2<int> start{
        .x = (int)(radius * std::cos(start_angle)),
        .y = (int)(radius * std::sin(start_angle))};
    Point2<int> end{
        .x = (int)(radius * std::cos(end_angle)),
        .y = (int)(radius * std::sin(end_angle))};
    // Relocate relative to centre
    start += centre;
    end += centre;
    // label arc edges
    label_shape_points(
        std::array{
            start.to_string() + ", deg=" + std::to_string(start_angle),
            end.to_string() + ", deg=" + std::to_string(end_angle)},
        std::array{start, end});
    // Now we identify each octant and draw it
    // Define axis and their deltas in counter-clockwise direction for each octant
    const auto octant_is_iteraxis_X_mapping = std::array{false, true, true, false, false, true, true, false};
    const auto iter_deltas_cc = std::array{+1, -1, -1, -1, -1, +1, +1, +1};
    const auto other_deltas_cc = std::array{-1, +1, -1, -1, +1, -1, +1, +1};
    // get start and end octants
    auto start_oct = static_cast<int>(getAngleOctant(start_angle)), end_oct = static_cast<int>(getAngleOctant(end_angle));
    // draw octants
    for (auto i = start_oct; i <= end_oct; ++i)
    {
        start = draw_octant_partial({.centre = centre,
                                     .end_point = end,
                                     .draw_start = start,
                                     .radius = radius,
                                     .iter_delta = iter_deltas_cc[i],
                                     .other_delta = other_deltas_cc[i],
                                     .is_iteraxis_X = octant_is_iteraxis_X_mapping[i]});
    }
}