# Time log

> 21:15, 2023-07-07
Starting up with the logo at the front of the game.
I don't want to miss it this time.

> 22:20
Created GMTK logo pop-up at startup.
Leaving some part of the startup for later
Going to plan some tasks

> 22:30
Pause

> 22:35
Going to plan the level structure.
I kind of want it to not be size-limited.
Instead it should be endless in any direction.
The player should be able to see nearby areas
 so that they can plan the Hero's path.

I think i want some kind of structure that
 behave as endless tile map and uses some
 internal compression & area generation.
Areas that get too far should as well be cleaned.
A good idea would be to introduce collapsing rooms/corridors. (And rooms & corridors as structures)

Corridors will be what players create to play.

> 22:40
Adding Camera



# Utility
- [x] Graphic loading
    - [ ] Resource management
- [ ] Text rendering
- [ ] Add SDL_mixer to the engine to add sound


# Startup
- [x] Add GMTK logo on startup
- [ ] Add theme in startup
- [ ] Prepare a dialogue in startup


# Menu
- [ ] Plan menu
    - [ ] Credits
    - [ ] Settings?


# Gameplay
- [x] Camera
    - [x] Store center for easier zoom
    - [ ] Test Camera::apply

- [ ] Level
    - [ ] Generation of areas
    - [ ] Editing
        - [ ] User interface
        - [ ] Time control


- [ ] Treasures
    - [ ] Weapons
    - [ ] Money/Loot
    - [ ] Resources

- [ ] Hero
    - [ ] Stats
    - [ ] Behavior

- [ ] Enemies
    - [ ] Stats/Types
    - [ ] Behavior


