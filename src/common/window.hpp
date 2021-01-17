#pragma once
#include <GL/freeglut.h>
#include "types.hpp"

// Args struct
struct __create_window_args
{
    struct
    {
        int argc;
        char **argv;
    } main_args;
    Point2<int> win_size, win_pos;
    const char *win_title;
};
int create_window(__create_window_args args)
{
    // Init. glut
    auto [argc, argv] = args.main_args;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Init. window
    glutInitWindowSize(args.win_size.x, args.win_size.y);
    glutInitWindowPosition(args.win_pos.x, args.win_pos.y);

    // Create window
    auto win_ID = glutCreateWindow(args.win_title);

    return win_ID;
}

// Args struct
struct __prepare_window_args
{
    OrthoArgs orthoArgs;
    float point_size = 1.0;
    Color drawing_color = {1, 0, 0, 0}, clear_color;
};
void prepare_window(__prepare_window_args args)
{
    using std::apply;
    // Clear window to clear_color
    apply(glClearColor, args.clear_color.to_tuple());

    // Apply drawing color and point size
    apply(glColor4f, args.drawing_color.to_tuple());
    glPointSize(args.point_size);

    //initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    apply(gluOrtho2D, args.orthoArgs.to_tuple());
}