#ifndef OLC_BALLS_H_
#define OLC_BALLS_H_

#include "common/common.hpp"
#include <math.h>

struct ball : public physics_body
{
    vec2 vel;
    vec2 acc;

    void add_force(vec2) override;
    void update(float) override;

    ball(float x, float y, float r) : physics_body(x, y, r)
    {
        vel = vec2{0.0f, 0.0f};
        acc = vel;
    }
};

struct balls : public physics_solver
{
    void add_item(float x, float y, float radius) override;
    void update(float) override;

    void update_positions(float);
    void do_naive_collision();

    balls() : physics_solver(){}
};

#endif // OLC_BALLS_H_
