// C program to demonstrate
// drawing a circle using
// OpenGL
#include "common.hpp"
#include "DrawArc.hpp"
#include "RadialMousePointHandler.hpp"

// Prepare input functions
RadialMousePointHandler<int, 3> radialHandler;

void display(void)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    // calc. point angles
    auto start_vec = radialHandler.points[1] - radialHandler.points[0];
    auto end_vec = radialHandler.points[2] - radialHandler.points[0];
    int radius = std::round(start_vec.magnitude());
    // Draw circle
    draw_arc({.centre = radialHandler.points[0],
              .radius = radius,
              // 135 degree = 2.35619
              .angle_start = std::atan2(-start_vec.y, -start_vec.x) + M_PI,
              // 215 degree = 3.75246
              .angle_end = std::atan2(-end_vec.y, -end_vec.x) + M_PI});
    // label_shape_points(pointsHandler.points);
    label_point(radialHandler.points[0].to_string() + ", r="+std::to_string(radius), radialHandler.points[0]);
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    // Create window
    auto win_ID = create_window({.main_args = {argc, argv},
                                 .win_size = {500, 500},
                                 .win_pos = {10, 30},
                                 .win_title = "Q3 - Draw Arc"});

    // Init. window
    prepare_window({.orthoArgs = {.lr = {10, 400}, .bt = {10, 400}}});

    radialHandler.points[0] = {220, 225}; // Centre point
    radialHandler.points[1] = {149, 296}; // Radius controllers
    radialHandler.points[2] = {138, 168}; 
    MouseEventBus::register_mouse_handler(&radialHandler);

    glutDisplayFunc(display);
    glutMouseFunc(MouseEventBus::glut_callback_mouse_func);
    glutMotionFunc(MouseEventBus::glut_callback_motion_func);
    glutPostRedisplay();
    glutMainLoop();
}