#include "game/render.hpp"
#include "game/hints.hpp"
#include "utils/textures.hpp"
#include "utils/screen.hpp"
#include "game/fonts.hpp"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;


void game::render_hints()
{
    auto screen = screen_size();

    for(auto key : active_hints()) {
        auto& hint = get_hint(key);

        switch(hint.pos) {
            case TOP_LEFT:
                hint.area.x = screen.x * 0.05;
                hint.area.y = screen.y * 0.05;
                break;

            case TOP_RIGHT:
                hint.area.x = screen.x * 0.95;
                hint.area.y = screen.y * 0.05;
                hint.area.x -= hint.area.w;
                break;

            case MID_LEFT:
                hint.area.x = screen.x * 0.05;
                hint.area.y = screen.y * 0.5;
                hint.area.y -= hint.area.h / 2;
                break;

            case MID_CENTER:
                hint.area.x = screen.x * 0.5;
                hint.area.y = screen.y * 0.5;
                hint.area.x -= hint.area.w / 2;
                hint.area.y -= hint.area.h / 2;
                break;

            case BOTTOM_RIGHT:
                hint.area.x = screen.x * 0.95;
                hint.area.y = screen.y * 0.95;
                hint.area.x -= hint.area.w;
                hint.area.y -= hint.area.h;
                hint.area.y -= screen.x * 0.3 / 4;
                break;

            case BOTTOM_LEFT:
                hint.area.x = screen.x * 0.05;
                hint.area.y = screen.y * 0.95;
                hint.area.y -= hint.area.h;
                break;

        }

        const float frame_speed = frame_dropdown_speed;
        const float text_speed = game::text_speed;

        float visible = hint.lifetime * text_speed
            / (hint.text.size() * 1000);
        int characters = std::max(0.0f, visible)
            * hint.text.size();
        string text = hint.text.substr(0, characters);

        float visible_frame = (hint.lifetime + 500)
            * frame_speed / (hint.area.h * 1000);
        if(visible_frame > 1)
            visible_frame = 1;

        SDL_Rect src {
            0, 0,
            hint.area.w,
            hint.area.h
        };
        SDL_Rect dest = hint.area;

        SDL_Rect frame {
            dest.x - 20,
            dest.y - 20,
            dest.w + 40,
            dest.h + 40
        };

        if(visible_frame < 1) {
            frame.h *= visible_frame;
        }

        auto texture = hint.texture;
        if(text.size() > 0 && visible < 1) {
            auto font = get_font(FT_DEFAULT);
            SDL_Color color {255, 255, 255, 255};

            auto surf = TTF_RenderUTF8_Blended_Wrapped
                (font, text.c_str(), color, 0);

            if(!surf) {
                cout << "Failed to render hint" << endl;
                cout << TTF_GetError() << endl;
                return;
            }

            texture = utils::create_texture(surf);

            src.w = surf->w;
            src.h = surf->h;
            dest.w = surf->w;
            dest.h = surf->h;

            SDL_FreeSurface(surf);
        }

        
        if(visible_frame > 0) {
            SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
            SDL_RenderFillRect(rnd, &frame);
            SDL_SetRenderDrawColor
                (rnd, 255, 255, 255, 255);
            SDL_RenderDrawRect(rnd, &frame);
        }

        if(text.size() > 0)
            SDL_RenderCopy(rnd, texture, &src, &dest);

        if(texture != hint.texture)
            SDL_DestroyTexture(texture);
    }
}

