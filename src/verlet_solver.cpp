#include "verlet_solver.hpp"
#include <math.h>

#include <iostream>

void video_verlet_object::update(float dt)
{
    vec2 vel = pos - pos_old;

    pos_old = pos;

    pos += vel + acc * (dt*dt);

    acc = vec2{0.0,0.0};
}


void verlet_container::add_item(float x, float y, float r)
{
    bodies.emplace_back(new video_verlet_object(x, y, r));
}

void verlet_container::update(float dt)
{
    int substep = 10;
    float subdt = dt/substep;
    for(int i = 0; i < substep; ++i)
    {
        //apply_gravitiy();
        //apply_constraint();
        //do_simple_collisions();
        update_positions(subdt);
    }

}

void verlet_container::update_positions(float dt)
{
    for(auto& bod : bodies)
    {
        bod->update(dt);
    }
}

void verlet_container::apply_gravitiy()
{
    for(auto& bod : bodies)
    {
        dynamic_cast<video_verlet_object&>(*bod).acc += gravity;
    }
}

void verlet_container::apply_constraint()
{
    for(auto& obj : bodies)
    {
        vec2 to_obj = obj->pos - container_pos;

        float dist = sqrt(to_obj.x*to_obj.x + to_obj.y*to_obj.y);

        if(dist > container_r - obj->radius)
        {
            vec2 n = to_obj / dist;

            obj->pos = container_pos + n * (container_r - obj->radius);
        }
    }
}

void verlet_container::do_simple_collisions()
{
    for(int i = 0; i < bodies.size(); ++i)
        for (int j = 0; j < bodies.size(); ++j)
        {
            if(i == j)
                continue;
            auto &obj1 = bodies[i];
            auto &obj2 = bodies[j];
            vec2 coll_axis = obj1->pos - obj2->pos;
            float dist = sqrt(coll_axis.x*coll_axis.x + coll_axis.y*coll_axis.y);
            if(dist < obj1->radius + obj2->radius)
            {
                vec2 n = coll_axis / dist;
                float delta = obj1->radius + obj2->radius - dist;

                obj1->pos += 0.5f * delta * n;
                obj2->pos -= 0.5f * delta * n;
            }
        }
}

void verlet_bodies::add_item(float x, float y, float r)
{
    bodies.emplace_back(new wiki_verlet_object(x, y, r));
}

void verlet_bodies::update(float dt)
{
    int substep = 10;
    float subdt = dt/substep;
    for(int i = 0; i < substep; ++i)
    {
        //apply_constraint();
        do_simple_collisions();
        update_positions(subdt);
    }
}


void verlet_bodies::update_positions(float dt)
{
    for(auto &b : bodies)
    {
        b->update(dt);
    }
}


void verlet_bodies::apply_constraint()
{
    for(auto& obj : bodies)
    {
        vec2 to_obj = obj->pos - container_pos;

        float dist = sqrt(to_obj.x*to_obj.x + to_obj.y*to_obj.y);

        if(dist > container_r - obj->radius)
        {
            vec2 n = to_obj / dist;

            obj->pos = container_pos + n * (container_r - obj->radius);
        }
    }
}

void verlet_bodies::do_simple_collisions()
{
    for(int i = 0; i < bodies.size(); ++i)
        for (int j = 0; j < bodies.size(); ++j)
        {
            if(i == j)
                continue;
            auto &obj1 = bodies[i];
            auto &obj2 = bodies[j];
            vec2 coll_axis = obj1->pos - obj2->pos;
            float dist = sqrt(coll_axis.x*coll_axis.x + coll_axis.y*coll_axis.y);
            if(dist < obj1->radius + obj2->radius)
            {
                vec2 n = coll_axis / dist;
                float delta = obj1->radius + obj2->radius - dist;

                obj1->pos += 0.5f * delta * n;
                obj2->pos -= 0.5f * delta * n;
            }
        }
}
