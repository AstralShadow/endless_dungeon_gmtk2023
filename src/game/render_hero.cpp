#include "game/render.hpp"
#include "game/hero.hpp"
#include "game/tile.hpp"
#include "game/camera.hpp"
#include "utils/textures.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace game
{
    static void render_hero_walking();
}


void game::render_hero()
{
    render_hero_walking();
}


/**
 * The player texture looks like 4 lines with 4 frames.
 * Lines: left, right, up, down.
 * Every sprite is 64x128
 */
void game::render_hero_walking()
{
    static SDL_Texture* texture
        = utils::load_texture("assets/player-walk.png");


    auto const& hero = game::hero();
    SDL_Rect tile_area {
        static_cast<int>
            (hero.pos.x * tile_size.x
                + hero.animation_pos.x),
        static_cast<int>
            (hero.pos.y * tile_size.y
                + hero.animation_pos.y),
        tile_size.x,
        tile_size.y
    };

    SDL_Rect dest = tile_area;
    dest.y -= tile_size.y;
    dest.h += tile_size.y;


    int direction = 0;

    if(hero.animation_pos.x < 0)
        direction = 0;
    else if(hero.animation_pos.x > 0)
        direction = 1;
    else if(hero.animation_pos.y > 0)
        direction = 3;
    else if(hero.animation_pos.y < 0)
        direction = 2;


    int frame = static_cast<int>(hero.frame);

    SDL_Rect src {
        frame * 64,
        direction * 128,
        64, 128
    };

    camera().apply(dest);

    SDL_RenderCopy(rnd, texture, &src, &dest);
}

