#ifndef HOME_H
#define HOME_H

#include "treesystem.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class house
{
    private:
        SDL_Rect rect;
        SDL_Texture* image;
        int health;
    public:
        house(SDL_Texture* _image);
        bool onscreen();
        vector <flame> flame_points;
        void set_up_flame_points();
        void update_position(bool move_left);
        void spread_flame_house(treesystem &forest, bushsystem &bushes);
        bool lose_health();
        void render_house(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        void reset();
};

class well
{
    private:
        SDL_Rect rect;
        SDL_Texture* image;
        int health;
    public:
        well(SDL_Texture* _image);
        bool onscreen();
        vector <flame> flame_points;
        void set_up_flame_points();
        void update_position(bool move_left);
        void spread_flame_well(bushsystem &bushes);
        bool lose_health();
        void render_well(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        bool near_character();
        void reset();
};

#endif
