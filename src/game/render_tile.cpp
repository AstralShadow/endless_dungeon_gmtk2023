#include "game/render.hpp"
#include "core/core.hpp"
#include "game/camera.hpp"
#include "game/level.hpp"
#include "utils/screen.hpp"
#include "utils/textures.hpp"
#include "utils/trandom.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

using std::string;
using utils::load_texture;

using std::cout;
using std::endl;

static auto& rnd = core::renderer;

static string wall_path = "assets/wall.png";
static string floor_path = "assets/floor.png";


void game::render_tile(int x, int y)
{
    static auto wall_tex = load_texture(wall_path);
    static auto floor_tex = load_texture(floor_path);
    struct RNG_Token;
    static int hash_extra = random<0x0000, 0xffff,
                                   RNG_Token>();

    Tile tile = level().at(x, y);
    SDL_Texture* tex = nullptr;

    switch(tile.type) {
        case Tile::T_WALL:
            tex = wall_tex;
            break;
        case Tile::T_GROUND:
        case Tile::T_PATH:
            tex = floor_tex;
            break;

        default:
            return;
    }

    // Using some big prime numbers to hash
    int hash = hash_extra + x * 7901 + y * 7919;

    SDL_Rect src {
        64 * ((hash / 4) & 0x3),
        64 * (((hash % 3) + 3) % 3),
        64, 64
    };

    SDL_FRect dest {
        x * 32,
        y * 32,
        32, 32
    };

    camera().apply(dest);

    SDL_RenderCopyF(rnd, tex, &src, &dest);
}


void game::render_tile_border(int, int)
{
    // TODO render_tile_border: implement
}

