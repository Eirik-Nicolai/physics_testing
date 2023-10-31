#include "olc_balls.hpp"

void ball::update(float dt)
{
    vel += acc * dt;
    pos += vel * dt;
}

void ball::add_force(vec2 force)
{
    vel += force;
}

void balls::add_item(float x, float y, float r)
{
    bodies.emplace_back(std::make_unique<ball>(x, y, r));
}

void balls::update(float dt)
{
    do_naive_collision();
    update_positions(dt);
}

void balls::update_positions(float dt)
{
    for(auto &b : bodies)
    {
        b->update(dt);
    }
}

void balls::do_naive_collision()
{
    for(auto &b1 : bodies)
        for(auto &b2 : bodies)
        {
            if(b1 == b2)
                continue;
            vec2 dist_vec = b2->pos - b1->pos;
            float dist = sqrt((dist_vec.x*dist_vec.x)+(dist_vec.y*dist_vec.y));
            if(dist <= (b1->radius+b2->radius))
            {
                float overlap = 0.5 * (dist - b1->radius - b2->radius);

                b1->pos.x -= overlap * (b1->pos.x - b2->pos.x)/dist;
                b1->pos.y -= overlap * (b1->pos.y - b2->pos.y)/dist;
                b2->pos.x += overlap * (b1->pos.x - b2->pos.x)/dist;
                b2->pos.y += overlap * (b1->pos.y - b2->pos.y)/dist;
            }
        }
}
