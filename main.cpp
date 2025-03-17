#define SDL_MAIN_HANDLED

#include "function.h"
#include "background.h"
#include "particlesystem.h"

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

    SDL_Rect background_rect;
    background_rect.y = 0;
    background_rect.w = WINDOW_WIDTH;
    background_rect.h = WINDOW_HEIGHT;

/// particle setup
    particle_system P;
    double particle_x, particle_y, particle_angle;

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

    bool move_left = false;
    bool move_right = false;
    bool move_up = false;

    int frame_num = 1;

    const SDL_Rect character_rect = {572, 488, 256, 288};

    // control character frame-rate independently
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

        // handle key press
        if(key_press[SDLK_LEFT] && key_press[SDLK_UP])
        {
            moving_background(0, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_left = true; move_up = true; move_right = false;
            particle_x = 640;
            particle_y = 565;
            particle_angle = 120;
        }

        else if(key_press[SDLK_RIGHT] && key_press[SDLK_UP])
        {
            moving_background(1, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_right = true; move_up = true; move_left = false;
            particle_x = 758;
            particle_y = 565;
            particle_angle = 60;
        }

        else if(key_press[SDLK_LEFT])
        {
            moving_background(0, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_left = true; move_up = false; move_right = false;
            particle_x = 630;
            particle_y = 635;
            particle_angle = 180;
        }

        else if(key_press[SDLK_RIGHT])
        {
            moving_background(1, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_right = true; move_up = false; move_left = false;
            particle_x = 767;
            particle_y = 635;
            particle_angle = 0;
        }

        if(key_press[SDLK_a])
        {
            P.add_particle(particle_x, particle_y, particle_angle);
        }

/// render everything
    //  clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

    // render background
        background_rect.x = bg1_position_x;
        SDL_RenderCopy(renderer, background1, NULL, &background_rect);
        background_rect.x = bg2_position_x;
        SDL_RenderCopy(renderer, background2, NULL, &background_rect);
    
    // render water shooting
    P.render_particle(renderer);

    // render character
        if(move_up)
        {
            if(move_left) SDL_RenderCopy(renderer, up_character_left[frame_num], NULL, &character_rect);
            else if(move_right) SDL_RenderCopy(renderer, up_character_right[frame_num], NULL, &character_rect);
        }
        else if(move_left) SDL_RenderCopy(renderer, basic_character_left[frame_num], NULL, &character_rect);
        else SDL_RenderCopy(renderer, basic_character_right[frame_num], NULL, &character_rect);

    // present
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

/// Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(background1);
    SDL_DestroyTexture(background2);
    for(int i = 1; i <= 3; i++)
    {
        SDL_DestroyTexture(basic_character_left[i]);
        SDL_DestroyTexture(basic_character_right[i]);
        SDL_DestroyTexture(up_character_left[i]);
        SDL_DestroyTexture(up_character_right[i]);
    }
    SDL_Quit();
    IMG_Quit();
    return 0;
}
