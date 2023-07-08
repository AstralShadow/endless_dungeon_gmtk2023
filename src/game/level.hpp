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


        /**
         * Wraps tiles so we can update the Level
         *  when new tiles get defined
         */
        struct TileWrapper
        {
            // TODO provide a copy of Tile that gets stored in the wrapper, and updated on-change in the map. It does not seem as an easy thing so for now just don't pass Tile& around.

            Level* parent;
            Point pos;

            operator Tile ();
            TileWrapper& operator = (Tile);

            /**
             * Does not update dijkstra maps.
             * Used in dijkstra map calculation
             *
             * Returns if maps should be updated
             */
            bool set(Tile);
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


        static ChunkPos hash_chunk_pos(int x, int y);
        static Point unhash_chunk_pos(ChunkPos);

        /** These functions take chunk coords (16bit) */
        /* Can return nullptr */
        Chunk* find_chunk(int x, int y);
        /* Creates chunk if not existing*/
        Chunk* get_chunk(int x, int y);
        /* Removes chunk if existing */
        void remove_chunk(int x, int y);

        friend void update_dijkstra_maps();
        friend void tick_tile_values(u32 ms);
    };

    Level& level();
}

#endif // INCLUDE_GAME_LEVEL_HPP
