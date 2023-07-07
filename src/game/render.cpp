#include "game/render.hpp"
#include "game/game.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void game::render(scene_uid)
{
    SDL_RenderClear(rnd);

    render_map_before(0);
    render_map_between(0, 100);
    render_map_after(100);

    SDL_RenderPresent(rnd);
}
