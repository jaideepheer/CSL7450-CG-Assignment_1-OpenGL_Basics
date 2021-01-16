#pragma once
#include<iostream>
#include <tuple>
#include<GL/glut.h>

typedef std::pair<int, char**> Main_Args_T; 
typedef std::pair<int, int> IntPair_T;

// Defines a RGBA color
struct Color
{
    float R,G,B,Alpha;
    std::tuple<float,float,float,float> to_tuple()
    {
        return { R, G, B, Alpha };
    }
};

// Defines a range with min/max values
template<typename T>
struct Range
{
    T min;
    T max;
    std::tuple<T, T> to_tuple()
    {
        return { min, max };
    }
};

// Arguments for glOrtho
struct OrthoArgs
{
    Range<float> lr;
    Range<float> bt;
    std::tuple<float,float,float,float> to_tuple()
    {
        return std::tuple_cat(lr.to_tuple(), bt.to_tuple());
    }
};

// Args struct
struct __create_window_args
{
    struct {int argc; char** argv;} main_args;
    Range<int> win_size, win_pos;
    const char* win_title;
};
int create_window(__create_window_args args)
{
    // Init. glut
    auto [argc, argv] = args.main_args;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Init. window
    glutInitWindowSize(args.win_size.min, args.win_size.max);
    glutInitWindowPosition(args.win_pos.min, args.win_pos.max);

    // Create window
    auto win_ID = glutCreateWindow(args.win_title);

    return win_ID;
}

// Args struct
struct __prepare_window_args
{
    OrthoArgs orthoArgs;
    float point_size = 1.0;
    Color drawing_color = {1,0,0,0}, clear_color;
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