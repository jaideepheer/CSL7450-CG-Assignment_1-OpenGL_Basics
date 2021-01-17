#pragma once
#include <GL/freeglut.h>
#include "types.hpp"

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
    return {objX, objY};
}