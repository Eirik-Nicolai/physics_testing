#ifndef VERLET_SOLVER_H_
#define VERLET_SOLVER_H_

#include "common/common.hpp"

#include <vector>

// From video
// https://www.youtube.com/watch?v=lS_qeBy3aQI
struct video_verlet_object : public physics_body
{
    vec2 pos_old;
    vec2 acc;

    float radius;

    void add_force(vec2) override
    {
        // todo
    }
    void update(float) override;
    void accelerate(vec2);

    video_verlet_object(float x, float y, float radius)
        : physics_body(x, y, radius)
    {
        pos_old = pos;
    }
};

struct verlet_container : public physics_solver
{
    vec2 gravity{0.0f, 100.0f};

    vec2 container_pos{400, 200};
    float container_r = 150;

    void add_item(float x, float y, float radius) override;
    void update(float) override;

    void update_positions(float);
    void apply_gravitiy();
    void apply_constraint();
    void do_simple_collisions();

    verlet_container() : physics_solver(){}
};


// from wikipedia
// https://en.wikipedia.org/wiki/Verlet_integration#Algorithmic_representation
struct wiki_verlet_object : public physics_body
{
    vec2 vel { 0.0, 0.0 }; // 2 m/s along x-axis
    vec2 acc { 0.0, 0.0 }; // no acceleration at first
    float mass = 1.0; // 1kg
    float drag = 0.1; // rho*C*Area – simplified drag for this example
    /**
     * Update pos and vel using "Velocity Verlet" integration
     * @param dt DeltaTime / time step [eg: 0.01]
     */
    void update(float dt) override
    {
        vec2 new_pos = pos + vel*dt + acc*(dt*dt*0.5);
        vec2 new_acc = apply_forces(); // only needed if acceleration is not constant
        vec2 new_vel = vel + (acc+new_acc)*(dt*0.5);
        pos = new_pos;
        vel = new_vel;
        acc = new_acc;
    }


    void add_force(vec2 force) override
    {
        vel += force;
    }

    vec2 apply_forces() const
    {
        vec2 grav = vec2{0.0f, 0.0f};
        vec2 drag_force = 0.5 * drag * vel * vel; // D = 0.5 * (rho * C * Area * vel^2)
        vec2 drag = drag_force / mass; // a = F/m
        return grav - drag;
    }

    wiki_verlet_object(float x, float y, float radius)
        : physics_body(x, y, radius) {}
};


struct verlet_bodies : public physics_solver
{
    vec2 container_pos{400, 200};
    float container_r = 150;

    void add_item(float x, float y, float radius) override;
    void update(float) override;
    void update_positions(float);
    void apply_constraint();
    void do_simple_collisions();

    verlet_bodies() : physics_solver(){}
};


#endif // VERLET_SOLVER_H_
