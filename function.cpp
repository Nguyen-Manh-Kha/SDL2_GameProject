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

SDL_Texture* load_texture_with_transparent_background(SDL_Renderer* renderer, const char* image_file)
{
    SDL_Surface* surface = IMG_Load(image_file);
    if(surface == NULL)
    {
        cout << SDL_GetError();
        return 0;
    }
/// make the white background transparent
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

/// the remaining parts
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
