#ifndef TREESYSTEM_H
#define TREESYSTEM_H

#include "function.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>

using namespace std;

class tree
{
    private:
        SDL_Texture* image;
        int x, y, w, h;
    
    public:
        tree(int &num, int _y, int _w, int _h);
        void load_tree(SDL_Texture* tree_texture[], int num);
        void render_tree(SDL_Renderer* renderer);
        void update_position(bool move_left);

};

class treesystem
{
    private:
        vector <tree> tree_system;
 
    public:
        void setup_tree(SDL_Texture* tree_texture[]);
        void update_forest(bool move_left);
        void render_forest(SDL_Renderer* renderer);
};

#endif