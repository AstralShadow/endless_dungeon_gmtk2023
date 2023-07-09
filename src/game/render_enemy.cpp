#include "game/render.hpp"
#include "game/enemy.hpp"
#include "game/tile.hpp"
#include "game/camera.hpp"
#include "utils/textures.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace game
{
    static void render_enemy_walking(Enemy const&);
}

void game::render_enemy(Enemy const* _enemy)
{
    if(_enemy == nullptr)
        return;

    Enemy const& enemy = *_enemy;
    render_enemy_walking(enemy);
}

/**
 * The player texture looks like 2 lines with 4 frames.
 * Lines: left, right
 * Every sprite is 64x128
 */
void game::render_enemy_walking(Enemy const& enemy)
{
    static SDL_Texture* texture1 = utils::
        load_texture("assets/ghost-walk.png");
    static SDL_Texture* texture2 = utils::
        load_texture("assets/goblin-walk.png");

    SDL_Rect tile_area {
        static_cast<int>
            (enemy.pos.x * tile_size.x
                + enemy.animation_pos.x),
        static_cast<int>
            (enemy.pos.y * tile_size.y
                + enemy.animation_pos.y),
        tile_size.x,
        tile_size.y
    };

    SDL_Rect dest = tile_area;
    dest.y -= tile_size.y;
    dest.h += tile_size.y;

    SDL_Texture* texture;
    switch(enemy.type) {
        case ET_GHOST:
            texture = texture1;
            break;
        case ET_GOBLIN:
            texture = texture2;
            break;
    }

    int direction = 0;

    if(enemy.animation_pos.x > 0)
        direction = 1;

    int frame = static_cast<int>(enemy.frame);

    SDL_Rect src {
        frame * 64,
        direction * 128,
        64, 128
    };

    camera().apply(dest);

    SDL_RenderCopy(rnd, texture, &src, &dest);
}

