#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

void moving_background(int, int&, int&, SDL_Renderer*, SDL_Texture*, SDL_Texture*, const int, const int);

#endif