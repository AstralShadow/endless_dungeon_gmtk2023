#include "game/level_generator.hpp"
#include "game/hero.hpp"
#include "game/level.hpp"
#include "utils/trandom.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace game {
    std::set<Point> generated_chunks = {{0, 0}};

    // Distance the hero has to have from any chunk to get new chunk generated
    static const int area_min_distance = 1; // chunks

    // Maximum distance the chunk may appear in
    static const int area_max_distance = 2; // chunks

    // Minimum distance between chunks
    static const int area_spread = 3; // chunks

    // Minimum distance from the player
    static const int min_hero_distance = 1;


    static const bool verbose_log = false;
}


void game::spawn_areas()
{
    if(verbose_log)
        cout << "Attempting area generation." << endl;

    auto& hero = game::hero();

    Point current_chunk {
        hero.pos.x / 16,
        hero.pos.y / 16
    };

    auto blocking_chunks = level().get_chunks_near
        (current_chunk.x, current_chunk.y,
         area_min_distance);

    if(verbose_log) {
        cout << "Poitential gen blocks: ";
        cout << blocking_chunks.size() << endl;
    }

    for(auto point : blocking_chunks) {
        auto _end = generated_chunks.end();
        if(generated_chunks.find(point) != _end)
            return;
    }
    if(verbose_log)
        cout << "Block check passed." << endl;

    struct RNG_Token;

    for(int attempt = 0; attempt < 10; ++attempt) {
        if(verbose_log)
            cout << "Attempt " << attempt << endl;
        const int min = min_hero_distance;
        const int max = area_max_distance;
        Point new_chunk {
            current_chunk.x
                + random<-max, max, RNG_Token>(),
            current_chunk.y
                + random<-max, max, RNG_Token>()
        };
        auto delta = new_chunk - current_chunk;
        if(std::abs(delta.x) + std::abs(delta.y) < min) {
            if(verbose_log)
                cout << "Invalid pos picked." << endl;
            continue;
        }


        auto blockers = level().get_chunks_near
            (new_chunk.x, new_chunk.y, area_spread);

        if(verbose_log)
            cout << "Checking availability..." << endl;
        for(auto point : blockers) {
            auto _end = generated_chunks.end();
            if(generated_chunks.find(point) != _end) {
                if(verbose_log)
                    cout << "Busy pos picked." << endl;
                goto next_attempt;
            }
        }

        generated_chunks.insert(new_chunk);
        spawn_area(new_chunk);
        break;

        next_attempt:;
    }
}
