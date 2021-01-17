#pragma once
#include "types.hpp"
#include "math.hpp"
#include <optional>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>

class MouseHandler
{
public:
    virtual void glut_callback_mouse_func(int button, int mouse_state, int x, int y){};
    virtual void glut_callback_motion_func(int x, int y){};
};

template <typename T, size_t N>
class MousePointsHandler : public MouseHandler
{
    int grab_button;
    struct
    {
        std::optional<size_t> selected_idx;
    } state;

public:
    std::array<Point2<T>, N> points;
    MousePointsHandler(size_t mouse_grab_button = GLUT_LEFT_BUTTON) : grab_button(mouse_grab_button) {}
    struct
    {
        // The distance at which a mouse click will grab the nearest point.
        double grab_distance = 25.0;
    } options;
    void glut_callback_motion_func(int x, int y)
    {
        // Mouse draged, update selected point
        if (state.selected_idx)
        {
            auto& point = points[*(state.selected_idx)];
            point = window_to_world(Point2<int>{x,y});
        }
    }
    void glut_callback_mouse_func(int button, int mouse_state, int x, int y)
    {
        // Only process grab button events
        if (button == grab_button)
        {
            Point2<int> mouse_pos = window_to_world(Point2<int>{x, y});
            if (mouse_state == GLUT_DOWN)
            {
                // mouse down, select clossest eligible point
                double dist = INFINITY;
                for (size_t i = 0; i < N; i++)
                {
                    auto p = points[i];
                    auto curDist = (p - mouse_pos).magnitude();
                    if (curDist < dist && curDist < options.grab_distance)
                    {
                        // select current point
                        this->state.selected_idx = i;
                    }
                }
            }
            else if (mouse_state == GLUT_UP)
            {
                // mouse up, unselect point
                this->state.selected_idx = {};
            }
        }
    }
};

class MouseEventBus
{
public:
    static std::vector<MouseHandler*> handlers;
    static void register_mouse_handler(MouseHandler *handler)
    {
        handlers.push_back(handler);
    }
    static void glut_callback_mouse_func(int button, int mouse_state, int x, int y)
    {
        // Mouse event recieved, pass it to all handlers
        for (auto &h : handlers)
        {
            h->glut_callback_mouse_func(button, mouse_state, x, y);
        }
        glutPostRedisplay();
    }
    static void glut_callback_motion_func(int x, int y)
    {
        // Motion event, pass it to all handlers
        for (auto &h : handlers)
        {
            h->glut_callback_motion_func(x, y);
        }
        glutPostRedisplay();
    }
};

std::vector<MouseHandler*> MouseEventBus::handlers = {};