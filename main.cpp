#define SDL_MAIN_HANDLED

#include "function.h"
#include "background.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

SDL_Window* window; // the main window
SDL_Renderer* renderer; // window renderer
SDL_Texture* background1; // background_1
SDL_Texture* background2; // background_2
SDL_Texture* character_left;
SDL_Texture* character_right;

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 750;

int main(int argc, char* argv[])
{
    initializing();

/// create window and renderer
    window = SDL_CreateWindow("SDL_Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(window == NULL)
    {
        cout << "Could not create window" << SDL_GetError();
        SDL_Quit();
        IMG_Quit();
        return 0;
    } 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        cout << "Could not create renderer" << SDL_GetError();
        SDL_Quit();
        IMG_Quit();
        return 0;
    }

/// background setup
    background1 = load_texture(renderer, "background/background1.png");
    background2 = load_texture(renderer, "background/background2.png");
    int bg1_position_x = 0; // start position of background image 1
    int bg2_position_x = WINDOW_WIDTH; // start position of background image 2

/// character setup
    character_left = load_texture_with_transparent_background(renderer, "Character/Basic_Character_Left.png");
    character_right = load_texture_with_transparent_background(renderer, "Character/Basic_Character_Right.png");
    const SDL_Rect character_position_rect = {572, 488, 256, 288};

/// main loop run
    bool run = true;
    SDL_Event e;
    while(run)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                run = false;
            }
            
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        moving_background(0, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
                        SDL_RenderCopy(renderer, character_left, NULL, &character_position_rect);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(16);
                        break;
                    case SDLK_RIGHT:
                        moving_background(1, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
                        SDL_RenderCopy(renderer, character_right, NULL, &character_position_rect);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(16);                      
                        break;
                }
            }
        }
        
    }

/// Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(background1);
    SDL_DestroyTexture(background2);
    SDL_Quit();
    IMG_Quit();
    return 0;
}
