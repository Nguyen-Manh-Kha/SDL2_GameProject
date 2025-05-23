Source code and game explain: https://drive.google.com/file/d/142EJHM-Ginjbtvt7xCuvjOrfT-wpx6C9/view?usp=sharing

Credit: Great thanks to Đinh Quang Minh - k69-I-CS8 for helping me design game menu

Explain game lore and game idea:

  You are just a normal forest ranger but one day, the fire suddenly started in the forest. You have no other choice but to become a firefighter to save the forest. Fortunately, You already have the exact tools for that mission, a protective suit that can protect you from the fire for a certain period of time, a water gun connected with a portable water tank
  In this game, you have to move around to put out the fire while also protecting your house and the water well at the same time

Game's main features:
  - Movement: LEFT_KEY and RIGHT_KEY only, no jumping (game logic)
  - Water shooting: (using PARTICLE EFFECT)
    + Press A_KEY to spray water to put out fire, the water gun points left or right as you move
    + Press UP_KEY to point water gun upwards
  - Water refill: stay near water well and hold R_KEY to refill water
  - World generation: (forest context)
    + Generate random trees and bushes, each has many different flame points(fire mechanism)
    + The house and the water well will spawn somewhere in the middle of the forest
    + The character will spawn at the house as the game starts
  - Fire mechanism:
    + When the game starts, there are random flame points in the forest
    + Then the fire will continue to spread to other points in the forest
  - House and water well: a fixed point, act as something you have to protect, not just running around and put out fire without worrying about anything else
  - Character status:
    + Health bar: The character will not lose health immediately by contacts with fire (the protective suit/ game logic), but when stays near fire for a certain amount of time, the character will eventually catch fire, the fire will disappear after a short amount of time, but your character will lose a portion of health and water as a penalty
    + Water bar: Decrease as your character sprays water or catches fire, increase as your character refills water near the well
  - Ending scenarios:
    + Win: Put out all fire in the forest, save atleast 30% of the forest, successfully protect the house and the water well, your character survives
    + Lose: More than 70% of the forest is burned down // The fire destroys the house or the water well // Your character does not survive

Code summarize:
  - background.cpp: scroll background with 2 images using parallax scrolling ( youtube link in progression note below)
  - function.cpp: basic functions only ( init SDL, SDL_image; load texture; change character sprites)
  - particlesystem.cpp: water spraying mechanism using particle effect (Learning from lazy fool)
  - treesystem.cpp: main world generation; contains flame class, tree class, bush class, treesystem class, bushsystem class
  - home.cpp: create house and water well (object quite similar to tree class)
  - character_status.cpp: health bar and water bar management
  - main.cpp: initializing; create window, renderer, load textures, set up world and player, menu and game states management, control key input, run the game with other .cpp file

Progression note

11/3/2025:
  - Create moving background with 2 background images in a loop ( background.cpp file )
    + The main idea of the code is using a term called " Parallax scrolling "
    + The background moves accordingly to KEY_LEFT and KEY_RIGHT
    + "Parallax scrolling" learning video: https://www.youtube.com/watch?v=VHMjJ9v--EM
    + Background image source: https://www.youtube.com/watch?v=Ic3ZdD5ko7k
  - Add 2 basic functions in "function.cpp" file : initializing() and load_texture()
    
12/3/2025:
  - Create 2 redesinged character sprites ( 2 basic poses left and right ) from an existing character model
      + The character model source: https://www.shutterstock.com/vi/image-vector/fireman-character-holding-fire-hose-firefighter-795518032
      + Tool used to design character model: https://www.piskelapp.com/
      + 2 character sprites ( will be more in the future) are located in "Character" folder
  - Render character with transparent background on the moving background (Using color keying)
  - Add another function to function.cpp: load_texture_with_transparent_background()
  - Make a small change to "background.cpp" code otherwise the character would move like Michael Jackson in the game

14/3/2025:
  - Finish designing all 12 character moving sprites
    + There are 4 main movement: left + up ; right + up ; left ; right
    + Each movement has 3 moving sprites
  - Finish the character moving animation
  - Add "update_character_frame" function to function.cpp file to control character frame independently using Uint32 GetTicks() otherwise the character sprites would change too fast 

