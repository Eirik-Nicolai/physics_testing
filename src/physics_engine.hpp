#ifndef PHYSICS_ENGINE_H_
#define PHYSICS_ENGINE_H_
#include "olcPixelGameEngine.h"

#include "common/common.hpp"

#include "olc_balls.hpp"
#include "verlet_solver.hpp"

class physics_engine : public olc::PixelGameEngine
{
    public:
        physics_engine();

    public:
        bool OnUserCreate() override;
        bool OnUserUpdate(float) override;
        bool OnUserDestroy() override;

    public:
        void do_physics(float);


    private:
        std::unique_ptr<physics_solver> solver;
        std::weak_ptr<physics_body> curr_sel;


};

#endif // PHYSICS_ENGINE_H_
