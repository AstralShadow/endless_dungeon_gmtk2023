#include "game/render.hpp"
#include "game/game.hpp"
#include "core/core.hpp"
#include "game/hero.hpp"
#include "game/tile.hpp"
#include <SDL2/SDL_render.h>
#include <map>
#include <vector>

using std::vector;

static auto& rnd = core::renderer;


struct IndexEntry
{
    int y;
    enum {
        O_NULL,
        O_HERO,

        O_LAST
    } type = O_NULL;
};

typedef int y_t;
static std::map<y_t, vector<IndexEntry>> depth_order;


void game::render(scene_uid)
{
    SDL_RenderClear(rnd);

    depth_order.clear();

    auto hero = game::hero();
    depth_order[hero.pos.y]
        .push_back({
            hero.pos.y,
            IndexEntry::O_HERO
        });


    auto itr = depth_order.begin();
    auto itr_last = itr;
    render_map_before((itr->first + 1) * tile_size.y);

    while(itr != depth_order.end()) {
        for(auto entry : itr->second)
            switch(entry.type) {
                case IndexEntry::O_HERO:
                    render_hero();
                    break;

                default:
                    break;
            }

        auto y1 = (itr->first + 1) * tile_size.y;
        itr_last = itr;
        itr++;
        if(itr != depth_order.end()) {
            auto y2 = (itr->first + 1) * tile_size.y;
            render_map_between(y1, y2);
        }
    }

    render_map_after((itr_last->first + 1) * tile_size.y);

    SDL_RenderPresent(rnd);
}
