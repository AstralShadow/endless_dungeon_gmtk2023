# Tasks for Alaka:

- [x] This is a completed task example.

- [ ] Read all tasks and pick most important first.

- [ ] Add "Created for" to logo in `assets/jamlogo2023.png`
    - Try not to make the image bigger than `1500x1100`
    - Code: `src/startup/logo.hpp`
        - contains image filename
        - contains timing variables
    - Original image in `doc/gmtk/jamlogo2023.png`

- [ ] Draw Wall & Floor texture(s)
    - Files: `assets/wall_solid.png` `assets/floor_grass.png`,
    - GIMP: `doc/gimp/azcraft/wall_solid.xcf`
    - They contain `4x4` tiles with `64x64` size (total size `256x256`)
    - Code: `src/game/render_tile.hpp`
    - The game picks random tile for every place.
    - If you want and have time you can make multiple versions for multiple game areas. (like different cave textures)
        - Not yet implemented in code.

- [ ] Draw Wall Border textures
    - File: `assets/wall_border.png`
    - GIMP: `doc/gimp/azcraft/wall_border.xcf`
    - It contains `4x5` tiles with `64x64` size (total size `256x256`)
    - If you don't want you can not draw these, but they will look cool.
        They will be rendered over floor tiles.
    - If you draw multiple floor types you should draw multiple border types too.

    - First row contains edges
        - top-right
        - bottom-right
        - bottom-left
        - top-left
    - Second row contains lines
        - right
        - bottom
        - left
        - top
    - Third row contains L (2 lines)
        - bottom-right
        - bottom-left
        - top-left
        - top-right
    - Fourth row contains U (3 lines)
        - no-top
        - no-right
        - no-bottom
        - no-left
    - Fifth row contains:
        - top and bottom line
        - left and right line
        - all 4 lines
        - unused texture


- [ ] Hero (main character)
    - Size: `64x64` or `64x128`
