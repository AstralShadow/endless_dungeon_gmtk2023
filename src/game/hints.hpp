#ifndef INCLUDE_GAME_HINTS_HPP
#define INCLUDE_GAME_HINTS_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

struct SDL_Texture;

namespace game
{
    enum HintPos : u8
    {
        TOP_LEFT,
        TOP_RIGHT,
        MID_LEFT,
        MID_CENTER,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    enum HintKey : u8
    {
        H_HELLO,
        H_LEVEL_DESIGN,

        H_PLAYER_ROLE,
        H_PLAYER_ROLE_2,
        H_PLAYER_ROLE_3,

        H_LEVEL,
        H_LEVEL_EDITING,
        H_LEVEL_MOVEMENT,

        H_HERO_STATS,
        H_FROZEN_HERO,
        H_FROZEN_HERO_2,
        H_TIME_CONTROL,
        H_TIME_CONTROL_2,

        H_INTRO_END,

        H_AREA_SPAWN,

        H_LAST
    };

    struct Hint
    {
        std::string text;
        HintPos pos = BOTTOM_LEFT;
        bool active = false;
        bool done = false;
        int lifetime = -800;

        bool can_show_item() {
            return active && lifetime > 200;
        }

        SDL_Texture* texture = nullptr;
        SDL_Rect area {0, 0, 0, 0};
    };

    vector<HintKey> active_hints();
    Hint& get_hint(HintKey);

    void activate_hint(HintKey);
    void render_hints();


    bool progress_intro_hints();

    extern int next_hint;
    const int last_intro_hint = H_INTRO_END;


    const int frame_dropdown_speed = 120; // px/s
    const int text_speed = 38; // characters/s
}

#endif // INCLUDE_GAME_HINTS_HPP
