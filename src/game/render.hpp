#ifndef INCLUDE_GAME_RENDER_HPP
#define INCLUDE_GAME_RENDER_HPP

namespace game
{
    /**
     * Renders level map up to N-th line.
     * This is useful for properly z-indexing stuff. 
     *
     * y in world coordinates
     */
    /** Renders until y: (-inf, y) */
    void render_map_before(int y);
    /** Renders from y1 to y2: [y1, y2)  */
    void render_map_between(int y1, int y2);
    /** Renders from y: [y, inf) */
    void render_map_after(int y);


    void render_tile(int x, int y);
    void render_tile_border(int x, int y);

    void render_hero();
}

#endif // INCLUDE_GAME_RENDER_HPP
