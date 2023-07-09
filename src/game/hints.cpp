#include "game/hints.hpp"
#include "game/render.hpp"
#include "game/fonts.hpp"
#include "utils/textures.hpp"
#include <iostream>

using std::cout;
using std::endl;

using game::HintKey;
using game::Hint;


namespace game {
    int next_hint = 0;

    static Hint _hints[H_LAST] {
        { // H_HELLO
            "Hello, Player!\n\n"
            "This game is unfinished.\n"
            "We didn't have anyone capable to do"
                " Level Design.\n\n"
            "Well, at least not in this time limit.\n"
            "              "
                "(Click to continue...)",
            MID_CENTER
        },
        { // H_LEVEL_DESIGN
            "Level Design is complex task.\n"
            "When designing a level you have to: \n\n"
            "Make sure the levels are not too hard.\n"
            "Make sure they are not too easy.\n"
            "Not too complex. Not too plain. \n"
            "Too short. Too long. Make them pretty...\n"
            "               ...and so on, and so on.\n\n"
            "TL;DR   Level Design is hard.",
            MID_CENTER
        },
        { // H_PLAYER_ROLE
            "Luckily, we found a loophole.\n"
            "The Jam theme is `ROLES REVERSED`.\n\n"
            "Guess who gets the Level Designer role.",
            MID_CENTER
        },
        { // H_PLAYER_ROLE_2
            "You get to be the Level Designer! :D",
            MID_CENTER
        },
        { // H_PLAYER_ROLE_3
            "Now, don't be Hasty.\n"
            "We'll have to take away"
                " your role as the Player.\n"
            "That's how reversing roles works.",
            MID_CENTER
        },

        { // H_LEVEL
            "Here's your Level Editor.\n"
            "I already put the Hero inside.\n"
            "Now, the crash course on using the editor.",
            BOTTOM_LEFT
        },

        { // H_LEVEL_EDITING
            "Currently the level is mostly made"
                " of walls.\n"
            "You can remove the walls with"
                " [Left Mouse Button]\n"
            "You can add new walls with"
                " [Right Mouse Button]\n\n"
            "This only works on not-special tiles.",
            BOTTOM_LEFT
        },

        { // H_LEVEL_MOVEMENT
            "You can move the screen by\n"
            "dragging the [Middle Mouse Button].\n"
            "You can also do so with"
                " [WASD] or the [Arrow keys]\n\n"
            "You can also Zoom with the scroll.",
            BOTTOM_LEFT
        },

        { // H_HERO_STATS
            "At the top left are the Hero's stats.\n"
            "They represent his "
                "Health, Stamina and Experience.",
            MID_LEFT
        },
        { // H_FROZEN_HERO
            "Uh.. the Hero's not moving tho.",
            BOTTOM_RIGHT
        },
        { // H_FROZEN_HERO_2
            "Let me check. . . .\n"
            "                   \n"
            "        ... Ah, yes\n",
            BOTTOM_RIGHT
        },
        { // H_TIME_CONTROL
            "I forgot to tell you.\n"
            "You can control game speed from here.",
            BOTTOM_RIGHT
        },
        { // H_TIME_CONTROL_2
            "I'll set it to normal for you.",
            BOTTOM_RIGHT
        },

        { // H_INTRO_END
            "I recommend you explore a bit and"
            " aid the Hero.\n"
            "He's pretty smart for a bot made by me.",
            BOTTOM_LEFT
        },


        { // H_AREA_SPAWN
            "Did you feel that?\n"
            "I think there was an earthquake.\n"
            "You should zoom out and look around.",
            BOTTOM_LEFT
        },

        { // H_MOVING_ENEMY
            "These pests started moving faster.",
            BOTTOM_RIGHT
        },


        { // H_GAME_OVER_1
            "OH NOOO!!!   The hero died. :(\n\n"
            "You still have to design the level.\n"
            "I'll revive him just this time.",
            MID_CENTER
        },
        { // H_GAME_OVER_2
            "Why did you let him die again?\n"
            "Please, don't repeat this.",
            MID_CENTER
        },
        { // H_GAME_OVER_3
            "Ok, ok, he got a lot of lives.\n"
            "Happy now? Please, stop killing him.",
            MID_CENTER
        },
        { // H_GAME_OVER_LOOP
            ". . .",
            MID_CENTER
        },
        { //H_GAME_OVER_END
            "That's it. I can't stand watching this.\n"
            "                                       \n"
            "            You're FIRED!              \n"
            "                                       ",
            MID_CENTER
        }
    };
}

vector<HintKey> game::active_hints()
{
    vector<HintKey> active;
    for(int key = 0; key < H_LAST; key++)
        if(_hints[key].active && !_hints[key].done)
            active.push_back(static_cast<HintKey>(key));

    return active;
}


Hint& game::get_hint(HintKey key)
{
    return _hints[key];
}


void game::activate_hint(HintKey key)
{
    using utils::create_texture;

    if(!_hints[key].done && !_hints[key].active) {
        _hints[key].active = true;

        auto font = get_font(FT_DEFAULT);
        SDL_Color color {255, 255, 255, 255};

        auto surf = TTF_RenderUTF8_Blended_Wrapped
            (font, _hints[key].text.c_str(), color, 0);

        if(!surf) {
            cout << "Failed to render text." << endl;
            cout << TTF_GetError() << endl;
            return;
        }

        _hints[key].texture = create_texture(surf);

        _hints[key].area = {
            0, 0,
            surf->w, surf->h
        };

        SDL_FreeSurface(surf);
    }
}

