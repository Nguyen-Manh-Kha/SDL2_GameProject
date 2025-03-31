#define SDL_MAIN_HANDLED

#include "function.h"
#include "background.h"
#include "particlesystem.h"
#include "treesystem.h"

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
SDL_Texture* tree_texture[19]; // 18 tree models
SDL_Texture* bush_texture[8]; // 7 bush models
SDL_Texture* flame_img[9]; // 8 flame sprites
SDL_Texture* barrier[2]; // 2 barrier prites
SDL_Texture* house;
SDL_Texture* well;

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 750;

bool key_press[512]; // control key press state with no delay

int main(int argc, char* argv[])
{
    initializing();

    ///// create window and renderer
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

    ///// background setup
    background1 = load_texture(renderer, "background/background1.png");
    background2 = load_texture(renderer, "background/background2.png");
    double bg1_position_x = 0; // start position of background image 1
    double bg2_position_x = WINDOW_WIDTH; // start position of background image 2

    SDL_Rect background_rect;
    background_rect.y = 0;
    background_rect.w = WINDOW_WIDTH;
    background_rect.h = WINDOW_HEIGHT;

    ///// map barrier and house setup
    barrier[0] = NULL;
    barrier[1] = load_texture(renderer, "barrier/sign_left.png");
    barrier[2] = load_texture(renderer, "barrier/sign_right.png");
    SDL_Rect barrier_rect = {0, 507, 177, 216};

    house = load_texture(renderer, "house/house.png");
    well = load_texture(renderer, "house/well.png");
    SDL_Rect house_rect = {500, 101, 816, 622};
    SDL_Rect well_rect = {200, 547, 212, 176};

    ///// forest setup
    // trees
    tree_texture[0] = NULL;
    tree_texture[1] = load_texture(renderer, "Trees/tree_1.png");
    tree_texture[2] = load_texture(renderer, "Trees/tree_2.png");
    tree_texture[3] = load_texture(renderer, "Trees/tree_3.png");
    tree_texture[4] = load_texture(renderer, "Trees/tree_4.png");
    tree_texture[5] = load_texture(renderer, "Trees/tree_5.png");
    tree_texture[6] = load_texture(renderer, "Trees/tree_6.png");
    tree_texture[7] = load_texture(renderer, "Trees/tree_7.png");
    tree_texture[8] = load_texture(renderer, "Trees/tree_8.png");
    tree_texture[9] = load_texture(renderer, "Trees/tree_9.png");
    tree_texture[10] = load_texture(renderer, "Trees/tree_10.png");
    tree_texture[11] = load_texture(renderer, "Trees/tree_11.png");
    tree_texture[12] = load_texture(renderer, "Trees/tree_12.png");
    tree_texture[13] = load_texture(renderer, "Trees/tree_13.png");
    tree_texture[14] = load_texture(renderer, "Trees/tree_14.png");
    tree_texture[15] = load_texture(renderer, "Trees/tree_15.png");
    tree_texture[16] = load_texture(renderer, "Trees/tree_16.png");
    tree_texture[17] = load_texture(renderer, "Trees/tree_17.png");
    tree_texture[18] = load_texture(renderer, "Trees/tree_18.png");

    treesystem forest;
    forest.setup_tree(tree_texture);

    // bushes
    bush_texture[0] = NULL;
    bush_texture[1] = load_texture(renderer, "Bush/bush_1.png");
    bush_texture[2] = load_texture(renderer, "Bush/bush_2.png");
    bush_texture[3] = load_texture(renderer, "Bush/bush_3.png");
    bush_texture[4] = load_texture(renderer, "Bush/bush_4.png");
    bush_texture[5] = load_texture(renderer, "Bush/bush_5.png");
    bush_texture[6] = load_texture(renderer, "Bush/bush_6.png");
    bush_texture[7] = load_texture(renderer, "Bush/bush_7.png");

    bushsystem bushes;
    bushes.setup_bush(bush_texture);

    ///// flame sprites setup
    flame_img[0] = NULL;
    flame_img[1] = load_texture_with_transparent_background(renderer, "flame/flame1.png", 8, 8, 8);
    flame_img[2] = load_texture_with_transparent_background(renderer, "flame/flame2.png", 8, 8, 8);
    flame_img[3] = load_texture_with_transparent_background(renderer, "flame/flame3.png", 8, 8, 8);
    flame_img[4] = load_texture_with_transparent_background(renderer, "flame/flame4.png", 8, 8, 8);
    flame_img[5] = load_texture_with_transparent_background(renderer, "flame/flame5.png", 8, 8, 8);
    flame_img[6] = load_texture_with_transparent_background(renderer, "flame/flame6.png", 8, 8, 8);
    flame_img[7] = load_texture_with_transparent_background(renderer, "flame/flame7.png", 8, 8, 8);
    flame_img[8] = load_texture_with_transparent_background(renderer, "flame/flame8.png", 8, 8, 8);

    ///// particle setup
    particle_system P;
    double particle_x = 760, particle_y = 656, particle_angle = 0;

    ///// character setup
    basic_character_left[1] = load_texture_with_transparent_background(renderer, "Character/basic_character_left/Basic_Character_Left_1.png",255,255,255);
    basic_character_left[2] = load_texture_with_transparent_background(renderer, "Character/basic_character_left/Basic_Character_Left_2.png",255,255,255);
    basic_character_left[3] = load_texture_with_transparent_background(renderer, "Character/basic_character_left/Basic_Character_Left_3.png",255,255,255);
    basic_character_right[1] = load_texture_with_transparent_background(renderer, "Character/basic_character_right/Basic_Character_Right_1.png",255,255,255);
    basic_character_right[2] = load_texture_with_transparent_background(renderer, "Character/basic_character_right/Basic_Character_Right_2.png",255,255,255);
    basic_character_right[3] = load_texture_with_transparent_background(renderer, "Character/basic_character_right/Basic_Character_Right_3.png",255,255,255);
    up_character_left[1] = load_texture_with_transparent_background(renderer, "Character/up_character_left/Up_Character_Left_1.png",255,255,255);
    up_character_left[2] = load_texture_with_transparent_background(renderer, "Character/up_character_left/Up_Character_Left_2.png",255,255,255);
    up_character_left[3] = load_texture_with_transparent_background(renderer, "Character/up_character_left/Up_Character_Left_3.png",255,255,255);
    up_character_right[1] = load_texture_with_transparent_background(renderer, "Character/up_character_right/Up_Character_Right_1.png",255,255,255);
    up_character_right[2] = load_texture_with_transparent_background(renderer, "Character/up_character_right/Up_Character_Right_2.png",255,255,255);
    up_character_right[3] = load_texture_with_transparent_background(renderer, "Character/up_character_right/Up_Character_Right_3.png",255,255,255);

    bool move_left = false;
    bool move_right = false;
    bool move_up = false;

    int frame_num = 1;

    const SDL_Rect character_rect = {618, 547, 192, 216};

    // control character frame-rate independently
    Uint32 last_frame_time = SDL_GetTicks();
    const int CHARACTER_ANIMATION_DELAY = 200;
 
    // key state
    key_press[512] = {false};

    ///// main loop run
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
                key_press[e.key.keysym.scancode] = true;
            }

            if(e.type == SDL_KEYUP)
            {
                key_press[e.key.keysym.scancode] = false;
            }
        }

    ///// handle key press
        if(key_press[SDL_SCANCODE_LEFT] && key_press[SDL_SCANCODE_UP])
        {
            moving_background(0, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_left = true; move_up = true; move_right = false;
            forest.update_forest(move_left);
            bushes.update_bushes(move_left);
            particle_x = 667;
            particle_y = 604;
            particle_angle = 120;
        }

        else if(key_press[SDL_SCANCODE_RIGHT] && key_press[SDL_SCANCODE_UP])
        {
            moving_background(1, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_right = true; move_up = true; move_left = false;
            forest.update_forest(move_left);
            bushes.update_bushes(move_left);
            particle_x = 756;
            particle_y = 608;
            particle_angle = 60;
        }

        else if(key_press[SDL_SCANCODE_LEFT] && key_press[SDL_SCANCODE_UP] == false)
        {
            moving_background(0, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_left = true; move_up = false; move_right = false;
            forest.update_forest(move_left);
            bushes.update_bushes(move_left);
            particle_x = 659;
            particle_y = 655;
            particle_angle = 180;
        }

        else if(key_press[SDL_SCANCODE_RIGHT] && key_press[SDL_SCANCODE_UP] == false)
        {
            moving_background(1, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_frame_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_right = true; move_up = false; move_left = false;
            forest.update_forest(move_left);
            bushes.update_bushes(move_left);
            particle_x = 760;
            particle_y = 656;
            particle_angle = 0;
        }

        if(key_press[SDL_SCANCODE_A])
        {
            P.add_particle(particle_x, particle_y, particle_angle);
        }

    ///// render everything
    //  clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

    // render background
        background_rect.x = bg1_position_x;
        SDL_RenderCopy(renderer, background1, NULL, &background_rect);
        background_rect.x = bg2_position_x;
        SDL_RenderCopy(renderer, background2, NULL, &background_rect);
    
    // render tree_system
        forest.render_forest(renderer, flame_img);
        bushes.render_bushes(renderer, flame_img);

    // render barrier
        

    // render water shooting
        P.render_particle(renderer, forest, bushes);

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

    ///// Quit SDL
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
    for(int i = 1; i <= 18; i++)
    {
        SDL_DestroyTexture(tree_texture[i]);
    }
    for(int i = 1; i <= 8; i++)
    {
        SDL_DestroyTexture(flame_img[i]);
    }
    SDL_Quit();
    IMG_Quit();
    return 0;
}
