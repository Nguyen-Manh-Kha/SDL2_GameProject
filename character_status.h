#ifndef CHARACTER_STATUS_H
#define CHARACTER_STATUS_H

#include "function.h"
#include "treesystem.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class status
{
    private:
        flame flame_point;
        SDL_Texture* heart;
        SDL_Texture* water;
        double health, water_level;
    
    public:
        status(SDL_Texture* _heart, SDL_Texture* _water);
        void lose_water();
        bool not_empty_water();
        void refill_water();
        bool not_full_water();
        void catch_fire(treesystem forest, bushsystem bushes);
        void on_fire();
        void render(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        bool lose();
};

#endif