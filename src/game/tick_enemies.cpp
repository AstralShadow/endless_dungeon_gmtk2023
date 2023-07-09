#include "game/tick.hpp"
#include "game/enemy.hpp"


void game::tick_enemies(u32 ms)
{
    for(Enemy& enemy : enemies())
        tick_enemy_movement(ms, enemy);
}
