#define SDL_MAIN_HANDLED

#include "function.h"
#include "background.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <map>

using namespace std;

SDL_Window* window; // the main window
SDL_Renderer* renderer; // window renderer
SDL_Texture* background1; // background_1
SDL_Texture* background2; // background_2
SDL_Texture* basic_character_left[4]; // 3 basic_left_moving_sprites
SDL_Texture* up_character_left[4]; // 3 up_left_moving_sprites
SDL_Texture* basic_character_right[4]; // 3 basic_left_moving_sprites
SDL_Texture* up_character_right[4]; // 3 up_right_moving_sprites

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 750;

map <SDL_Keycode, bool> key_press; // control key press state with no delay

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
    double bg1_position_x = 0; // start position of background image 1
    double bg2_position_x = WINDOW_WIDTH; // start position of background image 2

/// character setup
    basic_character_left[1] = load_texture_with_transparent_background(renderer, "Character/basic_character_left/Basic_Character_Left_1.png");
    basic_character_left[2] = load_texture_with_transparent_background(renderer, "Character/basic_character_left/Basic_Character_Left_2.png");
    basic_character_left[3] = load_texture_with_transparent_background(renderer, "Character/basic_character_left/Basic_Character_Left_3.png");
    basic_character_right[1] = load_texture_with_transparent_background(renderer, "Character/basic_character_right/Basic_Character_Right_1.png");
    basic_character_right[2] = load_texture_with_transparent_background(renderer, "Character/basic_character_right/Basic_Character_Right_2.png");
    basic_character_right[3] = load_texture_with_transparent_background(renderer, "Character/basic_character_right/Basic_Character_Right_3.png");
    up_character_left[1] = load_texture_with_transparent_background(renderer, "Character/up_character_left/Up_Character_Left_1.png");
    up_character_left[2] = load_texture_with_transparent_background(renderer, "Character/up_character_left/Up_Character_Left_2.png");
    up_character_left[3] = load_texture_with_transparent_background(renderer, "Character/up_character_left/Up_Character_Left_3.png");
    up_character_right[1] = load_texture_with_transparent_background(renderer, "Character/up_character_right/Up_Character_Right_1.png");
    up_character_right[2] = load_texture_with_transparent_background(renderer, "Character/up_character_right/Up_Character_Right_2.png");
    up_character_right[3] = load_texture_with_transparent_background(renderer, "Character/up_character_right/Up_Character_Right_3.png");

    int frame_num = 1;

    const SDL_Rect character_position_rect = {572, 488, 256, 288};

    // control character sprites framerate independently
    Uint32 last_frame_time = SDL_GetTicks();
    const int CHARACTER_ANIMATION_DELAY = 200;

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
                key_press[e.key.keysym.sym] = true;
            }

            if(e.type == SDL_KEYUP)
            {
                key_press[e.key.keysym.sym] = false;
            }
        }

        // control character framerate independently
        Uint32 current_time = SDL_GetTicks();
        if(current_time - last_frame_time > CHARACTER_ANIMATION_DELAY)
        {
            frame_num++;
            if(frame_num > 3) frame_num = 1;
            last_frame_time = current_time;
        }

        // handle key press
        if(key_press[SDLK_LEFT] && key_press[SDLK_UP])
        {
            moving_background(0, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
            SDL_RenderCopy(renderer, up_character_left[frame_num], NULL, &character_position_rect);
        }

        else if(key_press[SDLK_RIGHT] && key_press[SDLK_UP])
        {
            moving_background(1, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
            SDL_RenderCopy(renderer, up_character_right[frame_num], NULL, &character_position_rect);
        }

        else if(key_press[SDLK_LEFT])
        {
            moving_background(0, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
            SDL_RenderCopy(renderer, basic_character_left[frame_num], NULL, &character_position_rect);
        }

        else if(key_press[SDLK_RIGHT])
        {
            moving_background(1, bg1_position_x, bg2_position_x, renderer, background1, background2, WINDOW_WIDTH, WINDOW_HEIGHT);
            SDL_RenderCopy(renderer, basic_character_right[frame_num], NULL, &character_position_rect);
        }

        // render
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
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
