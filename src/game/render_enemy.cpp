#include "game/render.hpp"
#include "game/enemy.hpp"
#include "game/tile.hpp"
#include "game/camera.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::render_enemy(Enemy const* _enemy)
{
    if(_enemy == nullptr)
        return;

    Enemy const& enemy = *_enemy;

    SDL_Rect dest {
        static_cast<int>
            (enemy.pos.x * tile_size.x
                + enemy.animation_pos.x + 2),
        static_cast<int>
            (enemy.pos.y * tile_size.y
                + enemy.animation_pos.y + 2),
        28, 28
    };

    camera().apply(dest);

    SDL_SetRenderDrawColor(rnd, 255, 0, 0, 255);

    SDL_RenderFillRect(rnd, &dest);
}

