#ifndef INCLUDE_GAME_ENEMY_HPP
#define INCLUDE_GAME_ENEMY_HPP

#include "utils/point.hpp"
#include "game/entity.hpp"
#include <vector>

using std::vector;

namespace game
{
    enum EnemyType
    {
        ET_RAT,
        ET_GHOST,

        ET_LAST
    };

    struct Enemy : public Entity
    {
        Enemy(EnemyType, int hp, int atk, float spd);

        EnemyType type;
        int _health;
        int _attack;

        float _speed;


        int health() { return _health; }
        int attack() { return _attack; }
        float speed() { return _speed; }
    };


    Enemy& spawn_enemy(Point, EnemyType = ET_LAST);

    vector<Enemy>& enemies();
}

#endif // INCLUDE_GAME_ENEMY_HPP
