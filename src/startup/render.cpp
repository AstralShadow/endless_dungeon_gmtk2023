#include "startup/startup.hpp"
#include "startup/logo.hpp"
#include "game/fonts.hpp"
#include "core/core.hpp"
#include "utils/screen.hpp"
#include "utils/textures.hpp"
#include <SDL2/SDL_render.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

static auto& rnd = core::renderer;


void startup::render(scene_uid)
{
    SDL_RenderClear(rnd);

    auto logo = gmtk_logo();
    SDL_RenderCopy(rnd, logo, nullptr, &gmtk_logo_pos);

    /* "Created for" text */
    if(time > text_enter_start && time < text_exit_end) {
        auto font = get_font(game::FT_DEFAULT, 40);
        SDL_Color color {255, 255, 255, 255};

        string text = "Created in 48h for:";
        auto length = text.size();
        auto first = 0;

        if(time < text_enter_end) {
            auto k = 1.0f * (time - text_enter_start)
                / (text_enter_end - text_enter_start);
            length *= k;
        } else if (time > text_exit_start) {
            auto k = 1 - 1.0f * (time - text_exit_start)
                / (text_exit_end - text_exit_start);
            length *= k;
            first = text.size() - length;
        }

        string subtext = text.substr(first, length);

        if(length > 0) {
            auto surf = TTF_RenderUTF8_Blended
                (font, subtext.c_str(), color);

            if(!surf) {
                cout << "Failed to render text" << endl;
                cout << TTF_GetError() << endl;
            } else {
                auto tex = utils::create_texture(surf);

                auto screen = screen_size();
                SDL_Rect dest {
                    (screen.x - surf->w) / 2,
                    100,
                    surf->w, surf->h
                };

                SDL_RenderCopy(rnd, tex, nullptr, &dest);

                SDL_DestroyTexture(tex);
                SDL_FreeSurface(surf);
            }
        }
    }


    SDL_RenderPresent(rnd);
}
