#include "particlesystem.h"
#include "home.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

/// control each particle
particle::particle(double _x, double _y, double _angle)
{
    x = _x;
    y = _y;
    angle = _angle;
    speed = rand() % 3 + 11;
    lifetime = rand() % 21 + 40;
    particle_size = rand() % 3 + 3;
}

void particle::update_position()
{
    x += speed * cos(angle * 3.14 / 180);
    y -= ( speed * sin(angle * 3.14 / 180) - 0.01 * pow( (30 - lifetime), 2 ) );
    lifetime--;
}


void particle::render(SDL_Renderer* renderer)
{
    SDL_Rect particle_rect = {static_cast<int> (x), static_cast<int> (y), particle_size, particle_size};
    SDL_SetRenderDrawColor(renderer, rand() % 61, rand() % 61 + 52, rand() % 61 + 154 ,255);
    SDL_RenderFillRect(renderer, &particle_rect);
}

bool particle::is_dead()
{
    if(y >= 715) return true;
    return lifetime <= 0;
}

void particle::check_collision_flame(treesystem &forest, bushsystem &bushes, house &House, well &Well)
{
    for(int i = 0; i < (int)forest.tree_system.size(); i++) if(forest.tree_system[i].onscreen())
    {
        for(int j = 0; j < (int)forest.tree_system[i].flame_points.size(); j++)
        {
            if(forest.tree_system[i].flame_points[j].check_collision_water(x, y))
            {
                if(rand() % 100 <= 79)lifetime = 0;
            }
        }
    }

    for(int i = 0; i < (int)bushes.bush_system.size(); i++) if(bushes.bush_system[i].onscreen())
    {
        for(int j = 0; j < (int)bushes.bush_system[i].flame_points.size(); j++)
        {
            if(bushes.bush_system[i].flame_points[j].check_collision_water(x, y))
            {
                if(rand() % 100 <= 79)lifetime = 0;
            }
        }
    }

    if(House.onscreen())
    {
        for(int i = 0; i < (int)House.flame_points.size(); i++)
        {
            if(House.flame_points[i].check_collision_water(x, y))
            {
                if(rand() % 100 <= 79)lifetime = 0;
            }
        }
    }

    if(Well.onscreen())
    {
        for(int i = 0; i < (int)Well.flame_points.size(); i++)
        {
            if(Well.flame_points[i].check_collision_water(x, y))
            {
                if(rand() % 100 <= 79)lifetime = 0;
            }
        }
    }
}





/// particle system
void particle_system::add_particle(double X, double Y, double ANGLE)
{
    double tmp_ANGLE = ANGLE - 15;
    for(int i = 1; i <= 30; i++)
    {
        double rand_ANGLE = rand() % 31 + tmp_ANGLE; 
        particle tmp(X, Y, rand_ANGLE);
        v.push_back(tmp);
    }
}

void particle_system::render_particle(SDL_Renderer* renderer, treesystem &forest, bushsystem &bushes, house &House, well &Well)
{
    for(int i = (int)v.size() - 1; i >= 0; i--)
    {
        v[i].update_position();
        v[i].check_collision_flame(forest, bushes, House, Well);
        if(v[i].is_dead())
        {
            v.erase(v.begin() + i);
        }
        else v[i].render(renderer);
    }
}

void particle_system::reset()
{
    v.clear();
}






