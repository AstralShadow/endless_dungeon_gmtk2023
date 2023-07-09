#include "game/render.hpp"
#include "game/camera.hpp"
#include "game/level.hpp"
#include "utils/screen.hpp"
#include "utils/textures.hpp"
#include "utils/trandom.hpp"
#include "game/fonts.hpp"
#include "game/level_generator.hpp"
#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL_timer.h>

using std::string;
using utils::load_texture;
using utils::create_texture;

using std::cout;
using std::endl;

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
    int hash2 = hash ^ SDL_GetTicks();

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

    if(spawning_process) {
        auto other = get_spawning_area_pos();
        Point delta = {
            other.x - x,
            other.y - y
        };

        int dist = sqrt(delta.x * delta.x
                       + delta.y * delta.y);

        if((dist + (SDL_GetTicks() / 80)) % 16 == 0)
        if(dist < 250 && (hash2 & 0x18) == 0x18) {
            float shake = (250 - dist) / 250.0f;
            if(hash2 & 4)
                shake *= 2;
            int shake_x = (hash2 & 1) ? shake
                                      : -shake;
            int shake_y = (hash2 & 2) ? shake
                                      : -shake;
            dest.x += shake_x;
            dest.y += shake_y;
        }
    }

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

