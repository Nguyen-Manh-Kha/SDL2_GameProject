#include "treesystem.h"
#include "function.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

flame::flame()
{
    // blank
}

flame::flame(SDL_Point _point, int percentage)
{
    point.x = _point.x;
    point.y = _point.y;
    int tmp = 85 + rand() % 31;
    w = 105 * tmp / 100;
    h = 200 * tmp / 100;
    if(rand() % 100 <= percentage) // 30 percents
    {
        burning = true; 
        health = 1000 * tmp / 100;
    }
    else
    {
        burning = false;
        health = 0;
    }
    spread_time = 0;
}

bool flame::be_burning()
{
    return burning;
}

void flame::sudden_flame()
{
    burning = true;
    health = 1000;
}

void flame::update_flame(bool move_left)
{
    if(move_left) point.x += 5;
    else point.x -= 5;
}

void flame::receive_flame(flame other)
{
    if(other.burning)
    {
        double dx = (double) (other.point.x - point.x);
        double dy = (double) (other.point.x - point.x);
        double distance = sqrt(pow(dx, 2) + pow(dy, 2));
        if(distance <= 150) spread_time++;
    }
    if(spread_time >= 200)
    {
        burning = true;
        health = 1000;
        spread_time = 0;
    }
}

void flame::render_flame(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    if(burning)
    {
        SDL_Rect rect = {point.x, point.y, w, h};
        SDL_RenderCopy(renderer, flame_img[1 + rand() % 8], NULL, &rect);
    }
}

bool flame::check_collision_water(int X, int Y)
{
    if(burning == true && point.x + 20 <= X && X <= point.x + w - 20 && point.y + 10 <= Y && Y <= point.y + h - 10)
    {
        health--;
        if(health <= 0) burning = false;
        return true;
    }
    return false;
}

void flame::lose_health(int num) // for character only
{
    health -= num;
    if(health <= 0) burning = false;
}



// each tree
tree::tree(int _type, int &num, int _y, int _w, int _h, int _health)
{
    type = _type;
    x = num + rand() % 101;
    num += _w / 2;
    y = _y;
    w = _w;
    h = _h;
    health = _health;
    is_dead = false;
}

void tree::load_tree(SDL_Texture* tree_texture[], SDL_Texture* burnt_tree_texture[],  int num)
{
    image = tree_texture[num];
    burnt_image = burnt_tree_texture[num];
}

void tree::render_tree(SDL_Renderer* renderer)
{
    SDL_Rect rect = {x, y, w, h};
    if(is_dead == false) SDL_RenderCopy(renderer, image, NULL, &rect);
    if(is_dead) SDL_RenderCopy(renderer, burnt_image, NULL, &rect);
}

void tree::update_position(bool move_left)
{
    if(move_left)
    {
        x += 5;
        for(int i = 0; i < (int)flame_points.size(); i++)
        {
            flame_points[i].update_flame(move_left);
        }
    }
    else
    {
        x -= 5;
        for(int i = 0; i < (int)flame_points.size(); i++)
        {
            flame_points[i].update_flame(move_left);
        }
    }
}

