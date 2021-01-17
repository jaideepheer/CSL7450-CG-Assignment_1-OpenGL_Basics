#pragma once
#include <string>
#include <GL/freeglut.h>
#include <numeric>
#include "types.hpp"

template <typename T>
void put_text(Point2<T> point, std::string text, void *font = GLUT_BITMAP_TIMES_ROMAN_10, T font_height = 5)
{
    const auto length = glutBitmapLength(font, (const unsigned char *)text.c_str());
    glRasterPos2i(point.x - (length / 2), point.y - (font_height / 2));
    glutBitmapString(font, (const unsigned char *)text.c_str());
    glFlush();
}

template <typename T>
void label_point(Point2<T> point, Point2<T> delta = {0, 0}, void *font = GLUT_BITMAP_TIMES_ROMAN_10)
{
    put_text(point + delta, point.to_string(), font);
}

/**
 * Takes multiple points as input and tries to label them such that the labels do not overlap with shape.
 */
template <typename T, size_t N>
void label_shape_points(std::array<Point2<T>, N> points, T label_dist = 10, void *font = GLUT_BITMAP_TIMES_ROMAN_10)
{
    const Point2<T> sum = std::accumulate(points.begin(), points.end(), Point2<T>{T(0), T(0)});
    for (Point2<T> &p : points)
    {
        auto delta = ((p * N - sum).template cast<double>().norm() * label_dist).template cast<int>();
        label_point(p, delta);
    }
}