#include "game/game.hpp"
#include "game/tick.hpp"
#include "game/navigation.hpp"
#include "utils/screen.hpp"

int game::speed_mode = 1;

void game::tick(u32 ms, scene_uid)
{
    ms *= speed_mode;

    update_screen_size();

    tick_move_camera(ms);

    tick_tile_values(ms);

    tick_hero(ms);
}
