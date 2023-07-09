#include "game/level_generator.hpp"
#include "utils/trandom.hpp"
#include "game/navigation.hpp"
#include "game/level.hpp"
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


void game::tick_area_generator(u32 ms)
{
    auto& level = game::level();

    if(tiles_waiting.size()) {
        static u32 buffer = 0;
        buffer += ms;
        if(buffer > 50) {
            buffer -= 50;
            auto point = tiles_waiting.front();
            tiles_waiting.pop();
            level.at(point) = ground_tile();
        }
        return;
    }

    spawning_process = false;

}

