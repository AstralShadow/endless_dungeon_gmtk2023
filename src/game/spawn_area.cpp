#include "game/level_generator.hpp"
#include "utils/trandom.hpp"
#include "game/navigation.hpp"
#include "game/level.hpp"
#include "game/hints.hpp"
#include "game/enemy.hpp"
#include <queue>
#include <iostream>

using std::cout;
using std::endl;


namespace game
{
    bool spawning_process = false;
    static std::set<Point> area;
    static std::queue<Point> tiles_waiting;
}


void game::spawn_area(Point chunk)
{
    struct RNG_Token;
    activate_hint(H_AREA_SPAWN);

    cout << "Generating chunk at ";
    cout << chunk.x << ":" << chunk.y << endl;

    area.clear();
    switch(random<0, 1, RNG_Token>()) {
        case 0:
            area = plan_diamond_area(chunk);
            break;

        case 1:
        default:
            area = plan_rect_area(chunk);
            break;
    }

    while(!tiles_waiting.empty())
        tiles_waiting.pop();

    for(auto p : area)
        tiles_waiting.push(p);

    spawning_process = true;
}

Point game::get_spawning_area_pos()
{
    if(!tiles_waiting.empty())
        return tiles_waiting.front();
    return {0, 0};
}


void game::tick_area_generator(u32 ms)
{
    auto& level = game::level();

    if(tiles_waiting.size()) {
        static u32 buffer = 0;
        buffer += ms;
        if(buffer > 75) {
            buffer -= 75;
            auto point = tiles_waiting.front();
            tiles_waiting.pop();
            level.at(point) = ground_tile();
        }
        return;
    }

    struct RNG_Token;

    float enemies = 1 + randomf<RNG_Token>()
        * area.size() / 32;

    int _enemies = static_cast<int>(enemies);
    while(_enemies > 0) {
        for(Point pos : area) {
            if(randomf<RNG_Token>() < 0.01) {
                spawn_enemy(pos);
                _enemies--;
                break;
            }
        }
    }

    spawning_process = false;

}

