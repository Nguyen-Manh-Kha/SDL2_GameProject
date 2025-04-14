#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "treesystem.h"
#include "home.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

class particle
{
    private:
        double x, y;
        double angle;
        double speed;
        int lifetime;
        int particle_size;
    public:
        particle(double _x, double _y, double _angle);
        void update_position();
        void render(SDL_Renderer* renderer);
        bool is_dead();
        void check_collision_flame(treesystem &forest, bushsystem &bushes, house &House, well &Well);
};

class particle_system
{
    private:
        vector<particle> v;
    public:
        void add_particle(double X, double Y, double ANGLE);
        void render_particle(SDL_Renderer* renderer, treesystem &forest, bushsystem &bushes, house &House, well &Well);
};

#endif
