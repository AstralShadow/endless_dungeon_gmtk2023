#include "game/game.hpp"
#include "game/tick.hpp"
#include "game/navigation.hpp"
#include "utils/screen.hpp"
#include "game/hints.hpp"

int game::speed_mode = 0;


void game::tick(u32 ms, scene_uid)
{
    for(auto key : active_hints()) {
        auto& hint = get_hint(key);
        hint.lifetime += ms;
    }

    update_screen_size();
    tick_move_camera(ms);
    tick_tile_values(ms);


    ms *= speed_mode;

    tick_hero(ms);
}
