#include "background.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


void moving_background(int left,double &bg1_position_x, double &bg2_position_x, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
    const double BG_MOVING_SPEED = 5;
    if(left == 1)
    {
    /// update new background images position
        bg1_position_x -= BG_MOVING_SPEED;
        bg2_position_x -= BG_MOVING_SPEED;

    /// reset background images position in case getting over boundary
        if(bg1_position_x <= -WINDOW_WIDTH)
        {
            bg1_position_x = WINDOW_WIDTH - BG_MOVING_SPEED;
        }
        if(bg2_position_x <= -WINDOW_WIDTH)
        {
            bg2_position_x = WINDOW_WIDTH - BG_MOVING_SPEED;
        }
    }
    else
    {
    /// update new background images position
        bg1_position_x += BG_MOVING_SPEED;
        bg2_position_x += BG_MOVING_SPEED;

    /// reset background image position in case getting over boundary
        if(bg1_position_x >= WINDOW_WIDTH)
        {
            bg1_position_x = -WINDOW_WIDTH + BG_MOVING_SPEED;
        }
        if(bg2_position_x >= WINDOW_WIDTH)
        {
            bg2_position_x = -WINDOW_WIDTH + BG_MOVING_SPEED;
        }
    }
}
