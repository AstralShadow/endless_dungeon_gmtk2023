#include "game/hero.hpp"
#include "game/level.hpp"
#include <iostream>

using std::cout;
using std::endl;

using game::Hero;


Hero& game::hero()
{
    static Hero _hero;
    return _hero;
}


Hero::Hero() : Entity(Tile::C_HERO)
{

}

