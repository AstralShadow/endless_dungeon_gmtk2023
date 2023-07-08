#include "game/game.hpp"
#include "game/camera.hpp"
#include <SDL2/SDL_events.h>


void game::
mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    if(ev.state & SDL_BUTTON_MMASK) {
        // Dragging camera

        auto& camera = game::camera();
        camera.mid.x -= ev.xrel / camera.zoom;
        camera.mid.y -= ev.yrel / camera.zoom;
    }
}

