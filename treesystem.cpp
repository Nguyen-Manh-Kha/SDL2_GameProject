#include "treesystem.h"
#include "function.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>

using namespace std;

tree::tree(int &num, int _y, int _w, int _h)
{
    x = num + rand() % 101;
    num += _w / 2;
    y = _y;
    w = _w;
    h = _h;
}

void tree::load_tree(SDL_Texture* tree_texture[], int num)
{
    image = tree_texture[num];
}

void tree::render_tree(SDL_Renderer* renderer)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, image, NULL, &rect);
}

void tree::update_position(bool move_left)
{
    if(move_left) x += 5;
    else x -= 5;
}


void treesystem::setup_tree(SDL_Texture* tree_texture[])
{
    int num = -7000;
    for(int i = 0; i <= 56; i++)
    {
        int tmp = 1 + rand() % 18;
        if(tmp == 1)
        {
            tree tree_tmp1(num, 123, 500, 600);
            tree_tmp1.load_tree(tree_texture, 1);
            tree_system.push_back(tree_tmp1);
        }
        else if(tmp == 2)
        {
            tree tree_tmp2(num, 165, 592, 558);
            tree_tmp2.load_tree(tree_texture, 2);
            tree_system.push_back(tree_tmp2);
        }
        else if(tmp == 3)
        {
            tree tree_tmp3(num, 99, 768, 624);
            tree_tmp3.load_tree(tree_texture, 3);
            tree_system.push_back(tree_tmp3);
        }
        else if(tmp == 4)
        {
            tree tree_tmp4(num, 121, 581, 602);
            tree_tmp4.load_tree(tree_texture, 4);
            tree_system.push_back(tree_tmp4);
        }
        else if(tmp == 5)
        {
            tree tree_tmp5(num, 170, 560, 553);
            tree_tmp5.load_tree(tree_texture, 5);
            tree_system.push_back(tree_tmp5);
        }
        else if(tmp == 6)
        {
            tree tree_tmp6(num, 59, 736, 664);
            tree_tmp6.load_tree(tree_texture, 6);
            tree_system.push_back(tree_tmp6);
        }
        else if(tmp == 7)
        {
            tree tree_tmp7(num, -69, 648, 792);
            tree_tmp7.load_tree(tree_texture, 7);
            tree_system.push_back(tree_tmp7);
        }
        else if(tmp == 8)
        {
            tree tree_tmp8(num, 3, 848, 720);
            tree_tmp8.load_tree(tree_texture, 8);
            tree_system.push_back(tree_tmp8);
        }
        else if(tmp == 9)
        {
            tree tree_tmp9(num, 129, 522, 594);
            tree_tmp9.load_tree(tree_texture, 9);
            tree_system.push_back(tree_tmp9);
        }
        else if(tmp == 10)
        {
            tree tree_tmp10(num, 3, 945, 720);
            tree_tmp10.load_tree(tree_texture, 10);
            tree_system.push_back(tree_tmp10);
        }
        else if(tmp == 11)
        {
            tree tree_tmp11(num, 191, 448, 532);
            tree_tmp11.load_tree(tree_texture, 11);
            tree_system.push_back(tree_tmp11);
        }
        else if(tmp == 12)
        {
            tree tree_tmp12(num, -6, 1053, 729);
            tree_tmp12.load_tree(tree_texture, 12);
            tree_system.push_back(tree_tmp12);
        }
        else if(tmp == 13)
        {
            tree tree_tmp13(num, 39, 792, 684);
            tree_tmp13.load_tree(tree_texture, 13);
            tree_system.push_back(tree_tmp13);
        }
        else if(tmp == 14)
        {
            tree tree_tmp14(num, 12, 774, 711);
            tree_tmp14.load_tree(tree_texture, 14);
            tree_system.push_back(tree_tmp14);
        }
        else if(tmp == 15)
        {
            tree tree_tmp15(num, 115, 536, 608);
            tree_tmp15.load_tree(tree_texture, 15);
            tree_system.push_back(tree_tmp15);
        }
        else if(tmp == 16)
        {
            tree tree_tmp16(num, 142, 532, 581);
            tree_tmp16.load_tree(tree_texture, 16);
            tree_system.push_back(tree_tmp16);
        }
        else if(tmp == 17)
        {
            tree tree_tmp17(num, 120, 666, 603);
            tree_tmp17.load_tree(tree_texture, 17);
            tree_system.push_back(tree_tmp17);
        }
        else if(tmp == 18)
        {
            tree tree_tmp18(num, 66, 765, 657);
            tree_tmp18.load_tree(tree_texture, 18);
            tree_system.push_back(tree_tmp18);
        }
    }
}

void treesystem::update_forest(bool move_left)
{
    for(int i = 0;  i < (int)tree_system.size(); i++)
    {
        tree_system[i].update_position(move_left);
    }
}

void treesystem::render_forest(SDL_Renderer* renderer)
{
    for(int i = 0;  i < (int)tree_system.size(); i++)
    {
        tree_system[i].render_tree(renderer);
    }
}