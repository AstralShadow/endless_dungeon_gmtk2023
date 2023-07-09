#include "game/render.hpp"
#include "game/game.hpp"
#include "game/hero.hpp"
#include "game/tick.hpp"
#include "game/hints.hpp"
#include "utils/textures.hpp"
#include "utils/screen.hpp"
#include <string>

using std::string;

namespace game
{
    void render_ui_bars();
    void render_ui_time_controls();
}


static const string
time_controls_bg_path = "assets/time_controls_gray.png";
static const string
time_controls_path = "assets/time_controls_green.png";


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

static const string bars[BAR_INDEX_LAST + 1] {
    "assets/health_bar.png",
    "assets/health_bar_empty.png",

    "assets/stamina_bar.png",
    "assets/stamina_bar_empty.png",

    "assets/xp_bar.png",
    "assets/xp_bar_empty.png",

    "assets/bar_bg.png",
};

static SDL_Texture* textures[BAR_INDEX_LAST + 1];
static SDL_Point tex_size[BAR_INDEX_LAST + 1];


void game::render_ui_bars()
{
    [[maybe_unused]]
    static u8 _loaded = [](){
        for(int i = 0; i < BAR_INDEX_LAST + 1; ++i) {
            auto surf = utils::load_surface(bars[i]);
            if(!surf) {
                textures[i] = nullptr;
                tex_size[i] = {0, 0};
                continue;
            }
            tex_size[i] = {surf->w, surf->h};
            textures[i] = utils::create_texture(surf);
            SDL_FreeSurface(surf);
        }

        return 0;
    }();

    auto& hero = game::hero();
    auto screen = screen_size();


    /* Background */
    if(false) {
        int i_bg = BAR_INDEX_LAST;

        SDL_Rect bg_dest {
            static_cast<int>(screen.x * 0.025),
            static_cast<int>(screen.y * 0.015),
            static_cast<int>(screen.x * 0.45),
            static_cast<int>
                (screen.y * 0.05 + screen.x * 0.4
                 * tex_size[i_bg].y / tex_size[i_bg].x)
        }; // outdated

        SDL_RenderCopy(rnd, textures[i_bg],
                       nullptr, &bg_dest);
    }


    float values[BAR_INDEX_LAST / 2] {
        1.0f * hero.health / hero.max_health,
        1.0f * hero.stamina / hero.max_stamina,
        1.0f * hero.xp / hero.max_xp
    };

    SDL_Rect dest {
        static_cast<int>(screen.x * 0.05),
        static_cast<int>(screen.y * 0.05),
        0, 0
    };
    SDL_Rect src {
        0, 0, 0, 0
    };


    for(int i = 0; i < BAR_INDEX_LAST / 2; ++i)
    {
        auto bar = textures[i * 2];
        auto empty = textures[i * 2 + 1];
        auto size = tex_size[i * 2 + 1];
        auto value = values[i];

        src.w = size.x;
        src.h = size.y;
        dest.w = screen.x * 0.35;
        dest.h = dest.w * size.y / size.x;

        SDL_RenderCopy(rnd, empty, &src, &dest);

        src.w *= value;
        dest.w *= value;
        SDL_RenderCopy(rnd, bar, &src, &dest);

        dest.y += dest.h;
    }
}


void game::render_ui_time_controls()
{
    static Point size {0, 0};
    static SDL_Texture* texture = [](){
        auto surf = utils::
            load_surface(time_controls_path);
        if(!surf) {
            size = {0, 0};
            return static_cast<SDL_Texture*>(nullptr);
        }
        size = {surf->w * 4 / 5, surf->h};
        auto tex = utils::create_texture(surf);
        SDL_FreeSurface(surf);

        return tex;
    }();
    static SDL_Texture* background = utils
        ::load_texture(time_controls_bg_path);

    auto screen = screen_size();
    SDL_Rect dest {
        screen.x - 20,
        screen.y - 20,
        static_cast<int>(screen.x * 0.3),
        static_cast<int>(screen.x * 0.3)
            * size.y / size.x
    };
    dest.x -= dest.w;
    dest.y -= dest.h;
    SDL_Rect src { 0, 0, size.x, size.y };


    SDL_RenderCopy(rnd, background, &src,
                                 &dest);

    src.w /= 4;
    src.x = speed_mode * src.w;

    dest.w /= 4;
    dest.x += dest.w * speed_mode;

    SDL_RenderCopy(rnd, texture, &src, &dest);


}

void game::render_ui()
{
    if(get_hint(H_HERO_STATS).can_show_item())
        render_ui_bars();
    if(get_hint(H_TIME_CONTROL).can_show_item())
        render_ui_time_controls();
}
