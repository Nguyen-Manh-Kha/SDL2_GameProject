#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

void initializing();
SDL_Texture* load_texture(SDL_Renderer*, const char*);

#endif