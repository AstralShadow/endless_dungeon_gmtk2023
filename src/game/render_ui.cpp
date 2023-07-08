#include "game/render.hpp"
#include "game/game.hpp"
#include "core/core.hpp"
#include "game/hero.hpp"
#include "utils/textures.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_render.h>
#include <string>

using std::string;


static auto& rnd = core::renderer;

static const
string time_controls_path = "assets/time_controls.png";

enum BarIndex
{
    HP_BAR,
    HP_EMPTY,
    STAMINA_BAR,
    STAMINA_EMPTY,
    XP_BAR,
    XP_EMPTY,

    BAR_INDEX_LAST
};

static const string bars[BAR_INDEX_LAST] {
    "assets/health_bar.png",
    "assets/health_bar_empty.png",

    "assets/stamina_bar.png",
    "assets/stamina_bar_empty.png",

    "assets/xp_bar.png",
    "assets/xp_bar_empty.png",
};

static SDL_Texture* textures[BAR_INDEX_LAST];
static SDL_Point tex_size[BAR_INDEX_LAST];




void game::render_ui()
{
    [[maybe_unused]]
    static u8 _loaded = [](){
        for(int i = 0; i < BAR_INDEX_LAST; ++i) {
            auto surf = utils::load_surface(bars[i]);
            if(!surf) {
                textures[i] = nullptr;
                tex_size[i] = {0, 0};
                continue;
            }
            tex_size[i] = {surf->w, surf->h};
            textures[i] = utils::create_texture
                (surf);
            SDL_FreeSurface(surf);
        }

        return 0;
    }();


    auto& hero = game::hero();

    float values[BAR_INDEX_LAST / 2] {
        1.0f * hero.health / hero.max_health,
        1.0f * hero.stamina / hero.max_stamina,
        1.0f * hero.xp / hero.max_xp
    };

    SDL_Rect dest {
        20, 20,
        0, 0
    };
    SDL_Rect src {
        0, 0, 0, 0
    };

    auto screen = screen_size();

    for(int i = 0; i < BAR_INDEX_LAST / 2; ++i)
    {
        auto bar = textures[i * 2];
        auto empty = textures[i * 2 + 1];
        auto size = tex_size[i * 2 + 1];
        auto value = values[i];

        src.w = size.x;
        src.h = size.y;
        dest.w = screen.x * 0.4;
        dest.h = dest.w * size.y / size.x;

        SDL_RenderCopy(rnd, empty, &src, &dest);

        src.w *= value;
        dest.w *= value;
        SDL_RenderCopy(rnd, bar, &src, &dest);

        dest.y += dest.h;
    }
}

