#include "game/render.hpp"
#include "core/core.hpp"
#include "game/camera.hpp"
#include "game/level.hpp"
#include "utils/screen.hpp"
#include "utils/textures.hpp"
#include "utils/trandom.hpp"
#include "game/fonts.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <map>

using std::string;
using utils::load_texture;
using utils::create_texture;

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

    // Using some prime numbers to hash
    int hash = hash_extra + x * 7 + y * 5;

    SDL_Rect src {
        64 * ((hash / 4) & 0x3),
        64 * (((hash % 3) + 3) % 3),
        64, 64
    };

    SDL_FRect dest {
        static_cast<float>(x * 32),
        static_cast<float>(y * 32),
        32, 32
    };

    camera().apply(dest);

    SDL_RenderCopyF(rnd, tex, &src, &dest);


#ifdef RENDER_EXTRA_INFO

    /* Displaying Dijkstra values */

    int value = tile.interest_path;

    if(value > 0xff)
        return;

    SDL_Rect area {
        static_cast<int>(dest.x),
        static_cast<int>(dest.y),
        0, 0
    };


    struct CacheEntry {
        SDL_Texture* ptr;
        SDL_Point size;
    };
    static std::map<int, CacheEntry> text_cache;
    SDL_Texture* text_texture = nullptr;

    auto itr = text_cache.find(value);
    if(itr != text_cache.end()) {
        text_texture = itr->second.ptr;
        area.w = itr->second.size.x;
        area.h = itr->second.size.y;
    } else {
        auto font = get_font(FT_DEBUG);
        string text = std::to_string(value);
        SDL_Color color {255, 255, 255, 255};

        auto surface = TTF_RenderUTF8_Blended
            (font, text.c_str(), color);
        if(!surface) {
            cout << "Failed to render text." << endl;
            cout << TTF_GetError() << endl;
            return;
        }

        auto text_texture = create_texture(surface);

        SDL_Point text_size {
            surface->w,
            surface->h
        };
        area.w = text_size.x;
        area.h = text_size.y;

        SDL_FreeSurface(surface);
        if(!text_texture)
            return;

        text_cache[value] = {
            text_texture,
            text_size
        };
    }

    SDL_RenderCopy(rnd, text_texture, nullptr, &area);
#endif
}


void game::render_tile_border(int, int)
{
    // TODO render_tile_border: implement
}

