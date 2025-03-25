#include "particlesystem.h"

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
    lifetime = rand() % 21 + 30;
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

void particle_system::render_particle(SDL_Renderer* renderer)
{
    for(int i = (int)v.size() - 1; i >= 0; i--)
    {
        v[i].update_position();
        if(v[i].is_dead())
        {
            v.erase(v.begin() + i);
        }
        else v[i].render(renderer);
    }
}






