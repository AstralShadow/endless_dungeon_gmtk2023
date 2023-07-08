#include "game/game.hpp"
#include "game/mouse.hpp"
#include "game/camera.hpp"
#include "game/level.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

static enum {
    M_DRAGGING,
    M_ADD_GROUND,
    M_REMOVE_GROUND,
    M_NONE
} mode = M_NONE;


void game::
mousedown(SDL_MouseButtonEvent& ev, scene_uid)
{
    auto& camera = game::camera();
    auto& level = game::level();

    if(ev.button == SDL_BUTTON_LEFT) {
        if(click_time_control(ev))
            return;

        mode = M_ADD_GROUND;

        Point pos {ev.x, ev.y};
        camera.undo(pos);
        int x = pos.x >> 5;
        int y = pos.y >> 5;
        Tile current = level.at(x, y);
        if(current == default_tile())
            level.at(x, y) = path_tile();
    }

    if(ev.button == SDL_BUTTON_RIGHT) {
        mode = M_REMOVE_GROUND;

        Point pos {ev.x, ev.y};
        camera.undo(pos);
        int x = pos.x >> 5;
        int y = pos.y >> 5;
        Tile current = level.at(x, y);
        if(current == path_tile())
            level.at(x, y) = default_tile();
    }

    if(ev.button == SDL_BUTTON_MIDDLE) {
        mode = M_DRAGGING;
    }
}

void game::
mouseup(SDL_MouseButtonEvent& ev, scene_uid)
{
    mode = M_NONE;
}


void game::
mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    auto& camera = game::camera();
    auto& level = game::level();

    if(mode == M_DRAGGING) {
        // Dragging camera

        camera.mid.x -= ev.xrel / camera.zoom;
        camera.mid.y -= ev.yrel / camera.zoom;
    }

    if(mode == M_REMOVE_GROUND) {
        // Remove ground
        Point pos {ev.x, ev.y};
        camera.undo(pos);
        int x = pos.x >> 5;
        int y = pos.y >> 5;
        Tile current = level.at(x, y);
        if(current == path_tile())
            level.at(x, y) = default_tile();
    }

    if(mode == M_ADD_GROUND) {
        // Add ground
        Point pos {ev.x, ev.y};
        camera.undo(pos);
        int x = pos.x >> 5;
        int y = pos.y >> 5;
        Tile current = level.at(x, y);
        if(current == default_tile())
            level.at(x, y) = path_tile();
    }
}


void game::
mouse_wheel(SDL_MouseWheelEvent& ev, scene_uid)
{
    auto& camera = game::camera();

    Point m_pos;
    SDL_GetMouseState(&m_pos.x, &m_pos.y);

    camera.zoom += ev.y * 0.15f;

    if(camera.zoom < 0.3)
        camera.zoom = 0.3;

    if(camera.zoom > 2.5)
        camera.zoom = 2.5;
}

