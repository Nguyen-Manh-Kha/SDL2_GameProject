#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

void initializing();

SDL_Texture* load_texture(SDL_Renderer*, const char*);

SDL_Texture* load_texture_with_transparent_background(SDL_Renderer*, const char*, int a, int b, int c);

void update_character_frame(Uint32 &last_frame_time, int &frame_num, const int CHARACTER_ANIMATION_DELAY);

#endif
