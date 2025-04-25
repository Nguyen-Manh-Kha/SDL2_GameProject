#include "treesystem.h"
#include "home.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

house::house(SDL_Texture* _image)
{
    rect.x = 500;
    rect.y = 101;
    rect.w = 816;
    rect.h = 622;
    health = 1000;
    image = _image;
}

bool house::onscreen()
{
    return (rect.x <= 1400 || rect.x >= -900);
}

void house::set_up_flame_points()
{
    SDL_Point point;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            int num = i * 3 + j;
            if(num == 1 || num == 3 || num ==5 || num == 10 || num == 11 || num == 12 || num == 17) continue;
            point.x = 600 + 100 * i + rand() % 30;
            point.y = 150 + 150 * j + rand() % 30;
            flame tmp(point, -1);
            flame_points.push_back(tmp);
        }
    }
}

void house::update_position(bool move_left)
{
    if(move_left) rect.x += 5;
    else rect.x -= 5;
    for(int i = 0; i < (int)flame_points.size(); i++)
    {
        flame_points[i].update_flame(move_left);
    }
}

void house::spread_flame_house(treesystem &forest, bushsystem &bushes)
{
    int tree_right = forest.give_tree_near_house_num();
    int bush_right = bushes.give_bush_near_house_num();
    // flame spread between tree and house
    for(int i = tree_right; i >= tree_right - 1; i--)
    {
        for(int j = 0; j < (int)forest.tree_system[i].flame_points.size(); j++) if(forest.tree_system[i].flame_points[j].be_burning() == false)
        {
            for(int t = 0; t < (int)flame_points.size(); t++) if(flame_points[t].be_burning())
            {
                forest.tree_system[i].flame_points[j].receive_flame(flame_points[t]);
            }
        }
        else if(forest.tree_system[i].flame_points[j].be_burning())
        {
            for(int t = 0; t < (int)flame_points.size(); t++) if(flame_points[t].be_burning() == false)
            {
                flame_points[t].receive_flame(forest.tree_system[i].flame_points[j]);
            }
        }
    }
    // flame spread between bush and house
    for(int i = bush_right; i >= bush_right - 1; i--)
    {
        for(int j = 0; j < (int)bushes.bush_system[i].flame_points.size(); j++) if(bushes.bush_system[i].flame_points[j].be_burning() == false)
        {
            for(int t = 0; t < (int)flame_points.size(); t++) if(flame_points[t].be_burning())
            {
                bushes.bush_system[i].flame_points[j].receive_flame(flame_points[t]);
            }
        }
        else if(bushes.bush_system[i].flame_points[j].be_burning())
        {
            for(int t = 0; t < (int)flame_points.size(); t++) if(flame_points[t].be_burning() == false)
            {
                flame_points[t].receive_flame(bushes.bush_system[i].flame_points[j]);
            }
        }
    }
    // house spread flame on its own
    for(int i = 0; i < (int)flame_points.size(); i++) if(flame_points[i].be_burning() == false)
    {
        for(int j = 0; j < (int)flame_points.size(); j++) if(flame_points[j].be_burning())
        {
            flame_points[i].receive_flame(flame_points[j]);
        }
    }
}

bool house::lose_health()
{
    for(int i = 0; i < (int)flame_points.size(); i++) if(flame_points[i].be_burning())
    {
        health -= 1;
    }
    if(health <= 0) return true;
    return false;
}

void house::render_house(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    if(onscreen());
    {
        SDL_RenderCopy(renderer, image, NULL, &rect);
        for(int i = 0; i < (int)flame_points.size(); i++)
        {
            flame_points[i].render_flame(renderer, flame_img);
        }
    }
}




well::well(SDL_Texture* _image)
{
    rect.x = 200;
    rect.y = 547;
    rect.w = 212;
    rect.h = 176;
    health = 5000;
    image = _image;
}

bool well::onscreen()
{
    return (rect.x <= 1400 || rect.x >= -300);
}

void well::set_up_flame_points()
{
    SDL_Point tmp = {200, 500};
    flame flame1(tmp, -1);
    flame_points.push_back(flame1);
    tmp.x = 300, tmp.y = 400;
    flame flame2(tmp, -1);
    flame_points.push_back(flame2);
}

void well::update_position(bool move_left)
{
    if(move_left) rect.x += 5;
    else rect.x -= 5;
    for(int i = 0; i < (int)flame_points.size(); i++)
    {
        flame_points[i].update_flame(move_left);
    }
}

void well::spread_flame_well(bushsystem &bushes)
{
    int bush_right = bushes.give_bush_near_house_num();
    for(int i = bush_right; i >= bush_right - 6; i--)
    {
        for(int j = 0; j < (int)bushes.bush_system[i].flame_points.size(); j++) if(bushes.bush_system[i].flame_points[j].be_burning())
        {
            for(int t = 0; t < (int)flame_points.size(); t++) if(flame_points[t].be_burning() == false)
            {
                flame_points[t].receive_flame(bushes.bush_system[i].flame_points[j]);
            }
        }
    }
}

bool well::lose_health()
{
    for(int i = 0; i < (int)flame_points.size(); i++) if(flame_points[i].be_burning())
    {
        health -= 1;
    }
    if(health <= 0) return true;
    return false;
}

void well::render_well(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    if(onscreen());
    {
        SDL_RenderCopy(renderer, image, NULL, &rect);
        for(int i = 0; i < (int)flame_points.size(); i++)
        {
            flame_points[i].render_flame(renderer, flame_img);
        }
    }
}

bool well::near_character()
{
    return (rect.x >= 550 && rect.x <= 650);
}
