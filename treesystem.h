#ifndef TREESYSTEM_H
#define TREESYSTEM_H

#include "function.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>

using namespace std;

class flame
{
    private:
        SDL_Point point;
        bool burning;
        int health;
    public: 
        flame(SDL_Point _point);
        void update_flame(bool move_left);
        void render_flame(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        bool check_collision_water(int X, int Y);
};

class tree
{
    private:
        int type;
        SDL_Texture* image;
        int x, y, w, h;
    public:
        vector<flame> flame_points;
        tree(int _type, int &num, int _y, int _w, int _h);
        void load_tree(SDL_Texture* tree_texture[], int num);
        void render_tree(SDL_Renderer* renderer);
        void update_position(bool move_left);
        void setup_flame_points();
        void render_flame_tree(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        bool onscreen(); 
};

class treesystem
{
    private:
        // blank

    public:
        vector <tree> tree_system;
        void setup_tree(SDL_Texture* tree_texture[]);
        void update_forest(bool move_left);
        void render_forest(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
};

class bush
{
    private:
        int type;
        SDL_Texture* bush_img;
        int x, y, w, h;
    public:
        vector<flame> flame_points;
        bush(int &num, int _y, int _w, int _h);
        void load_bush(SDL_Texture* bush_texture[], int num);
        void render_bush(SDL_Renderer* renderer);
        void update_position(bool move_left);
        void setup_flame_bush();
        void render_flame_bush(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        bool onscreen();
};

class bushsystem
{
    private:
        // blank
    public:
        vector <bush> bush_system;
        void setup_bush(SDL_Texture* bush_texture[]);
        void update_bushes(bool move_left);
        void render_bushes(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
};

#endif
