#define OLC_PGE_APPLICATION
#include "physics_engine.hpp"

#include <chrono>
#include <thread>

physics_engine::physics_engine()
{

}

bool physics_engine::OnUserCreate()
{
    solver = std::make_unique<verlet_bodies>();

    solver->add_item(400, 100, 20);
    solver->add_item(400, 350, 20);

    return true;
}


bool physics_engine::OnUserUpdate(float dt)
{
    using namespace std::chrono_literals;

    Clear(olc::BLACK);

    if(GetMouse(0).bPressed || GetMouse(1).bPressed)
    {
        for(auto &obj : solver->bodies)
        {
            vec2 dist_vec = vec2{(float)GetMouseX(), (float)GetMouseY()} - obj->pos;
            float mdist = sqrt(dist_vec.x*dist_vec.x+dist_vec.y*dist_vec.y);
            if(mdist <= obj->radius)
            {
                curr_sel = obj;
            }
        }
    }

    if(GetMouse(0).bHeld)
    {
        if(!curr_sel.expired())
        {
            curr_sel.lock()->pos = vec2{(float)GetMouseX(), (float)GetMouseY()};
        }
    }

    if(GetMouse(1).bHeld)
    {
        if(!curr_sel.expired())
            DrawLine(curr_sel.lock()->pos.x, curr_sel.lock()->pos.y, GetMouseX(), GetMouseY());
    }

    if(GetMouse(1).bReleased)
    {
        if(!curr_sel.expired())
        {
            vec2 dist = vec2{(float)GetMouseX(), (float)GetMouseY()} - curr_sel.lock()->pos;
            dist /= 0.5;
            curr_sel.lock()->add_force(dist);
        }
    }

    do_physics(dt);

    int i = 0;

    for(auto &obj : solver->bodies)
    {
        DrawCircle(obj->pos.x, obj->pos.y, obj->radius);
    }

    //std::this_thread::sleep_for(100ms);

    return true;
}

bool physics_engine::OnUserDestroy()
{
    return true;
}

void physics_engine::do_physics(float dt)
{
    solver->update(dt);
}
