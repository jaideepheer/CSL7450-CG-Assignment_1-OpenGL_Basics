#pragma once
#include "common.hpp"
#include <math.h>

template <typename T, size_t N>
class RadialMousePointHandler : public MousePointsHandler<T, N>
{
public:
    RadialMousePointHandler(Point2<T> anchor = {0, 0})
    {
        this->points[0] = anchor;
    }
    void glut_callback_motion_func(int x, int y)
    {
        // Mouse draged, update selected point
        if (this->state.selected_idx)
        {
            auto &point = this->points[*(this->state.selected_idx)];
            auto mouse_loc = window_to_world(Point2<int>{x, y});
            auto anchor_delta = mouse_loc - this->points[0];
            if (this->state.selected_idx == 0)
            {
                // centre moved, relocate all points
                for (auto i = 0; i < N; i++)
                    this->points[i] += anchor_delta;
            }
            else
            {
                // radial point moved
                point = mouse_loc;
                // rescale all points
                auto new_mag = (point - this->points[0]).magnitude();
                for (auto i = T(1); i < N; ++i)
                {
                    if (i == this->state.selected_idx)
                        continue;
                    auto &p = this->points[i];
                    p -= this->points[0];
                    auto mg = p.magnitude();
                    p.x = (T)std::round((double)p.x * new_mag / mg);
                    p.y = (T)std::round((double)p.y * new_mag / mg);
                    p += this->points[0];
                }
            }
        }
    }
};