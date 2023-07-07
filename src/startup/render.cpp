#include "startup/startup.hpp"
#include "startup/logo.hpp"
#include "core/core.hpp"
#include "utils/screen.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void startup::render(scene_uid)
{
    SDL_RenderClear(rnd);

    auto logo = gmtk_logo();
    SDL_RenderCopy(rnd, logo, nullptr, &gmtk_logo_pos);

    SDL_RenderPresent(rnd);
}
