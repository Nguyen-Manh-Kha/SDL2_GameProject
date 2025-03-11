#include "function.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

void initializing()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Could not init SDL" << SDL_GetError();
        return;
    }
    if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {
        cout << "Could not init SDL_image" << SDL_GetError();
        return;
    }
}

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* image_file)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, image_file);
    if(texture == NULL)
    {
        cout << "Could not create texture" << IMG_GetError();
        SDL_Quit();
        IMG_Quit();
        return 0;
    }
    return texture;
}