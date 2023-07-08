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

> 22:52
Adding Level

> 23:00
Decided to make Tile Wrapper

> 23:29
Decided to store tiles in chunks

> 00:00, 2023-07-08
Finished Level's Chunk and Tile Wrapper.
I haven't tested them tho.

> 00:45
Took some rest.
Adding spawn area.

> 00:55
Creating wall and floor texture formats.
Creating placeholder textures.

> 01:25
Described the texture format in `tasks_alaka.md`

> 01:50
Currently working on tile rendering.
I kind of realized i should've went for the prototype..

> 02:02
At least my textures are below prototype level :D

> 02:38
Rendering works.. I suppose.
Going to add camera controls on
 - [x] `WASD`
 - [x] arrows
 - [x] mid-mouse drag
 - [x] screen border (disabled)

> 03:40
Trying to fix bad scaling when zooming in.
Adding Camera::undo

> 03:48
Added last camera movement and disabled flag for it

> 03:59
Added camera scroll-to-zoom functionality.
I wanted it better (with respect to cursor position)
 but i don't want to waste time on this.

> 10:48
Took a nap from nearly 5am to now.
Rendering hero.

> 12:52
Currently working on Dijkstra maps inspired by:
<https://chizaruu.github.io/roguebasin/the_incredible_power_of_dijkstra_maps>

> 13:37
Working on map exploration (interest)

> 16:30
Dijkstra maps were hard to get right the first time.
Now they work.
I'll add Hero stats


# Utility
- [x] Graphic loading
    - [ ] Resource management
- [x] Text rendering
    - [x] Fonts
- [ ] Add SDL_mixer to the engine to add sound


# Startup
- [x] Add GMTK logo on startup
- [ ] Add theme in startup
- [ ] Prepare a dialogue in startup
- [ ] Add tutorial image


# Menu
- [ ] Plan menu
    - [ ] Credits
    - [ ] Settings?


# Gameplay
- [x] Camera
    - [x] Store center for easier zoom
    - [x] Movement controls
    - [x] Zoom controls
    - [x] Test Camera::apply

- [ ] Level
    - [x] Chunks
        - [ ] Move the world if position goes too high
            `524287/-524288` is the limit when using 32bit chunk position token (16bit per axis) and `16x16` tiles per chunk `2^16 * 16 = 1048576`
    - [x] Rendering level map
        - [ ] Assure border is properly rendered
    - [ ] Generation of areas
        - [x] Spawn area
    - [x] Editing
        - [x] User interface
        - [x] Time control


- [ ] Treasures
    - [ ] Weapons
    - [ ] Money/Loot
    - [ ] Resources

- [x] Hero
    - [x] Rendering
        - [ ] Rendering textures
    - [x] Movement
        - [x] Animation
    - [ ] Actions
        - [ ] Animation?
    - [x] Stats
    - [ ] Behavior

- [ ] Enemies
    - [ ] Stats/Types
    - [ ] Behavior


