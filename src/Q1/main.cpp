// C program to demonstrate
// drawing a circle using
// OpenGL
#include "common.hpp"
#include "MidPointLine.hpp"
#include "input.hpp"

// Prepare input functions
MousePointsHandler<int, 2> pointsHandler;

void display(void)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw line
    draw_line({.point_1 = pointsHandler.points[0],
               .point_2 = pointsHandler.points[1]});
    label_shape_points(pointsHandler.points);
    glFlush();
    glutSwapBuffers();
}

void onReshape(int w, int h)
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    // Create window
    auto win_ID = create_window({.main_args = {argc, argv},
                                 .win_size = {500, 500},
                                 .win_pos = {10, 30},
                                 .win_title = "Q1 - Midpoint Line Algorithm"});

    // Init. window
    prepare_window({.orthoArgs = {.lr = {10, 400}, .bt = {10, 400}}});

    pointsHandler.points[0].x = 100;
    pointsHandler.points[0].y = 100;
    pointsHandler.points[1].x = 300;
    pointsHandler.points[1].y = 300;
    MouseEventBus::register_mouse_handler(&pointsHandler);

    glutDisplayFunc(display);
    glutMouseFunc(MouseEventBus::glut_callback_mouse_func);
    glutMotionFunc(MouseEventBus::glut_callback_motion_func);
    glutPostRedisplay();
    glutMainLoop();
}