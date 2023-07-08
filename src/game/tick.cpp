#include "game/game.hpp"
#include "game/tick.hpp"
#include "utils/screen.hpp"


void game::tick(u32 ms, scene_uid)
{
    update_screen_size();

    tick_move_camera(ms);
}
