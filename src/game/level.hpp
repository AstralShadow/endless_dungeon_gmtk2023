#ifndef INCLUDE_GAME_LEVEL_HPP
#define INCLUDE_GAME_LEVEL_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include "game/tile.hpp"
#include <unordered_map>

using std::unordered_map;


namespace game
{
    struct Tile;

    /**
     * Represents a tilemap, but uses compression.
     */
    class Level
    {
    public:
        Level();
        ~Level();


        // TODO provide a copy of Tile that gets stored in the wrapper, and updated on-change in the map. It does not seem as an easy thing so for now just don't pass Tile& around.

        /**
         * Wraps tiles so we can update the Level
         *  when new tiles get defined
         */
        struct TileWrapper
        {
            Level* parent;
            Point pos;

            operator Tile ();
            TileWrapper& operator = (Tile);
        };

        TileWrapper at(int x, int y);
        TileWrapper at(Point);


    private:
        struct Chunk
        {
            u16 active_tiles = 0; // not default tiles
            Tile tiles[256];
        };

        typedef u32 ChunkPos;
        unordered_map<ChunkPos, Chunk> _data;


        ChunkPos hash_chunk_pos(int x, int y);
        /** These functions take chunk coords (16bit) */
        /* Can return nullptr */
        Chunk* find_chunk(int x, int y);
        /* Creates chunk if not existing*/
        Chunk* get_chunk(int x, int y);
        /* Removes chunk if existing */
        void remove_chunk(int x, int y);
    };

    Level& level();
}

#endif // INCLUDE_GAME_LEVEL_HPP
