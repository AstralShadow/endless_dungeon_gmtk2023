#include "game/render.hpp"
#include "game/hero.hpp"
#include "game/tile.hpp"
#include "game/camera.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::render_hero()
{
    auto const& hero = game::hero();
    SDL_Rect dest {
        static_cast<int>
            (hero.pos.x * tile_size.x
                + hero.animation_pos.x + 2),
        static_cast<int>
            (hero.pos.y * tile_size.y
                + hero.animation_pos.y + 2),
        28, 28
    };

    camera().apply(dest);

    SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255);

    SDL_RenderFillRect(rnd, &dest);
}

