#include "background.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


void moving_background(int left,int &bg1_position_x, int &bg2_position_x, SDL_Renderer* renderer, SDL_Texture* background1, SDL_Texture* background2, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
    const int BG_MOVING_SPEED = 5;
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

/// render both images
    SDL_Rect window_rect;
    window_rect.x = bg1_position_x;
    window_rect.y = 0;
    window_rect.w = WINDOW_WIDTH;
    window_rect.h = WINDOW_HEIGHT;

    SDL_RenderClear(renderer);
    // render image 1
    SDL_RenderCopy(renderer, background1, NULL, &window_rect);
    
    // render image 2
    window_rect.x = bg2_position_x;
    SDL_RenderCopy(renderer, background2, NULL, &window_rect);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}