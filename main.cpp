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
    background1 = load_texture(renderer, "background/background1.png");
    background2 = load_texture(renderer, "background/background2.png");

/// main loop run
    int bg1_position_x = 0; // position of background image 1
    int bg2_position_x = WINDOW_WIDTH; // position of background image 2
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
                        moving_background(1, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
                        break;
                    case SDLK_RIGHT:
                        moving_background(0, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
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