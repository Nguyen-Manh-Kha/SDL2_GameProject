#include "character_status.h"
#include "function.h"
#include "treesystem.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

status::status(SDL_Texture* _heart, SDL_Texture* _water)
{
    SDL_Point tmp = {660, 547};
    flame flame_tmp = flame(tmp, -1);
    flame_point = flame_tmp;

    heart = _heart;
    water = _water;
    health = 450;
    water_level = 850;
}

void status::lose_water()
{
    water_level -= 0.6;
}

bool status::not_empty_water()
{
    return water_level >= 0.6;
}

void status::refill_water()
{
    water_level += 3;
}

bool status::not_full_water()
{
    return water_level <= 847;
}

void status::catch_fire(treesystem forest, bushsystem bushes)
{
    for(int i = 0; i < (int)bushes.bush_system.size(); i++)
    {
        if(i < (int)forest.tree_system.size() && forest.tree_system[i].onscreen())
        {
            for(int j = 0; j < (int)forest.tree_system[i].flame_points.size(); j++)
            {
                flame_point.receive_flame(forest.tree_system[i].flame_points[j]);
            }
        }
        if(bushes.bush_system[i].onscreen())
        {
            for(int j = 0; j < (int)bushes.bush_system[i].flame_points.size(); j++)
            {
                flame_point.receive_flame(bushes.bush_system[i].flame_points[j]);
            }
        }
    }
}

void status::on_fire()
{
    if(flame_point.be_burning())
    {
        flame_point.lose_health(67);
        health -= 6;
        if(water_level >= 9)water_level -= 9;
    }
}

void status::render(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    SDL_Rect heart_rect = {10, 725, 30, 25};
    SDL_Rect health_rect = {50, 730, 0, 15};
    health_rect.w = static_cast <int> (health);
    SDL_RenderCopy(renderer, heart, NULL, &heart_rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health_rect);

    SDL_Rect water_rect = {510, 722, 20, 28};
    SDL_Rect water_level_rect = {540, 730, 0, 15};
    water_level_rect.w = static_cast <int> (water_level);
    SDL_RenderCopy(renderer, water, NULL, &water_rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &water_level_rect);

    flame_point.render_flame(renderer, flame_img);
}

bool status::lose()
{
    return health <= 0;
}