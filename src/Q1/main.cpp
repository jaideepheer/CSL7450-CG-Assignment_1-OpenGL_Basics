// C program to demonstrate
// drawing a circle using
// OpenGL
#include "common.hpp"
#include<math.h>

#define pi 3.142857


void display (void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    float x, y, i;
     
    // iterate y up to 2*pi, i.e., 360 degree
    // with small increment in angle as
    // glVertex2i just draws a point on specified co-ordinate
    for ( i = 0; i < (2 * pi); i += 0.001)
    {
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        x = 200 * cos(i);
        y = 200 * sin(i);
         
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

int main (int argc, char** argv)
{
    // Create window
    auto win_ID = create_window({
        .main_args={argc,argv}, 
        .win_size={500, 500},
        .win_pos={10,30},
        .win_title="Q1 - Midpoint Line Algorithm"
        });
    
    // Init. window
    prepare_window({
        .orthoArgs= {.lr={10,400}, .bt={10,400}}
        });
     
    glutDisplayFunc(display);
    glutMainLoop();
}