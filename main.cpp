#define SDL_MAIN_HANDLED

#include "function.h"
#include "background.h"
#include "particlesystem.h"
#include "treesystem.h"
#include "home.h"
#include "character_status.h"

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
SDL_Texture* burnt_tree_texture[19]; // 18 burnt tree models
SDL_Texture* bush_texture[8]; // 7 bush models
SDL_Texture* burnt_bush_texture[8]; // 7 burnt bush models
SDL_Texture* flame_img[9]; // 8 flame sprites
SDL_Texture* barrier[3]; // 2 barrier prites
SDL_Texture* house_img;
SDL_Texture* well_img;
SDL_Texture* heart;
SDL_Texture* water;
SDL_Texture* menu;

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

    ///// map barrier and home setup
    barrier[0] = NULL;
    barrier[1] = load_texture(renderer, "barrier/sign_left.png");
    barrier[2] = load_texture(renderer, "barrier/sign_right.png");
    SDL_Rect barrier_rect = {-13000, 507, 177, 216};

    house_img = load_texture(renderer, "house/house.png");
    house House(house_img);
    House.set_up_flame_points();
    
    well_img = load_texture(renderer, "house/well.png");
    well Well(well_img);
    Well.set_up_flame_points();

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
    
    // burnt trees
    burnt_tree_texture[0] = NULL;
    burnt_tree_texture[1] = load_texture(renderer, "Burnt_tree/burnt_tree_1.png");
    burnt_tree_texture[2] = load_texture(renderer, "Burnt_tree/burnt_tree_2.png");
    burnt_tree_texture[3] = load_texture(renderer, "Burnt_tree/burnt_tree_3.png");
    burnt_tree_texture[4] = load_texture(renderer, "Burnt_tree/burnt_tree_4.png");
    burnt_tree_texture[5] = load_texture(renderer, "Burnt_tree/burnt_tree_5.png");
    burnt_tree_texture[6] = load_texture(renderer, "Burnt_tree/burnt_tree_6.png");
    burnt_tree_texture[7] = load_texture(renderer, "Burnt_tree/burnt_tree_7.png");
    burnt_tree_texture[8] = load_texture(renderer, "Burnt_tree/burnt_tree_8.png");
    burnt_tree_texture[9] = load_texture(renderer, "Burnt_tree/burnt_tree_9.png");
    burnt_tree_texture[10] = load_texture(renderer, "Burnt_tree/burnt_tree_10.png");
    burnt_tree_texture[11] = load_texture(renderer, "Burnt_tree/burnt_tree_11.png");
    burnt_tree_texture[12] = load_texture(renderer, "Burnt_tree/burnt_tree_12.png");
    burnt_tree_texture[13] = load_texture(renderer, "Burnt_tree/burnt_tree_13.png");
    burnt_tree_texture[14] = load_texture(renderer, "Burnt_tree/burnt_tree_14.png");
    burnt_tree_texture[15] = load_texture(renderer, "Burnt_tree/burnt_tree_15.png");
    burnt_tree_texture[16] = load_texture(renderer, "Burnt_tree/burnt_tree_16.png");
    burnt_tree_texture[17] = load_texture(renderer, "Burnt_tree/burnt_tree_17.png");
    burnt_tree_texture[18] = load_texture(renderer, "Burnt_tree/burnt_tree_18.png");

    treesystem forest;
    forest.setup_tree(tree_texture, burnt_tree_texture);

    // bushes
    bush_texture[0] = NULL;
    bush_texture[1] = load_texture(renderer, "Bush/bush_1.png");
    bush_texture[2] = load_texture(renderer, "Bush/bush_2.png");
    bush_texture[3] = load_texture(renderer, "Bush/bush_3.png");
    bush_texture[4] = load_texture(renderer, "Bush/bush_4.png");
    bush_texture[5] = load_texture(renderer, "Bush/bush_5.png");
    bush_texture[6] = load_texture(renderer, "Bush/bush_6.png");
    bush_texture[7] = load_texture(renderer, "Bush/bush_7.png");

    // burnt bushes
    burnt_bush_texture[0] = NULL;
    burnt_bush_texture[1] = load_texture(renderer, "Burnt_bush/burnt_bush_1.png");
    burnt_bush_texture[2] = load_texture(renderer, "Burnt_bush/burnt_bush_2.png");
    burnt_bush_texture[3] = load_texture(renderer, "Burnt_bush/burnt_bush_3.png");
    burnt_bush_texture[4] = load_texture(renderer, "Burnt_bush/burnt_bush_4.png");
    burnt_bush_texture[5] = load_texture(renderer, "Burnt_bush/burnt_bush_5.png");
    burnt_bush_texture[6] = load_texture(renderer, "Burnt_bush/burnt_bush_6.png");
    burnt_bush_texture[7] = load_texture(renderer, "Burnt_bush/burnt_bush_7.png");

    bushsystem bushes;
    bushes.setup_bush(bush_texture, burnt_bush_texture);

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
    
    heart = load_texture(renderer, "Character/heart.png");
    water = load_texture(renderer, "Character/h2o.png");

    status character_status(heart, water);
    int survive_tree = 0;
    int survive_bush = 0;

    bool move_left = false;
    bool move_right = false;
    bool move_up = false;

    int frame_num = 1;

    const SDL_Rect character_rect = {618, 547, 192, 216};

    // control character frame-rate independently
    Uint32 last_character_time = SDL_GetTicks();
    const int CHARACTER_ANIMATION_DELAY = 200;
    
    // control fire spread time
    Uint32 last_fire_time = SDL_GetTicks();

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

        Uint32 current_frame_time = SDL_GetTicks();
        if(current_frame_time - last_fire_time >= 200)
        {
            forest.spread_flame_forest();
            forest.health_tree();
            
            bushes.spread_flame_bushes();
            bushes.health_bush();
            
            House.spread_flame_house(forest, bushes);

            character_status.catch_fire(forest, bushes);
            character_status.on_fire();

            if(House.lose_health())
            {
                cout << "You lose" << endl << "The fire destroyed your house";
                run = false;
            }
            Well.spread_flame_well(bushes);
            if(Well.lose_health())
            {
                cout << "You lose" << endl << "The fire destroyed the well";
                run = false;
            }
            if(forest.lose() && bushes.lose())
            {
                cout << "You lose" << endl << "The fire destroyed the forest";
            }
            if(character_status.lose())
            {
                cout << "You lose" << endl << "You lost all your health. Beware of the fire";
            }
            if(forest.win(survive_tree) && bushes.win(survive_bush))
            {
                int percentage = (survive_tree + survive_bush) * 100 / (forest.tree_system.size() + bushes.bush_system.size());
                cout << "You win" << endl << "You saved " << percentage << '%' << " of the forest";
            }
            last_fire_time = current_frame_time;
        }

    ///// handle key press
        if(key_press[SDL_SCANCODE_LEFT] && barrier_rect.x <= 400)
        {
            moving_background(0, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_character_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_left = true; move_up = false; move_right = false;
            forest.update_forest(move_left);
            bushes.update_bushes(move_left);
            House.update_position(move_left);
            Well.update_position(move_left);
            barrier_rect.x += 5;
            particle_x = 659;
            particle_y = 655;
            particle_angle = 170;
        }

        else if(key_press[SDL_SCANCODE_RIGHT] && barrier_rect.x >= -27100)
        {
            moving_background(1, bg1_position_x, bg2_position_x, WINDOW_WIDTH, WINDOW_HEIGHT);
            update_character_frame(last_character_time, frame_num, CHARACTER_ANIMATION_DELAY);
            move_right = true; move_up = false; move_left = false;
            forest.update_forest(move_left);
            bushes.update_bushes(move_left);
            House.update_position(move_left);
            Well.update_position(move_left);
            barrier_rect.x -= 5;
            particle_x = 760;
            particle_y = 656;
            particle_angle = 10;
        }

        if(move_left && key_press[SDL_SCANCODE_UP])
        {
            move_left = true; move_right = false; move_up = true;
            particle_x = 667;
            particle_y = 604;
            particle_angle = 115;
        }

        else if(move_right && key_press[SDL_SCANCODE_UP])
        {
            move_left = false; move_right = true; move_up = true;
            particle_x = 756;
            particle_y = 608;
            particle_angle = 65;
        }

        if(key_press[SDL_SCANCODE_A] && character_status.not_empty_water())
        {
            P.add_particle(particle_x, particle_y, particle_angle);
            key_press[SDL_SCANCODE_R] = false;
            character_status.lose_water();
        }
        
        if(key_press[SDL_SCANCODE_R] && character_status.not_full_water() && Well.near_character())
        {
            key_press[SDL_SCANCODE_A] = false;
            character_status.refill_water();
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
    
    // render map barrier
        SDL_RenderCopy(renderer, barrier[1], NULL, &barrier_rect);
        barrier_rect.x += 28000;
        SDL_RenderCopy(renderer, barrier[2], NULL, &barrier_rect);
        barrier_rect.x -= 28000;

    // render home
        House.render_house(renderer, flame_img);
    
    // render tree_system
        forest.render_forest(renderer, flame_img);
        bushes.render_bushes(renderer, flame_img);

    // render well and barrier
        Well.render_well(renderer, flame_img);

    // render water shooting
        P.render_particle(renderer, forest, bushes, House, Well);

    // render character
        if(move_up)
        {
            if(move_left) SDL_RenderCopy(renderer, up_character_left[frame_num], NULL, &character_rect);
            else if(move_right) SDL_RenderCopy(renderer, up_character_right[frame_num], NULL, &character_rect);
        }
        else if(move_left) SDL_RenderCopy(renderer, basic_character_left[frame_num], NULL, &character_rect);
        else SDL_RenderCopy(renderer, basic_character_right[frame_num], NULL, &character_rect);

        character_status.render(renderer, flame_img);

    // present
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    ///// Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(background1);
    SDL_DestroyTexture(background2);
    SDL_DestroyTexture(house_img);
    SDL_DestroyTexture(well_img);
    for(int i = 1; i <= 18; i++)
    {
        SDL_DestroyTexture(tree_texture[i]);
        SDL_DestroyTexture(burnt_bush_texture[i]);
        if(i <= 8) SDL_DestroyTexture(flame_img[i]);
        if(i <= 7)
        {
            SDL_DestroyTexture(bush_texture[i]);
            SDL_DestroyTexture(burnt_bush_texture[i]);
        }
        if(i <= 3)
        {
            SDL_DestroyTexture(basic_character_left[i]);
            SDL_DestroyTexture(basic_character_right[i]);
            SDL_DestroyTexture(up_character_left[i]);
            SDL_DestroyTexture(up_character_right[i]);
        }
        if(i <= 2)
        {
            SDL_DestroyTexture(barrier[i]);
        }
    }
    SDL_Quit();
    IMG_Quit();
    return 0;
}
