#include "game/game.hpp"
#include "game/tick.hpp"
#include "game/navigation.hpp"
#include "utils/screen.hpp"
#include "game/hints.hpp"
#include "game/level_generator.hpp"

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



    for(int i = 0; i < speed_mode; i++) {
        tick_hero(ms);
        tick_enemies(ms);
    }

    ms *= speed_mode;

    /* Level Generation */
    if(!spawning_process) {
        static u32 buffer = 0;
        buffer += ms;
        if(buffer > 1000) {
            buffer -= 1000;
            spawn_areas();
        }
    } else {
        tick_area_generator(ms);
    }
}
