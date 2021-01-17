// C program to demonstrate
// drawing a circle using
// OpenGL
#include "common.hpp"
#include "DrawTriangle.hpp"

// Prepare input functions
MousePointsHandler<int, 3> pointsHandler;

void display(void)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw triangle
    draw_triangle_bb({
        .point_1 = pointsHandler.points[0],
        .point_2 = pointsHandler.points[1],
        .point_3 = pointsHandler.points[2]
    });
    label_shape_points(pointsHandler.points);
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    // Create window
    auto win_ID = create_window({.main_args = {argc, argv},
                                 .win_size = {500, 500},
                                 .win_pos = {10, 30},
                                 .win_title = "Q2 - Supersampling Triangle"});

    // Init. window
    prepare_window({.orthoArgs = {.lr = {10, 400}, .bt = {10, 400}}});

    pointsHandler.points[0] = {126, 225};
    pointsHandler.points[1] = {177, 129};
    pointsHandler.points[2] = {288, 309};
    MouseEventBus::register_mouse_handler(&pointsHandler);

    glutDisplayFunc(display);
    glutMouseFunc(MouseEventBus::glut_callback_mouse_func);
    glutMotionFunc(MouseEventBus::glut_callback_motion_func);
    glutPostRedisplay();
    glutMainLoop();
    std::cout<<"Hello\n";
}