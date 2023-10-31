#include <iostream>
#include <string>
#include <chrono>

#include "physics_engine.hpp"

int main(int argc, char *argv[])
{
    physics_engine p;
    if(p.Construct(800, 450, 2, 2))
        p.Start();

    return 0;
}
