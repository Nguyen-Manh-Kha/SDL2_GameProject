#ifndef TREESYSTEM_H
#define TREESYSTEM_H

#include "function.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

class flame
{
    private:
        SDL_Point point;
        int w, h;
        bool burning;
        int health;
        int spread_time;
    public:
        flame();
        flame(SDL_Point _point, int percentage);
        bool be_burning();
        void sudden_flame();
        void update_flame(bool move_left);
        void receive_flame(flame other);
        void render_flame(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        bool check_collision_water(int X, int Y);
        void lose_health(int num); // for character only
};

class tree
{
    private:
        int type;
        SDL_Texture* image;
        SDL_Texture* burnt_image;
        int x, y, w, h;
        int health;
    public:
        bool is_dead;
        vector<flame> flame_points;
        tree(int _type, int &num, int _y, int _w, int _h, int _health);
        void load_tree(SDL_Texture* tree_texture[],SDL_Texture* burnt_tree_texture[], int num);
        void render_tree(SDL_Renderer* renderer);
        void update_position(bool move_left);
        void setup_flame_points();
        void render_flame_tree(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        void lose_health();
        bool onscreen();
};

class treesystem
{
    private:
        // blank

    public:
        vector <tree> tree_system;
        void setup_tree(SDL_Texture* tree_texture[], SDL_Texture* burnt_tree_texture[]);
        void update_forest(bool move_left);
        void health_tree();
        void spread_flame_forest();
        void render_forest(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        int tree_near_house;
        int give_tree_near_house_num();
        bool lose();
        bool win(int &survive_tree);
};

class bush
{
    private:
        int type;
        SDL_Texture* bush_img;
        SDL_Texture* burnt_img;
        int x, y, w, h;
        int health;
    public:
        bool is_dead;
        vector<flame> flame_points;
        bush(int &num, int _y, int _w, int _h, int _health);
        void load_bush(SDL_Texture* bush_texture[], SDL_Texture* burnt_bush_texture[], int num);
        void render_bush(SDL_Renderer* renderer);
        void update_position(bool move_left);
        void setup_flame_bush();
        void render_flame_bush(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        void lose_health();
        bool onscreen();
};

class bushsystem
{
    private:
        // blank
    public:
        vector <bush> bush_system;
        void setup_bush(SDL_Texture* bush_texture[], SDL_Texture* burnt_bush_texture[]);
        void update_bushes(bool move_left);
        void health_bush();
        void spread_flame_bushes();
        void render_bushes(SDL_Renderer* renderer, SDL_Texture* flame_img[]);
        int bush_near_house;
        int give_bush_near_house_num();
        bool lose();
        bool win(int &survive_bush);
};

#endif
