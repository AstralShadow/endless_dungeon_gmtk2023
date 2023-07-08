#ifndef INCLUDE_GAME_GAME_HPP
#define INCLUDE_GAME_GAME_HPP

#include "utils/types.hpp"

struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseWheelEvent;

namespace game
{
    struct scene_uid_t;
    typedef struct scene_uid_t* scene_uid;

    void init(int, char**, scene_uid = 0);
    void deinit(scene_uid = 0);
    void tick(u32 ms, scene_uid = 0);
    void render(scene_uid = 0);
    
    void keydown(SDL_KeyboardEvent&, scene_uid = 0);
    void mouse_motion(SDL_MouseMotionEvent&,
                      scene_uid = 0);
    void mouse_wheel(SDL_MouseWheelEvent&,
                    scene_uid = 0);
}

#endif // INCLUDE_GAME_GAME_HPP