17/3/2025:
  - Finish water spraying animation using particle effect
    + The particle system is a vector that consists of multiple particles
    + Each particle has its own size, color (mostly blue), speed, shooting angle, lifetime using rand()
    + Pressing KEY_A adds more particles to the particle system
    + Every frame, the particle system will check every single particle, update its position, check whether it's dead or not and remove dead ones, and render all the particles that sill exist
  - Make some small adjustments to other source files to adapt to new features

25/3/2025:
  - Create a forest system using tile map method( not really, the actual ingame idea is quite different )
    + "Tile map method" learning video: https://youtu.be/DNu8yUsxOnE?si=KisWBHMKdNmM_aYb
    + There is a total of 18 different tree models in "Trees" file
    + Each tree object has its own size, shape and location
    + The forest system is a vector that consist of all tree objects
    + Whenever the character moves, the forest system will update all trees position and render them
  - Working on bushes system, fire burning and spreading and burnt dead trees mechanism

31/3/2025:
  - Basically finish the forest system
    + There are a total of 18 different tree models in "Trees" file and 7 bush models in "Bush" file
    + The source of the tree and bush models: https://www.shutterstock.com/vi/image-vector/pixel-forest-jungle-trees-shrub-grass-2290404331
  - Add the flame system to the forest system
    + Class flame: each flame has its own location ( SDL Point ), burning state (using probability, the testing video is 100% burning, this is changeable depending on the final version of the game) and health
    + The source of the flame sprites: https://www.vecteezy.com/vector-art/23844301-fire-flame-pixel-art-animation-sprite-frames-8bit
    + Each tree, each bush has its own flame system which is a vector that consists of all flames and their state
    + Add a mechanism to the particle system: Every frame, the particle system will check if there is any particle that hits the hitbox of the flame, that particle will disappear and the health of the flame will decrease, the flame will also disappear if its health = 0
    + Every frame, the flame system will check every flame and render all the flame that still exist
    + Working on the speading mechanism of the flame ( the flame will spread to other flame points in the same tree/ bush and to the tree/ bush nearby )
    + Working on the trees/bushes' health and burned dead tree/ bush sprites

14/4/2025:
  - Add fire spreading mechanism:
    + The fire can spread betweens nearby flame points depending on the distance between them
    + If a flame point is not burning, only when there is at least 1 burning flame point nearby and only after a certain "spreading time" could the "not burning flame point" ignite
    + The more burning flame points nearby, the faster the "not burning flame point" ignites
    + The fire can spread betweens flame points in the same tree or the same bush, or betweens flame points of different nearby trees or bushes
  - Add another game content: besides putting out the fire to save the trees, player also has to also protect the wooden house and the well from being destroyed by the fire
    + Create class house and well in "home.cpp" file
    + The house and the well also have flame points, now the fire can spread between trees, bushesand and also house and well
    + Now you also lose the game if the house or the well is destroyed by the fire
  - Working on trees/bushes health and burned dead tree/ bush sprites
  - Working on player health bar and water bar
    + Player can also catch fire and lose health if the fire is too close
    + After a certain time of shooting water, player has to come back to the well to refill the water tank

26/4/2025: Basically finish the game
  - Create 18 burnt tree models and 7 burnt bush models based on 18 "living" tree models and 7 "livinng" bush models using https://www.piskelapp.com/
  - Add map barrier to the game
  - Add health system to trees, bushes, house and well
    + When the tree/bush's health drops to 0, its texture will become "burnt texture" and all the flame points of that tree/bush will disappear(which means that that burnt tree/bush can no longer catch fire and burn)
  - Add a character status system
    + The character status system consists of health status and water level status
    + Health status show how much health your character has
    + Water level status show how much water your character has in the water tank
    + When you shoot water, the water level will drop
    + To refill your water, you have to come back to the well and hold 'R' key to refill water
    + The character now can also catch fire if you stands too close to fire for a certain amount of time
    + When the character is on fire, the fire will eventually disappear after a few seconds thanks to the protective suit, but you will lose some health and some water as a penalty
    - There are totally 4 win-lose scenarios:
      (1) You only win if you put out all the fire and you save atleast 30% of the forest, you lose if you save less than 30% of the forest
      (2) You lose if your character'health drops to 0
      (3) You lose if the fire destroys your house or your well
      (4) You lose if the fire destroy all trees and bushes

27/4/2025:
  - Add the game menu
    + Design all game menu thanks to the help of Dinh Quang Minh - K69-I-CS8
    + Tools used to design:
      ~ https://www.photopea.com/
      ~ https://www.fontspace.com/akura-popo-font-f19216
  - Change some game stats to balance the game
