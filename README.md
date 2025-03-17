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
    + The particle system is a vector consists of multiple particles
    + Each particle has its own size, color (mostly blue), speed, shooting angle, lifetime using rand()
    + Pressing KEY_A adds more particles to the particle system
    + Every frame, the particle system will check every single particle, update its position, check whether it's dead or not and remove dead ones, and render all the particles that sill exist
  - Make some small adjustments to other source files to adapt to new features
