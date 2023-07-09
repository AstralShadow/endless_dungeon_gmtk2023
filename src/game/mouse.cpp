#include "game/game.hpp"
#include "game/mouse.hpp"
#include "game/camera.hpp"
#include "game/level.hpp"
#include "game/hints.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <cmath>

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

        if(progress_intro_hints())
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
mouseup(SDL_MouseButtonEvent&, scene_uid)
{
    mode = M_NONE;
}


void game::
mouse_motion(SDL_MouseMotionEvent& ev, scene_uid)
{
    auto& camera = game::camera();

    if(mode == M_DRAGGING) {
        // Dragging camera

        camera.mid.x -= ev.xrel / camera.zoom;
        camera.mid.y -= ev.yrel / camera.zoom;
        return;
    }
    static Point last = {0, 0};


    if(mode == M_ADD_GROUND || mode == M_REMOVE_GROUND)
    {
        Point delta {
            ev.x - last.x,
            ev.y - last.y
        };

        if(std::abs(delta.x) > tile_size.x
            || std::abs(delta.y) > tile_size.y)
        {
            place_tile(last.x + delta.x / 2,
                       last.y + delta.y / 2);
        }

        place_tile(ev.x, ev.y);
    }

    last = {ev.x, ev.y};
}

void game::
place_tile(int x, int y)
{
    auto& camera = game::camera();
    auto& level = game::level();

    if(mode == M_REMOVE_GROUND) {
        // Remove ground
        Point pos {x, y};
        camera.undo(pos);
        int x = pos.x >> 5;
        int y = pos.y >> 5;
        Tile current = level.at(x, y);
        if(current == path_tile())
            level.at(x, y) = default_tile();
    }

    if(mode == M_ADD_GROUND) {
        // Add ground
        Point pos {x, y};
        camera.undo(pos);
        int x = pos.x >> 5;
        int y = pos.y >> 5;
        Tile current = level.at(x, y);
        if(current == default_tile()) {
            level.at(x, y) = path_tile();
            Point neighbours[] = {
                {x + 1, y},
                {x - 1, y},
                {x, y + 1},
                {x, y - 1}
            };
            Point common[] = {
                {x + 1, y + 1}, {x + 1, y - 1},
                {x - 1, y + 1}, {x - 1, y - 1},
                {x + 1, y + 1}, {x + 1, y + 1},
                {x - 1, y - 1}, {x - 1, y - 1}
            };

            bool not_connected = true;
            for(int i = 0; i < 4; i++) {
                Tile neighbour =
                    level.at(neighbours[i]);
                if(neighbour != default_tile())
                    not_connected = false;
            }

            if(not_connected)
            for(int i = 0; i < 4; i++) {
                Tile t1 = level.at(common[2 * i]);
                Tile t2 = level.at(common[2 * i + 1]);
                if(t1 != default_tile()) {
                    level.at(neighbours[i])
                        = path_tile();
                    break;
                }
                if(t2 != default_tile()) {
                    level.at(neighbours[i])
                        = path_tile();
                    break;
                }
            }
            
        }
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

