Explaining game idea:
  - You are a normal forest ranger but one day, the fire suddenly breaks out in the forest and you have no other choice but to become a fire-fighter to save the forest
  - You are equipped with a small water tank to keep water and a water gun to put out fire
    + The water animation will be built by using particle effect
    + After a certain amount of time of spraying water, you will have to get to a point ( a lake / a well ? ) to recharge
  - Thanks to the advance of technology, you are also equipped with a protective suit that can protect you from the fire, the suit along with the heavy water tank means that you cannot jump, but you are completely fire-proof, but the trees aren't, so you better save them before they burn down
  - The trees, the burning effect and how the fire spreads (on progress and will be updated)
    
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
  - Create a forest system using tile map method
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