void tree::setup_flame_points()
{
    if(type == 1)
    {
        for(int i = 1; i <= 5; i++)
        {
            SDL_Point point = {x + 90 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 40; else point.y = y + 80 + rand() % 80;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 2)
    {
        for(int i = 1; i <= 4; i++)
        {
            SDL_Point point = {x + 130 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 20; else point.y = y + 40 + rand() % 40;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 3)
    {
        for(int i = 1; i <= 6; i++)
        {
            SDL_Point point = {x + 116 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 37; else point.y = y + 80 + rand() % 85;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 4)
    {
        for(int i = 1; i <= 5; i++)
        {
            SDL_Point point = {x + 106 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 40; else point.y = y + 90 + rand() % 90;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 5)
    {
        for(int i = 1; i <= 4; i++)
        {
            SDL_Point point = {x + 125 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 32; else point.y = y + 65 + rand() % 65;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 6)
    {
        for(int i = 1; i <= 7; i++)
        {
            SDL_Point point = {x + 100 * (i - 1) + rand() % 30, y};
            if(i % 3 == 1) point.y = y + 160 + rand() % 80;
            else if(i % 3 == 0) point.y = y + 80 + rand() % 80;
            else point.y = y + rand() % 30;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 7)
    {
        for(int i = 1; i <= 5; i++)
        {
            SDL_Point point = {x + 120 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 40; else point.y = y + 125 + rand() % 125;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 8)
    {
        for(int i = 1; i <= 7; i++)
        {
            SDL_Point point = {x + 114 * (i - 1) + rand() % 30, y};
            if(i % 3 == 1) point.y = y+ rand() % 30;
            else if(i % 3 == 0) point.y = y + 150 + rand() % 75;
            else point.y = y + 75 + rand() % 75;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 9)
    {
        for(int i = 1; i <= 5; i++)
        {
            SDL_Point point = {x + 90 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 30; else point.y = y + 90 + rand() % 90;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 10)
    {
        for(int i = 1; i <= 10; i++)
        {
            SDL_Point point = {x + 85 * (i - 1) + rand() % 30, y};
            if(i % 4 == 1) point.y = y + 225 + rand() % 60;
            else if(i % 4 == 2) point.y = y + rand() % 30;
            else if(i % 4 == 3) point.y = y + 150 + rand() % 60;
            else point.y = y + 75 + rand() % 60;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 11)
    {
        for(int i = 1; i <= 5; i++)
        {
            SDL_Point point = {x + 80 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 30; else point.y = y + 75 + rand() % 75;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 12)
    {
        for(int i = 1; i <= 11; i++)
        {
            SDL_Point point = {x + 90 * (i - 1) + rand() % 30, y};
            if(i % 4 == 1) point.y = y + 270 + rand() % 75;
            else if(i % 4 == 2) point.y = y + rand() % 30;
            else if(i % 4 == 3) point.y = y + 180 + rand() % 75;
            else point.y = y + 90 + rand() % 75;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 13)
    {
        for(int i = 1; i <= 7; i++)
        {
            SDL_Point point = {x + 103 * (i - 1) + rand() % 30, y};
            if(i % 3 == 1) point.y = y+ rand() % 30;
            else if(i % 3 == 2) point.y = y + 186 + rand() % 80;
            else point.y = y + 93 + rand() % 80;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 14)
    {
        for(int i = 1; i <= 6; i++)
        {
            SDL_Point point = {x + 116 * (i - 1) + rand() % 30, y};
            if(i % 3 == 1) point.y = y+ rand() % 30;
            else if(i % 3 == 2) point.y = y + 192 + rand() % 90;
            else point.y = y + 96 + rand() % 90;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 15)
    {
        for(int i = 1; i <= 5; i++)
        {
            SDL_Point point = {x + 90 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 30; else point.y = y + 110 + rand() % 110;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 16)
    {
        for(int i = 1; i <= 6; i++)
        {
            SDL_Point point = {x + 80 * (i - 1) + rand() % 30, y};
            if(i % 2 == 1) point.y = y + rand() % 30; else point.y = y + 72 + rand() % 72;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 17)
    {
        for(int i = 1; i <= 7; i++)
        {
            SDL_Point point = {x + 85 * (i - 1) + rand() % 30, y};
            if(i % 2 == 0) point.y = y + rand() % 30; else point.y = y + 135 + rand() % 135;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
    else if(type == 18)
    {
        for(int i = 1; i <= 9; i++)
        {
            SDL_Point point = {x + 77 * (i - 1) + rand() % 30, y};
            if(i % 4 == 1) point.y = y + 225 + rand() % 65;
            else if(i % 4 == 2) point.y = y + rand() % 30;
            else if(i % 4 == 3) point.y = y + 150 + rand() % 65;
            else point.y = y + 75 + rand() % 65;
            flame tmp(point,29);
            flame_points.push_back(tmp);
        }
    }
}

void tree::render_flame_tree(SDL_Renderer*renderer, SDL_Texture* flame_img[])
{
    for(int i = 0; i < (int)flame_points.size(); i++)
    {
        flame_points[i].render_flame(renderer, flame_img);
    }
}

void tree::lose_health()
{
    if(is_dead == false)
    {
        for(int i = 0; i < (int)flame_points.size(); i++) if(flame_points[i].be_burning())
        {
            health -= 1;
        }
    }
    if(health <= 0)
    {
        is_dead = true;
        int tmp = flame_points.size();
        for(int i = 1; i <= tmp; i++) flame_points.pop_back();
    }
}

bool tree::onscreen()
{
    if(x >= -1100 && x <= 1400) return true;
    return false;
}




// tree system
void treesystem::setup_tree(SDL_Texture* tree_texture[], SDL_Texture* burnt_tree_texture[])
{
    int num = -12600;
    bool home = false;
    while(num <= 14000)
    {
        if(num >= -200 && home == false)
        {
            tree tree_tmp6(6, num, 59, 736, 664, 7000);
            tree_tmp6.load_tree(tree_texture, burnt_tree_texture, 6);
            tree_tmp6.setup_flame_points();
            tree_system.push_back(tree_tmp6);
            num = 1100;
            home = true;
            tree_near_house = (int)tree_system.size();
        }
        int tmp = 1 + rand() % 18;
        if(tmp == 1)
        {
            tree tree_tmp1(1, num, 123, 500, 600, 5000);
            tree_tmp1.load_tree(tree_texture, burnt_tree_texture, 1);
            tree_tmp1.setup_flame_points();
            tree_system.push_back(tree_tmp1);
        }
        else if(tmp == 2)
        {
            tree tree_tmp2(2, num, 165, 592, 558, 4000);
            tree_tmp2.load_tree(tree_texture, burnt_tree_texture, 2);
            tree_tmp2.setup_flame_points();
            tree_system.push_back(tree_tmp2);
        }
        else if(tmp == 3)
        {
            tree tree_tmp3(3, num, 99, 768, 624, 6000);
            tree_tmp3.load_tree(tree_texture, burnt_tree_texture, 3);
            tree_tmp3.setup_flame_points();
            tree_system.push_back(tree_tmp3);
        }
        else if(tmp == 4)
        {
            tree tree_tmp4(4, num, 121, 581, 602, 5000);
            tree_tmp4.load_tree(tree_texture, burnt_tree_texture, 4);
            tree_tmp4.setup_flame_points();
            tree_system.push_back(tree_tmp4);
        }
        else if(tmp == 5)
        {
            tree tree_tmp5(5, num, 170, 560, 553, 4000);
            tree_tmp5.load_tree(tree_texture, burnt_tree_texture, 5);
            tree_tmp5.setup_flame_points();
            tree_system.push_back(tree_tmp5);
        }
        else if(tmp == 6)
        {
            tree tree_tmp6(6, num, 59, 736, 664, 7000);
            tree_tmp6.load_tree(tree_texture, burnt_tree_texture, 6);
            tree_tmp6.setup_flame_points();
            tree_system.push_back(tree_tmp6);
        }
        else if(tmp == 7)
        {
            tree tree_tmp7(7, num, -69, 648, 792, 5000);
            tree_tmp7.load_tree(tree_texture, burnt_tree_texture, 7);
            tree_tmp7.setup_flame_points();
            tree_system.push_back(tree_tmp7);
        }
        else if(tmp == 8)
        {
            tree tree_tmp8(8, num, 3, 848, 720, 7000);
            tree_tmp8.load_tree(tree_texture, burnt_tree_texture, 8);
            tree_tmp8.setup_flame_points();
            tree_system.push_back(tree_tmp8);
        }
        else if(tmp == 9)
        {
            tree tree_tmp9(9, num, 129, 522, 594, 5000);
            tree_tmp9.load_tree(tree_texture, burnt_tree_texture, 9);
            tree_tmp9.setup_flame_points();
            tree_system.push_back(tree_tmp9);
        }
        else if(tmp == 10)
        {
            tree tree_tmp10(10, num, 3, 945, 720, 10000);
            tree_tmp10.load_tree(tree_texture, burnt_tree_texture, 10);
            tree_tmp10.setup_flame_points();
            tree_system.push_back(tree_tmp10);
        }
        else if(tmp == 11)
        {
            tree tree_tmp11(11, num, 191, 448, 532, 5000);
            tree_tmp11.load_tree(tree_texture, burnt_tree_texture, 11);
            tree_tmp11.setup_flame_points();
            tree_system.push_back(tree_tmp11);
        }
        else if(tmp == 12)
        {
            tree tree_tmp12(12, num, -6, 1053, 729, 11000);
            tree_tmp12.load_tree(tree_texture, burnt_tree_texture, 12);
            tree_tmp12.setup_flame_points();
            tree_system.push_back(tree_tmp12);
        }
        else if(tmp == 13)
        {
            tree tree_tmp13(13, num, 39, 792, 684, 7000);
            tree_tmp13.load_tree(tree_texture, burnt_tree_texture, 13);
            tree_tmp13.setup_flame_points();
            tree_system.push_back(tree_tmp13);
        }
        else if(tmp == 14)
        {
            tree tree_tmp14(14, num, 12, 774, 711, 6000);
            tree_tmp14.load_tree(tree_texture, burnt_tree_texture, 14);
            tree_tmp14.setup_flame_points();
            tree_system.push_back(tree_tmp14);
        }
        else if(tmp == 15)
        {
            tree tree_tmp15(15, num, 115, 536, 608, 5000);
            tree_tmp15.load_tree(tree_texture, burnt_tree_texture, 15);
            tree_tmp15.setup_flame_points();
            tree_system.push_back(tree_tmp15);
        }
        else if(tmp == 16)
        {
            tree tree_tmp16(16, num, 142, 532, 581, 6000);
            tree_tmp16.load_tree(tree_texture, burnt_tree_texture, 16);
            tree_tmp16.setup_flame_points();
            tree_system.push_back(tree_tmp16);
        }
        else if(tmp == 17)
        {
            tree tree_tmp17(17, num, 120, 666, 603, 7000);
            tree_tmp17.load_tree(tree_texture, burnt_tree_texture, 17);
            tree_tmp17.setup_flame_points();
            tree_system.push_back(tree_tmp17);
        }
        else if(tmp == 18)
        {
            tree tree_tmp18(18, num, 66, 765, 657, 9000);
            tree_tmp18.load_tree(tree_texture, burnt_tree_texture, 18);
            tree_tmp18.setup_flame_points();
            tree_system.push_back(tree_tmp18);
        }
    }
}

int treesystem::give_tree_near_house_num()
{
    return tree_near_house;
}

void treesystem::update_forest(bool move_left)
{
    for(int i = 0;  i < (int)tree_system.size(); i++)
    {
        tree_system[i].update_position(move_left);
    }
}

void treesystem::health_tree()
{
    for(int i = 0; i < (int)tree_system.size(); i++)
    {
        tree_system[i].lose_health();
    }
}

void treesystem::spread_flame_forest()
{
    for(int i = 0; i < (int)tree_system.size(); i++)
    {
        for(int j = 0; j < (int)tree_system[i].flame_points.size(); j++) if(tree_system[i].flame_points[j].be_burning() == false)
        {
            if(rand() % 10000 == 1808) tree_system[i].flame_points[j].sudden_flame(); 
            else for(int I = i - 1; I <= i + 1; I++)
            {
                for(int J = 0; J < (int)tree_system[I].flame_points.size(); J++)
                {
                    tree_system[i].flame_points[j].receive_flame(tree_system[I].flame_points[J]);
                }
            }
        }
    }
}

void treesystem::render_forest(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    for(int i = 0;  i < (int)tree_system.size(); i += 3) if(tree_system[i].onscreen())
    {
        tree_system[i].render_tree(renderer);
        tree_system[i].render_flame_tree(renderer, flame_img);
    }
    for(int i = 1; i < (int)tree_system.size(); i += 3) if(tree_system[i].onscreen())
    {
        tree_system[i].render_tree(renderer);
        tree_system[i].render_flame_tree(renderer, flame_img);
    }
    for(int i = 2; i < (int)tree_system.size(); i += 3) if(tree_system[i].onscreen())
    {
        tree_system[i].render_tree(renderer);
        tree_system[i].render_flame_tree(renderer, flame_img);
    }
}

bool treesystem::lose()
{
    for(int i = 0; i < (int)tree_system.size(); i++)
    {
        if(tree_system[i].is_dead == false) return false;
    }
    return true;
}

bool treesystem::win(int &survive_tree)
{
    int count = 0;
    for(int i = 0; i < (int)tree_system.size(); i++) if(tree_system[i].is_dead == false)
    {
        count++;
        for(int j = 0; j < (int)tree_system[i].flame_points.size(); j++)
        {
            if(tree_system[i].flame_points[j].be_burning()) return false;
        }
    }
    if(count > 0)
    {
        survive_tree = count;  
        return true;   
    }
    else return false;
}


// each bush
bush::bush(int &num, int _y, int _w, int _h, int _health)
{
    x = num + rand() % 101;
    num += _w *2 / 3;
    y = _y;
    w = _w;
    h = _h;
    health = _health;
    is_dead = false;
}

void bush::load_bush(SDL_Texture* bush_texture[],SDL_Texture* burnt_bush_texture[], int num)
{
    type = num;
    bush_img = bush_texture[num];
    burnt_img = burnt_bush_texture[num];
}

void bush::render_bush(SDL_Renderer* renderer)
{
    SDL_Rect rect = {x, y, w, h};
    if(is_dead == false) SDL_RenderCopy(renderer, bush_img, NULL, &rect);
    if(is_dead) SDL_RenderCopy(renderer, burnt_img, NULL, &rect);
}

void bush::update_position(bool move_left)
{
    if(move_left)
    {
        x += 5;
        for(int i = 0; i < (int)flame_points.size(); i++)
        {
            flame_points[i].update_flame(move_left);
        }
    }
    else 
    {
        x -= 5;
        for(int i = 0; i < (int)flame_points.size(); i++)
        {
            flame_points[i].update_flame(move_left);
        }
    }
}

void bush::setup_flame_bush()
{
    int flame_num;
    if(type == 4 || type == 6 || type == 7) flame_num = 2; else flame_num = 3;
    for(int i = 1; i <= flame_num; i++)
    {
        SDL_Point point = {x + w / flame_num * (i - 1) + rand() % 30, y - 110 + rand() % 30};
        flame tmp(point,29);
        flame_points.push_back(tmp);
    }
}

void bush::render_flame_bush(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    for(int i = 0; i < (int)flame_points.size(); i++)
    {
        flame_points[i].render_flame(renderer, flame_img);
    }
}

void bush::lose_health()
{
    if(is_dead == false)
    {
        for(int i = 0; i < (int)flame_points.size(); i++) if(flame_points[i].be_burning())
        {
            health -= 1;
        }
    }
    if(health <= 0)
    {
        is_dead = true;
        int tmp = flame_points.size();
        for(int i = 1; i <= tmp; i++) flame_points.pop_back();
    }
}

bool bush::onscreen()
{
    if(x >= -700 && x <= 1400) return true;
    return false;
}




// bush system
void bushsystem:: setup_bush(SDL_Texture* bush_texture[], SDL_Texture* burnt_bush_texture[])
{
    int num = -12600;
    bool house = false;
    while(num <= 14000)
    {
        if(num >= 350 && house == false)
        {
            num = 1100;
            bush_near_house = bush_system.size();
            house = true;
        }
        int tmp = 1 + rand() % 7;
        if(tmp == 1)
        {
            bush bush_tmp(num, 571, 380, 156, 3000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 1);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
        else if(tmp == 2)
        {
            bush bush_tmp(num, 603, 420, 124, 3000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 2);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
        else if(tmp == 3)
        {
            bush bush_tmp(num, 559, 404, 168, 3000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 3);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
        else if(tmp == 4)
        {
            bush bush_tmp(num, 592, 219, 135, 2000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 4);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
        else if(tmp == 5)
        {
            bush bush_tmp(num, 583, 452, 144, 3000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 5);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
        else if(tmp == 6)
        {
            bush bush_tmp(num, 618, 244, 112, 2000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 6);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
        else if(tmp == 7)
        {
            bush bush_tmp(num, 611, 256, 116, 2000);
            bush_tmp.load_bush(bush_texture, burnt_bush_texture, 7);
            bush_tmp.setup_flame_bush();
            bush_system.push_back(bush_tmp);
        }
    }
}

int bushsystem::give_bush_near_house_num()
{
    return bush_near_house;
}

void bushsystem::update_bushes(bool move_left)
{
    for(int i = 0;  i < (int)bush_system.size(); i++)
    {
        bush_system[i].update_position(move_left);
    }
}

void bushsystem::health_bush()
{
    for(int i = 0; i < (int)bush_system.size(); i++)
    {
        bush_system[i].lose_health();
    }
}

void bushsystem::spread_flame_bushes()
{
    for(int i = 0; i < (int)bush_system.size(); i++)
    {
        for(int j = 0; j < (int)bush_system[i].flame_points.size(); j++) if(bush_system[i].flame_points[j].be_burning() == false)
        {
            if(rand() % 10000 == 1808) bush_system[i].flame_points[j].sudden_flame();
            else for(int I = i - 1; I <= i + 1; I++)
            {
                for(int J = 0; J < (int)bush_system[I].flame_points.size(); J++)
                {
                    bush_system[i].flame_points[j].receive_flame(bush_system[I].flame_points[J]);
                }
            }
        }
    }
}

void bushsystem::render_bushes(SDL_Renderer* renderer, SDL_Texture* flame_img[])
{
    for(int i = 0;  i < (int)bush_system.size(); i += 3)
    {
        bush_system[i].render_bush(renderer);
        bush_system[i].render_flame_bush(renderer, flame_img);
    }
    for(int i = 1; i < (int)bush_system.size(); i += 3)
    {
        bush_system[i].render_bush(renderer);
        bush_system[i].render_flame_bush(renderer, flame_img);
    }
    for(int i = 2; i < (int)bush_system.size(); i += 3)
    {
        bush_system[i].render_bush(renderer);
        bush_system[i].render_flame_bush(renderer, flame_img);
    }
}

bool bushsystem::lose()
{
    for(int i = 0; i < (int)bush_system.size(); i++)
    {
        if(bush_system[i].is_dead == false) return false;
    }
    return true;
}

bool bushsystem::win(int &survive_bush)
{
    int count = 0;
    for(int i = 0; i < (int)bush_system.size(); i++) if(bush_system[i].is_dead == false)
    {
        count++;
        for(int j = 0; j < (int)bush_system[i].flame_points.size(); j++)
        {
            if(bush_system[i].flame_points[j].be_burning()) return false;
        }
    }
    if(count > 0)
    {
        return true;
        survive_bush = count;    
    }
    else return false;
}
