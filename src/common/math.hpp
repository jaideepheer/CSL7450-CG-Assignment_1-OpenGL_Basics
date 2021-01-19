#pragma once
#include <GL/freeglut.h>
#include "types.hpp"
#include <math.h>

// Returns the angle b/w two points
template<typename T>
double point_angle(Point2<T> p1, Point2<T> p2)
{
    auto dot = p1.x*p2.x + p1.y*p2.y;      // dot product between [x1, y1] and [x2, y2]
    auto det = p1.x*p2.y - p1.y*p2.x;      // determinant
    return std::atan2(-det, -dot) + M_PI;  // atan2(y, x) or atan2(sin, cos)
}

template <typename T>
Point2<T> window_to_world(Point2<T> screen_point)
{
    // https://stackoverflow.com/questions/1834648/world-coordinate-issues-with-gluunproject?rq=1
    GLint view[4];  //viewport dimensions+pos
    GLdouble p[16]; //projection matrix
    GLdouble m[16]; //modelview matrix
    // get data
    glGetDoublev(GL_MODELVIEW_MATRIX, m);
    glGetDoublev(GL_PROJECTION_MATRIX, p);
    glGetIntegerv(GL_VIEWPORT, view);
    // vars to recieve data in
    double objX, objY, objZ;
    // unproject
    gluUnProject(screen_point.x, view[3]-screen_point.y, 0.5, m, p, view, &objX, &objY, &objZ);
    return {(T)round(objX), (T)round(objY)};
}