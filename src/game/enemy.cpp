#include "game/enemy.hpp"
#include "game/hero.hpp"
#include "game/tile.hpp"
#include "utils/trandom.hpp"
#include "game/hints.hpp"

using game::Enemy;


namespace game
{
    int defeated_enemies = 0;

    struct BaseStats
    {
        float health;
        float attack;
        float speed;
    } static _base[ET_LAST] {
        { // ET_RAT
            150,
            30,
            160
        },
        { // ET_GHOST
            250,
            50,
            96
        }
    };
}

struct RNG_Token;

vector<Enemy>& game::enemies()
{
    static vector<Enemy> _enemies;
    return _enemies;
}

Enemy::Enemy(EnemyType _type,
             int _hp, int _atk, float _spd) :
    Entity(Tile::C_ENEMY),
    type(_type),
    _health(_hp),
    _attack(_atk),
    _speed(_spd)
{ }


Enemy& game::spawn_enemy(Point p, EnemyType t)
{
    if(t == ET_LAST) {
        if(defeated_enemies < 5) {
            t = ET_RAT;
        } else {
            float chance = 0.05f * defeated_enemies;
            if(chance > 0.6f)
                chance = 0.6f;

            if(randomf<RNG_Token>() < chance)
                t = ET_GHOST;
            else
                t = ET_RAT;
        }
    }

    float difficulty_multiplier = 0.1f;
    if(defeated_enemies > 5)
        difficulty_multiplier
            += 0.05f * defeated_enemies;

    Enemy enemy (
        t,
        static_cast<int>
            (difficulty_multiplier * _base[t].health),
        static_cast<int>
            (difficulty_multiplier * _base[t].attack),
        64 + _base[t].speed * defeated_enemies
                           / (defeated_enemies + 5.0)
    );

    if(enemy.speed() > 80) {
        activate_hint(H_MOVING_RAT);
    }

    enemy.move_to(p);

    enemies().push_back(enemy);

    return enemies().back();
}


